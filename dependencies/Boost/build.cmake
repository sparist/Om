cmake_minimum_required(VERSION 3.0)

function(GetBoost Directory Name MajorVersion MinorVersion Extension Sha256
	DownloadDirectoryVariable DownloadNameVariable
)
	set(DownloadName "boost_${MajorVersion}_${MinorVersion}_0")
	set(${DownloadNameVariable} ${DownloadName} PARENT_SCOPE)

	string(SUBSTRING "${Sha256}" 0 7 DownloadDirectoryName)

	file(
		DOWNLOAD "http://sourceforge.net/projects/boost/files/boost/${MajorVersion}.${MinorVersion}.0/${DownloadName}.${Extension}/download" "${Directory}/downloads/${DownloadDirectoryName}/download/${DownloadName}.${Extension}"
		STATUS DownloadStatus
		SHOW_PROGRESS
		EXPECTED_HASH SHA256=${Sha256}
	)
	list(GET DownloadStatus 0 Status)
	if(NOT ${Status} EQUAL 0)
		list(GET DownloadStatus 1 Error)
		message(FATAL_ERROR "Boost could not be downloaded: ${Error} (${Status})")
	endif()
	get_filename_component(DownloadDirectory "${Directory}/downloads/${DownloadDirectoryName}" REALPATH)
	set(${DownloadDirectoryVariable} ${DownloadDirectory} PARENT_SCOPE)

	if(NOT EXISTS "${DownloadDirectory}/download/complete")
		message(STATUS "Unpacking Boost")
		execute_process(
			COMMAND "${CMAKE_COMMAND}" -E tar xvzf "${DownloadName}.${Extension}"
			WORKING_DIRECTORY "${DownloadDirectory}/download"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "Boost could not be unpacked: ${Status}")
		endif()

		file(WRITE "${DownloadDirectory}/download/complete" "")
	endif()
endfunction()

function(BuildBoost Name DownloadDirectory DownloadName Icu4cInstallDirectory
	InstallDirectoryVariable
)
	set(BuildDirectory "${DownloadDirectory}/build/${Name}")

	if(NOT EXISTS "${BuildDirectory}/complete")
		message(STATUS "Configuring Boost")
		set(BootstrapCommand ./bootstrap.sh)
		if(WIN32)
			set(BootstrapCommand bootstrap.bat)
		endif()
		execute_process(
			COMMAND ${BootstrapCommand}
			WORKING_DIRECTORY "${DownloadDirectory}/download/${DownloadName}"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "Boost could not be configured: ${Status}")
		endif()

		message(STATUS "Building and Installing Boost")
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
			COMMAND ${BuildCommand} boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off boost.locale.winapi=off boost.locale.posix=off ${DefineOption} -sICU_PATH="${Icu4cInstallDirectory}" --build-dir=${BuildDirectory}/make --prefix=${BuildDirectory}/install ${HashOption} --with-locale --with-system --with-thread --with-test link=static ${AddressModelOption} ${LinkFlagsOption} install
			WORKING_DIRECTORY "${DownloadDirectory}/download/${DownloadName}"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "Boost could not be built and/or installed: ${Status}")
		endif()

		file(WRITE "${BuildDirectory}/complete" "")
	endif()

	get_filename_component(InstallDirectory "${BuildDirectory}/install" REALPATH)
	set(${InstallDirectoryVariable} ${InstallDirectory} PARENT_SCOPE)
endfunction()

function(SetUpBoost BuildsDirectory Platform Icu4cInstallDirectory
	IncludeDirectoryVariable
	PrgExecMonitorDebugLibraryVariable PrgExecMonitorReleaseLibraryVariable
	TestExecMonitorDebugLibraryVariable TestExecMonitorReleaseLibraryVariable
	UnitTestFrameworkDebugLibraryVariable UnitTestFrameworkReleaseLibraryVariable
	LocaleDebugLibraryVariable LocaleReleaseLibraryVariable
	SystemDebugLibraryVariable SystemReleaseLibraryVariable
	ThreadDebugLibraryVariable ThreadReleaseLibraryVariable
)
	set(MajorVersion 1)
	set(MinorVersion 73)
	if(WIN32)
		set(Extension zip)
		set(Sha256 0909a79524f857ef54570ceef8f397cc0629202532cc997785479c7c08bbc2a4)
	else()
		set(Extension tar.gz)
		set(Sha256 9995e192e68528793755692917f9eb6422f3052a53c5e13ba278a228af6c7acf)
	endif()

	set(InstallDirectory "${BoostInstallDirectory}")
	if(NOT EXISTS "${InstallDirectory}")
		set(BuildDirectoryDefault "${BuildsDirectory}/Boost")
		set(BuildDirectoryCaption "The Boost build path")
		set(BoostBuildDirectory "${BuildDirectoryDefault}" CACHE PATH "${BuildDirectoryCaption}")

		execute_process(
			COMMAND "${CMAKE_COMMAND}" -E make_directory "${BoostBuildDirectory}"
			WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "The directory \"${BoostBuildDirectory}\" could not be created: ${Status}")
		endif()

		GetBoost("${BoostBuildDirectory}" "${Platform}" "${MajorVersion}" "${MinorVersion}" "${Extension}" "${Sha256}" DownloadDirectory DownloadName)
		BuildBoost("${Platform}" "${DownloadDirectory}" "${DownloadName}" "${Icu4cInstallDirectory}" InstallDirectory)
	endif()

	if(WIN32)
		set(MsvcVersion "${MSVC_TOOLSET_VERSION}")
		set(Suffix -${MajorVersion}_${MinorVersion})
		set(Prefix lib)
		if(CMAKE_CL_64)
			set(Architecture -x64)
		endif()
		set(DebugSuffix -vc${MsvcVersion}-mt-gd${Architecture}${Suffix})
		set(ReleaseSuffix -vc${MsvcVersion}-mt${Architecture}${Suffix})

		set(${IncludeDirectoryVariable} "${InstallDirectory}/include/boost${Suffix}" PARENT_SCOPE)
	else()
		set(${IncludeDirectoryVariable} "${InstallDirectory}/include" PARENT_SCOPE)
	endif()

	find_library(PrgExecMonitorDebugLibrary ${Prefix}boost_prg_exec_monitor${DebugSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(PrgExecMonitorReleaseLibrary ${Prefix}boost_prg_exec_monitor${ReleaseSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(TestExecMonitorDebugLibrary ${Prefix}boost_test_exec_monitor${DebugSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(TestExecMonitorReleaseLibrary ${Prefix}boost_test_exec_monitor${ReleaseSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(UnitTestFrameworkDebugLibrary ${Prefix}boost_unit_test_framework${DebugSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(UnitTestFrameworkReleaseLibrary ${Prefix}boost_unit_test_framework${ReleaseSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(LocaleDebugLibrary ${Prefix}boost_locale${DebugSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(LocaleReleaseLibrary ${Prefix}boost_locale${ReleaseSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(SystemDebugLibrary ${Prefix}boost_system${DebugSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(SystemReleaseLibrary ${Prefix}boost_system${ReleaseSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(ThreadDebugLibrary ${Prefix}boost_thread${DebugSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(ThreadReleaseLibrary ${Prefix}boost_thread${ReleaseSuffix} "${InstallDirectory}/lib" NO_DEFAULT_PATH)

	set(${PrgExecMonitorDebugLibraryVariable} "${PrgExecMonitorDebugLibrary}" PARENT_SCOPE)
	set(${PrgExecMonitorReleaseLibraryVariable} "${PrgExecMonitorReleaseLibrary}" PARENT_SCOPE)
	set(${TestExecMonitorDebugLibraryVariable} "${TestExecMonitorDebugLibrary}" PARENT_SCOPE)
	set(${TestExecMonitorReleaseLibraryVariable} "${TestExecMonitorReleaseLibrary}" PARENT_SCOPE)
	set(${UnitTestFrameworkDebugLibraryVariable} "${UnitTestFrameworkDebugLibrary}" PARENT_SCOPE)
	set(${UnitTestFrameworkReleaseLibraryVariable} "${UnitTestFrameworkReleaseLibrary}" PARENT_SCOPE)
	set(${LocaleDebugLibraryVariable} "${LocaleDebugLibrary}" PARENT_SCOPE)
	set(${LocaleReleaseLibraryVariable} "${LocaleReleaseLibrary}" PARENT_SCOPE)
	set(${SystemDebugLibraryVariable} "${SystemDebugLibrary}" PARENT_SCOPE)
	set(${SystemReleaseLibraryVariable} "${SystemReleaseLibrary}" PARENT_SCOPE)
	set(${ThreadDebugLibraryVariable} "${ThreadDebugLibrary}" PARENT_SCOPE)
	set(${ThreadReleaseLibraryVariable} "${ThreadReleaseLibrary}" PARENT_SCOPE)
endfunction()
