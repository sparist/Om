cmake_minimum_required(VERSION 2.8.7)

function(BuildBoost Directory Name MajorVersion MinorVersion Extension Md5 Icu4c)
	set(Download "boost_${MajorVersion}_${MinorVersion}_0")

	file(
		DOWNLOAD "http://sourceforge.net/projects/boost/files/boost/${MajorVersion}.${MinorVersion}.0/${Download}.${Extension}/download" "${Directory}/${Md5}/download/${Download}.${Extension}"
		STATUS DownloadStatus
		SHOW_PROGRESS
		EXPECTED_MD5 ${Md5}
	)
	list(GET DownloadStatus 0 Status)
	if(NOT ${Status} EQUAL 0)
		list(GET DownloadStatus 1 Error)
		message(FATAL_ERROR "Boost could not be downloaded: ${Error} (${Status})")
	endif()
	get_filename_component(Output "${Directory}/${Md5}" REALPATH)

	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E tar xvzf "${Download}.${Extension}"
		WORKING_DIRECTORY "${Output}/download"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "Boost could not be unpacked: ${Status}")
	endif()

	message(STATUS "Configuring Boost...")
	set(BootstrapCommand ./bootstrap.sh)
	if(WIN32)
		set(BootstrapCommand bootstrap.bat)
	endif()
	execute_process(
		COMMAND ${BootstrapCommand}
		WORKING_DIRECTORY "${Output}/download/${Download}"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "Boost could not be configured: ${Status}")
	endif()

	message(STATUS "Building Boost...")
	set(Build "${Output}/build/${Name}")
	set(BuildCommand ./b2)
	set(DefineOption define=U_CHARSET_IS_UTF8=1)
	set(HashOption)
	set(AddressModelOption)
	set(LinkFlagsOption linkflags=-ldl)
	if(WIN32)
		set(BuildCommand b2)
		set(DefineOption define=U_STATIC_IMPLEMENTATION=1)
		set(HashOption --hash)
		if(CMAKE_CL_64)
			set(AddressModelOption address-model=64)
		endif()
		set(LinkFlagsOption)
	endif()
	execute_process(
		COMMAND ${BuildCommand} boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off boost.locale.winapi=off boost.locale.posix=off ${DefineOption} -sICU_PATH="${Icu4c}" --build-dir=${Build}/make --prefix=${Build}/install ${HashOption} --with-locale --with-system --with-thread --with-test link=static ${AddressModelOption} ${LinkFlagsOption} install
		WORKING_DIRECTORY "${Output}/download/${Download}"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "Boost could not be built: ${Status}")
	endif()
endfunction()
