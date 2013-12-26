cmake_minimum_required(VERSION 2.8.7)

function(BuildIcu4c Directory Name MajorVersion MinorVersion Extension Md5)
	set(Download icu)

	file(
		DOWNLOAD "http://download.icu-project.org/files/icu4c/${MajorVersion}.${MinorVersion}/icu4c-${MajorVersion}_${MinorVersion}-src.${Extension}" "${Directory}/${Md5}/download/${Download}.${Extension}"
		STATUS DownloadStatus
		SHOW_PROGRESS
		EXPECTED_MD5 ${Md5}
	)
	list(GET DownloadStatus 0 Status)
	if(NOT ${Status} EQUAL 0)
		list(GET DownloadStatus 1 Error)
		message(FATAL_ERROR "ICU4C could not be downloaded: ${Error} (${Status})")
	endif()
	get_filename_component(Output "${Directory}/${Md5}" REALPATH)

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

	function(BuildIcu4cConfiguration Build Configuration Prefix)
		set(EnableDebugOption)
		set(DisableReleaseOption)
		string(COMPARE EQUAL "${Configuration}" "Debug" IsDebug)
		if(IsDebug)
			set(EnableDebugOption --enable-debug)
			set(DisableReleaseOption --disable-release)
		endif()

		execute_process(
			COMMAND "${CMAKE_COMMAND}" -E make_directory "${Configuration}"
			WORKING_DIRECTORY "${Build}/make"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "The directory \"${Build}/make/${Configuration}\" could not be created: ${Status}")
		endif()

		message(STATUS "Configuring ICU4C (${Configuration})...")
		set(Command bash)
		set(DisableSharedOption)
		set(CppFlagsOption)
		if(WIN32)
			set(Command bash)
			set(System Cygwin/MSVC)
		else()
			if(APPLE)
				set(System MacOSX)
			else()
				set(System Linux)
			endif()
			set(DisableSharedOption --disable-shared)
			set(CppFlagsOption CPPFLAGS=-DU_CHARSET_IS_UTF8=1)
		endif()
		execute_process(
			COMMAND ${Command} ../../../../download/icu/source/runConfigureICU ${EnableDebugOption} ${DisableReleaseOption} ${System} --enable-static ${DisableSharedOption} --prefix=${Prefix} ${CppFlagsOption}
			WORKING_DIRECTORY "${Build}/make/${Configuration}"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "ICU4C (${Configuration}) could not be configured: ${Status}")
		endif()

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
	if(WIN32)
		execute_process(
			COMMAND cygpath --unix "${Prefix}"
			OUTPUT_VARIABLE Prefix
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "The output path could not be converted to Unix format: ${Status}")
		endif()

		BuildIcu4cConfiguration(${Build} Debug ${Prefix})
	endif()
	BuildIcu4cConfiguration(${Build} Release ${Prefix})
endfunction()
