cmake_minimum_required(VERSION 2.8.7)

# Arguments:
# -D Platform=[Platform]
# -D MajorVersion=[Major Version]
# -D MinorVersion=[Minor Version]
# -D Extension=[Download Extension]
# -D Md5=[Download MD5]

set(Name icu)

set(Output "./${Md5}")
file(
	DOWNLOAD "http://download.icu-project.org/files/icu4c/${MajorVersion}.${MinorVersion}/icu4c-${MajorVersion}_${MinorVersion}-src.${Extension}" "${Output}/download/${Name}.${Extension}"
	STATUS DownloadStatus
	SHOW_PROGRESS
	EXPECTED_MD5 ${Md5}
)
list(GET DownloadStatus 0 Status)
if(NOT ${Status} EQUAL 0)
	list(GET DownloadStatus 1 Error)
	message(FATAL_ERROR "ICU4C could not be downloaded: ${Error} (${Status})")
endif()
get_filename_component(Output ${Output} REALPATH)

execute_process(
	COMMAND "${CMAKE_COMMAND}" -E tar xvzf "${Name}.${Extension}"
	WORKING_DIRECTORY "${Output}/download"
	RESULT_VARIABLE Status
)
if(NOT ${Status} EQUAL 0)
	message(FATAL_ERROR "ICU4C could not be unpacked: ${Status}")
endif()

execute_process(
	COMMAND "${CMAKE_COMMAND}" -E make_directory "build/${Platform}/make"
	WORKING_DIRECTORY "${Output}"
	RESULT_VARIABLE Status
)
if(NOT ${Status} EQUAL 0)
	message(FATAL_ERROR "The directory \"${Output}/build/${Platform}/make\" could not be created: ${Status}")
endif()
get_filename_component(Build "${Output}/build/${Platform}" REALPATH)

function(CreateConfigurationDirectory Configuration)
	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${Configuration}"
		WORKING_DIRECTORY "${Build}/make"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "The directory \"${Build}/make/${Configuration}\" could not be created: ${Status}")
	endif()
endfunction()
if(WIN32)
	CreateConfigurationDirectory(Debug)
endif()
CreateConfigurationDirectory(Release)

if(WIN32)
	set(System Cygwin/MSVC)

	if(WIN32)
		execute_process(
			COMMAND cygpath --unix "${Build}/install"
			OUTPUT_VARIABLE Prefix
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "The output path could not be converted to Unix format: ${Status}")
		endif()
	endif()

	message(STATUS "Configuring ICU4C (Debug)...")
	execute_process(
		COMMAND bash ../../../../download/icu/source/runConfigureICU --enable-debug --disable-release ${System} --enable-static --prefix=${Prefix}
		WORKING_DIRECTORY "${Build}/make/Debug"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "ICU4C (Debug) could not be configured: ${Status}")
	endif()

	message(STATUS "Configuring ICU4C (Release)...")
	execute_process(
		COMMAND bash ../../../../download/icu/source/runConfigureICU ${System} --enable-static --prefix=${Prefix}
		WORKING_DIRECTORY "${Build}/make/Release"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "ICU4C (Release) could not be configured: ${Status}")
	endif()
else()
	if(APPLE)
		set(System MacOSX)
	else()
		set(System Linux)
	endif()

	message(STATUS "Configuring ICU4C (Release)...")
	execute_process(
		COMMAND ../../../../download/icu/source/runConfigureICU ${System} --enable-static --disable-shared --prefix=${Build}/install CPPFLAGS=-DU_CHARSET_IS_UTF8=1
		WORKING_DIRECTORY "${Build}/make/Release"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "ICU4C (Release) could not be configured: ${Status}")
	endif()
endif()

function(Build Configuration)
	message(STATUS "Building ICU4C (${Configuration})...")
	execute_process(
		COMMAND make -s
		COMMAND make -s install
		WORKING_DIRECTORY "${Build}/make/${Configuration}"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "ICU4C (${Configuration}) could not be built: ${Status}")
	endif()
endfunction()
if(WIN32)
	Build(Debug)
endif()
Build(Release)
