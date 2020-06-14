cmake_minimum_required(VERSION 3.0)

function(GetIcu4c Directory Name MajorVersion MinorVersion Extension Sha512
	DownloadDirectoryVariable DownloadNameVariable
)
	set(DownloadName icu)
	set(${DownloadNameVariable} ${DownloadName} PARENT_SCOPE)

	string(SUBSTRING "${Sha512}" 0 7 DownloadDirectoryName)

	message("Downloading https://github.com/unicode-org/icu/releases/download/release-${MajorVersion}-${MinorVersion}/icu4c-${MajorVersion}_${MinorVersion}-src.${Extension}...")
	file(
		DOWNLOAD "https://github.com/unicode-org/icu/releases/download/release-${MajorVersion}-${MinorVersion}/icu4c-${MajorVersion}_${MinorVersion}-src.${Extension}" "${Directory}/downloads/${DownloadDirectoryName}/download/${DownloadName}.${Extension}"
		STATUS DownloadStatus
		SHOW_PROGRESS
		EXPECTED_HASH SHA512=${Sha512}
	)
	list(GET DownloadStatus 0 Status)
	if(NOT ${Status} EQUAL 0)
		list(GET DownloadStatus 1 Error)
		message(FATAL_ERROR "ICU4C could not be downloaded: ${Error} (${Status})")
	endif()
	get_filename_component(DownloadDirectory "${Directory}/downloads/${DownloadDirectoryName}" REALPATH)
	set(${DownloadDirectoryVariable} ${DownloadDirectory} PARENT_SCOPE)

	if(NOT EXISTS "${DownloadDirectory}/download/complete")
		message(STATUS "Unpacking ICU4C")
		execute_process(
			COMMAND "${CMAKE_COMMAND}" -E tar xvzf "${DownloadName}.${Extension}"
			WORKING_DIRECTORY "${DownloadDirectory}/download"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "ICU4C could not be unpacked: ${Status}")
		endif()

		file(WRITE "${DownloadDirectory}/download/complete" "")
	endif()
endfunction()

function(BuildIcu4c Name DownloadDirectory DownloadName
	InstallDirectoryVariable
)
	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E make_directory "build/${Name}/make"
		WORKING_DIRECTORY "${DownloadDirectory}"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "The directory \"${DownloadDirectory}/build/${Name}/make\" could not be created: ${Status}")
	endif()
	get_filename_component(BuildDirectory "${DownloadDirectory}/build/${Name}" REALPATH)

	if(NOT EXISTS "${BuildDirectory}/complete")
		function(BuildIcu4cConfiguration Configuration)
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
			set(PrefixOption "${BuildDirectory}/install")
			set(CFlagsOption)
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
				set(CppFlagsOption "-DU_CHARSET_IS_UTF8=1")
				if(APPLE)
					set(System MacOSX)
				else()
					set(System Linux)
					set(CFlagsOption -fPIC)
					set(CppFlagsOption "${CppFlagsOption} -fPIC")
				endif()
			endif()

			message(STATUS "Configuring ICU4C (${Configuration})")
			set(ENV{CFLAGS} "${CFlagsOption}")
			set(ENV{CPPFLAGS} "${CppFlagsOption}")
			find_program(BashExecutable bash)
			if(NOT BashExecutable)
				message(FATAL_ERROR "Bash could not be found.")
			endif()
			execute_process(
				COMMAND "${BashExecutable}" ../../../../download/${DownloadName}/source/runConfigureICU ${EnableDebugOption} ${DisableReleaseOption} ${System} --enable-static ${DisableSharedOption} --prefix=${PrefixOption}
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
			BuildIcu4cConfiguration(Debug)
		endif()
		BuildIcu4cConfiguration(Release)

		file(WRITE "${BuildDirectory}/complete" "")
	endif()

	get_filename_component(InstallDirectory "${BuildDirectory}/install" REALPATH)
	set(${InstallDirectoryVariable} ${InstallDirectory} PARENT_SCOPE)
endfunction()

# Note that ICU4C does not support spaces in the path.
function(SetUpIcu4c BuildsDirectory Platform
	InstallDirectoryVariable
	I18nDebugLibraryVariable I18nReleaseLibraryVariable
	UcDebugLibraryVariable UcReleaseLibraryVariable
	DataDebugLibraryVariable DataReleaseLibraryVariable
)
	set(MajorVersion 56)
	set(MinorVersion 2)
	set(Extension tgz)
	set(Sha512 c94dc3c1e1da794d83b1962596c742d26d80d9f79f794dd8c14ca6dee88553ce13be4d283c54abb22329b1e78d784820af76ae1d85ab6961f5df770b2d416894)

	set(InstallDirectory "${Icu4cInstallDirectory}")
	if(NOT EXISTS "${InstallDirectory}")
		set(BuildDirectoryDefault "${BuildsDirectory}/Icu4c")
		set(BuildDirectoryCaption "The ICU4C build path")
		set(Icu4cBuildDirectory "${BuildDirectoryDefault}" CACHE PATH "${BuildDirectoryCaption}")

		execute_process(
			COMMAND "${CMAKE_COMMAND}" -E make_directory "${Icu4cBuildDirectory}"
			WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "The directory \"${Icu4cBuildDirectory}\" could not be created: ${Status}")
		endif()

		GetIcu4c("${Icu4cBuildDirectory}" "${Platform}" "${MajorVersion}" "${MinorVersion}" "${Extension}" "${Sha512}" DownloadDirectory DownloadName)
		BuildIcu4c("${Platform}" "${DownloadDirectory}" "${DownloadName}" InstallDirectory)
	endif()
	set(${InstallDirectoryVariable} "${InstallDirectory}" PARENT_SCOPE)

	if(WIN32)
		find_library(I18nDebugLibrary sicuind "${InstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(I18nReleaseLibrary sicuin "${InstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(UcDebugLibrary sicuucd "${InstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(UcReleaseLibrary sicuuc "${InstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(DataDebugLibrary sicudtd "${InstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(DataReleaseLibrary sicudt "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	else()
		find_library(I18nDebugLibrary icui18n "${InstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(I18nReleaseLibrary icui18n "${InstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(UcDebugLibrary icuuc "${InstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(UcReleaseLibrary icuuc "${InstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(DataDebugLibrary icudata "${InstallDirectory}/lib" NO_DEFAULT_PATH)
		find_library(DataReleaseLibrary icudata "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	endif()

	set(${I18nDebugLibraryVariable} "${I18nDebugLibrary}" PARENT_SCOPE)
	set(${I18nReleaseLibraryVariable} "${I18nReleaseLibrary}" PARENT_SCOPE)
	set(${UcDebugLibraryVariable} "${UcDebugLibrary}" PARENT_SCOPE)
	set(${UcReleaseLibraryVariable} "${UcReleaseLibrary}" PARENT_SCOPE)
	set(${DataDebugLibraryVariable} "${DataDebugLibrary}" PARENT_SCOPE)
	set(${DataReleaseLibraryVariable} "${DataReleaseLibrary}" PARENT_SCOPE)
endfunction()
