cmake_minimum_required(VERSION 2.8.7)

# Arguments:
# -D Platform=[Platform]
# -D MajorVersion=[Major Version]
# -D MinorVersion=[Minor Version]
# -D Extension=[Download Extension]
# -D Md5=[Download MD5]
# -D Icu4c=[ICU4C Install Directory]

set(Name "boost_${MajorVersion}_${MinorVersion}_0")

set(Output "./${Md5}")
file(
	DOWNLOAD "http://sourceforge.net/projects/boost/files/boost/${MajorVersion}.${MinorVersion}.0/${Name}.${Extension}/download" "${Output}/download/${Name}.${Extension}"
	STATUS DownloadStatus
	SHOW_PROGRESS
	EXPECTED_MD5 ${Md5}
)
list(GET DownloadStatus 0 Status)
if(NOT ${Status} EQUAL 0)
	list(GET DownloadStatus 1 Error)
	message(FATAL_ERROR "Boost could not be downloaded: ${Error} (${Status})")
endif()
get_filename_component(Output "${Output}" REALPATH)

execute_process(
	COMMAND "${CMAKE_COMMAND}" -E tar xvzf "${Name}.${Extension}"
	WORKING_DIRECTORY "${Output}/download"
	RESULT_VARIABLE Status
)
if(NOT ${Status} EQUAL 0)
	message(FATAL_ERROR "Boost could not be unpacked: ${Status}")
endif()

message(STATUS "Configuring Boost...")
if(WIN32)
	execute_process(
		COMMAND bootstrap.bat
		WORKING_DIRECTORY "${Output}/download/${Name}"
		RESULT_VARIABLE Status
	)
else()
	execute_process(
		COMMAND ./bootstrap.sh
		WORKING_DIRECTORY "${Output}/download/${Name}"
		RESULT_VARIABLE Status
	)
endif()
if(NOT ${Status} EQUAL 0)
	message(FATAL_ERROR "Boost could not be configured: ${Status}")
endif()

message(STATUS "Building Boost...")
set(Build "${Output}/build/${Platform}")
if(WIN32)
	if(CMAKE_CL_64)
		set(AddressModelOption address-model=64)
	endif()
	execute_process(
		COMMAND b2 boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off boost.locale.winapi=off boost.locale.posix=off define=U_STATIC_IMPLEMENTATION=1 -sICU_PATH="${Icu4c}" --build-dir=${Build}/make --prefix=${Build}/install --hash --with-locale --with-system --with-thread --with-test link=static ${AddressModelOption} install
		WORKING_DIRECTORY "${Output}/download/${Name}"
		RESULT_VARIABLE Status
	)
else()
	execute_process(
		COMMAND ./b2 boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off define=U_CHARSET_IS_UTF8=1 -sICU_PATH="${Icu4c}" --build-dir=${Build}/make --prefix=${Build}/install --with-locale --with-system --with-thread --with-test link=static linkflags=-ldl install
		WORKING_DIRECTORY "${Output}/download/${Name}"
		RESULT_VARIABLE Status
	)
endif()
if(NOT ${Status} EQUAL 0)
	message(FATAL_ERROR "Boost could not be built: ${Status}")
endif()
