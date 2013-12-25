cmake_minimum_required(VERSION 2.8.7)

# Arguments:
# -D Name=[Name]
# -D MajorVersion=[Major Version]
# -D MinorVersion=[Minor Version]
# -D Extension=[Download Extension]
# -D Md5=[Download MD5]

set(Download icu)

file(
	DOWNLOAD "http://download.icu-project.org/files/icu4c/${MajorVersion}.${MinorVersion}/icu4c-${MajorVersion}_${MinorVersion}-src.${Extension}" "${Md5}/download/${Download}.${Extension}"
	STATUS DownloadStatus
	SHOW_PROGRESS
	EXPECTED_MD5 ${Md5}
)
list(GET DownloadStatus 0 Status)
if(NOT ${Status} EQUAL 0)
	list(GET DownloadStatus 1 Error)
	message(FATAL_ERROR "ICU4C could not be downloaded: ${Error} (${Status})")
endif()
get_filename_component(Output ${Md5} REALPATH)

execute_process(
	COMMAND "${CMAKE_COMMAND}" -E tar xvzf "${Download}.${Extension}"
	WORKING_DIRECTORY "${Output}/download"
	RESULT_VARIABLE Status
)
if(NOT ${Status} EQUAL 0)
	message(FATAL_ERROR "ICU4C could not be unpacked: ${Status}")
endif()

execute_process(
	COMMAND "${CMAKE_COMMAND}" -E make_directory "build/${Name}/make"
	WORKING_DIRECTORY "${Output}"
	RESULT_VARIABLE Status
)
if(NOT ${Status} EQUAL 0)
	message(FATAL_ERROR "The directory \"${Output}/build/${Name}/make\" could not be created: ${Status}")
endif()
get_filename_component(Build "${Output}/build/${Name}" REALPATH)

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

set(Prefix ${Build}/install)
set(System)
set(DisableSharedOption --disable-shared)
set(CppFlagsOption CPPFLAGS=-DU_CHARSET_IS_UTF8=1)
if(WIN32)
	set(System Cygwin/MSVC)

	execute_process(
		COMMAND cygpath --unix "${Prefix}"
		OUTPUT_VARIABLE Prefix
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "The output path could not be converted to Unix format: ${Status}")
	endif()

	set(DisableSharedOption)
	set(CppFlagsOption)

	message(STATUS "Configuring ICU4C (Debug)...")
	CreateConfigurationDirectory(Debug)
	execute_process(
		COMMAND bash ../../../../download/icu/source/runConfigureICU --enable-debug --disable-release ${System} --enable-static --prefix=${Prefix}
		WORKING_DIRECTORY "${Build}/make/Debug"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "ICU4C (Debug) could not be configured: ${Status}")
	endif()
	Build(Debug)
else()
	if(APPLE)
		set(System MacOSX)
	else()
		set(System Linux)
	endif()
endif()

message(STATUS "Configuring ICU4C (Release)...")
CreateConfigurationDirectory(Release)
execute_process(
	COMMAND bash ../../../../download/icu/source/runConfigureICU ${System} --enable-static ${DisableSharedOption} --prefix=${Prefix} ${CppFlagsOption}
	WORKING_DIRECTORY "${Build}/make/Release"
	RESULT_VARIABLE Status
)
if(NOT ${Status} EQUAL 0)
	message(FATAL_ERROR "ICU4C (Release) could not be configured: ${Status}")
endif()
Build(Release)
