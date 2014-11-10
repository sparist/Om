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
	get_filename_component(OutputDirectory "${Directory}/${Md5}" REALPATH)

	message(STATUS "Unpacking ICU4C")
	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E tar xvzf "${Download}.${Extension}"
		WORKING_DIRECTORY "${OutputDirectory}/download"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "ICU4C could not be unpacked: ${Status}")
	endif()

	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E make_directory "build/${Name}/make"
		WORKING_DIRECTORY "${OutputDirectory}"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "The directory \"${OutputDirectory}/build/${Name}/make\" could not be created: ${Status}")
	endif()
	get_filename_component(BuildDirectory "${OutputDirectory}/build/${Name}" REALPATH)

	function(BuildIcu4cConfiguration BuildDirectory Configuration)
		execute_process(
			COMMAND "${CMAKE_COMMAND}" -E make_directory "${Configuration}"
			WORKING_DIRECTORY "${BuildDirectory}/make"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "The directory \"${BuildDirectory}/make/${Configuration}\" could not be created: ${Status}")
		endif()

		set(EnableDebugOption)
		set(DisableReleaseOption)
		if("${Configuration}" STREQUAL "Debug")
			set(EnableDebugOption --enable-debug)
			set(DisableReleaseOption --disable-release)
		endif()

		set(DisableSharedOption --disable-shared)
		set(PrefixOption "${InstallDirectoryDefault}")
		set(CppFlagsOption)
		if(WIN32)
			set(System Cygwin/MSVC)

			execute_process(
				COMMAND cygpath --unix "${PrefixOption}"
				OUTPUT_VARIABLE PrefixOption
				RESULT_VARIABLE Status
			)
			if(NOT ${Status} EQUAL 0)
				message(FATAL_ERROR "The ICU4C install directory path could not be converted to Unix format: ${Status}")
			endif()

			# On Windows, the shared libraries must be built for Boost ICU detection to succeed.
			set(DisableSharedOption)
		else()
			if(APPLE)
				set(System MacOSX)
			else()
				set(System Linux)
			endif()
			set(CppFlagsOption CPPFLAGS=-DU_CHARSET_IS_UTF8=1)
		endif()

		message(STATUS "Configuring ICU4C (${Configuration})")
		execute_process(
			COMMAND bash ../../../../download/icu/source/runConfigureICU ${EnableDebugOption} ${DisableReleaseOption} ${System} --enable-static ${DisableSharedOption} --prefix=${PrefixOption} ${CppFlagsOption}
			WORKING_DIRECTORY "${BuildDirectory}/make/${Configuration}"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "ICU4C (${Configuration}) could not be configured: ${Status}")
		endif()

		message(STATUS "Building ICU4C (${Configuration})")
		execute_process(
			COMMAND make -s
			WORKING_DIRECTORY "${BuildDirectory}/make/${Configuration}"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "ICU4C (${Configuration}) could not be built: ${Status}")
		endif()

		message(STATUS "Installing ICU4C (${Configuration})")
		execute_process(
			COMMAND make -s install
			WORKING_DIRECTORY "${BuildDirectory}/make/${Configuration}"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "ICU4C (${Configuration}) could not be installed: ${Status}")
		endif()
	endfunction()

	if(WIN32)
		BuildIcu4cConfiguration(${BuildDirectory} Debug)
	endif()
	BuildIcu4cConfiguration(${BuildDirectory} Release)
endfunction()

# Note that ICU4C does not support spaces in the path.
function(SetUpIcu4c BuildsDirectory Platform
	I18nDebugLibraryVariable I18nReleaseLibraryVariable
	UcDebugLibraryVariable UcReleaseLibraryVariable
	DataDebugLibraryVariable DataReleaseLibraryVariable
)
	set(MajorVersion 54)
	set(MinorVersion 1)
	set(Extension tgz)
	set(Md5 e844caed8f2ca24c088505b0d6271bc0)

	set(BuildDirectoryDefault "${BuildsDirectory}/Icu4c")
	set(BuildDirectoryCaption "The ICU4C build path")
	set(Icu4cBuildDirectory "${BuildDirectoryDefault}" CACHE PATH "${BuildDirectoryCaption}")

	set(InstallDirectoryDefault "${Icu4cBuildDirectory}/${Md5}/build/${Platform}/install")
	set(InstallDirectoryCaption "The ICU4C install path")
	set(Icu4cInstallDirectory "${InstallDirectoryDefault}" CACHE PATH "${InstallDirectoryCaption}")

	if(NOT EXISTS "${Icu4cInstallDirectory}")
		set(Icu4cBuildDirectory "${BuildDirectoryDefault}" CACHE PATH "${BuildDirectoryCaption}" FORCE)

		execute_process(
			COMMAND "${CMAKE_COMMAND}" -E make_directory "${Icu4cBuildDirectory}"
			WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "The directory \"${Icu4cBuildDirectory}\" could not be created: ${Status}")
		endif()

		BuildIcu4c("${Icu4cBuildDirectory}" "${Platform}" ${MajorVersion} ${MinorVersion} ${Extension} ${Md5})

		get_filename_component(InstallDirectory "${InstallDirectoryDefault}" REALPATH)
		set(Icu4cInstallDirectory "${InstallDirectory}" CACHE PATH "${InstallDirectoryCaption}" FORCE)
	endif()

	if(WIN32)
		find_library(I18nDebugLibrary sicuind "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(I18nReleaseLibrary sicuin "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(UcDebugLibrary sicuucd "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(UcReleaseLibrary sicuuc "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(DataDebugLibrary sicudtd "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(DataReleaseLibrary sicudt "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
	else()
		find_library(I18nDebugLibrary icui18n "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(I18nReleaseLibrary icui18n "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(UcDebugLibrary icuuc "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(UcReleaseLibrary icuuc "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(DataDebugLibrary icudata "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(DataReleaseLibrary icudata "${Icu4cInstallDirectory}/lib" NO_DEFAULT_PATH)
	endif()

	set(${I18nDebugLibraryVariable} "${I18nDebugLibrary}" PARENT_SCOPE)
	set(${I18nReleaseLibraryVariable} "${I18nReleaseLibrary}" PARENT_SCOPE)
	set(${UcDebugLibraryVariable} "${UcDebugLibrary}" PARENT_SCOPE)
	set(${UcReleaseLibraryVariable} "${UcReleaseLibrary}" PARENT_SCOPE)
	set(${DataDebugLibraryVariable} "${DataDebugLibrary}" PARENT_SCOPE)
	set(${DataReleaseLibraryVariable} "${DataReleaseLibrary}" PARENT_SCOPE)
endfunction()
