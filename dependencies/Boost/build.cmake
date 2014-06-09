cmake_minimum_required(VERSION 2.8.7)

function(BuildBoost Directory Name MajorVersion MinorVersion Extension Md5 Icu4cInstallDirectory)
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
	get_filename_component(OutputDirectory "${Directory}/${Md5}" REALPATH)

	message(STATUS "Unpacking Boost")
	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E tar xvzf "${Download}.${Extension}"
		WORKING_DIRECTORY "${OutputDirectory}/download"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "Boost could not be unpacked: ${Status}")
	endif()

	message(STATUS "Configuring Boost")
	set(BootstrapCommand ./bootstrap.sh)
	if(WIN32)
		set(BootstrapCommand bootstrap.bat)
	endif()
	execute_process(
		COMMAND ${BootstrapCommand}
		WORKING_DIRECTORY "${OutputDirectory}/download/${Download}"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "Boost could not be configured: ${Status}")
	endif()

	message(STATUS "Building and Installing Boost")
	set(BuildDirectory "${OutputDirectory}/build/${Name}")
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
		WORKING_DIRECTORY "${OutputDirectory}/download/${Download}"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "Boost could not be built and/or installed: ${Status}")
	endif()
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
	if(WIN32)
		set(MinorVersion 55)
		set(Extension zip)
		set(Md5 8aca361a4713a1f491b0a5e33fee0f1f)
	else()
		set(MinorVersion 54)
		set(Extension tar.gz)
		set(Md5 efbfbff5a85a9330951f243d0a46e4b9)
	endif()

	set(BuildDirectoryDefault "${BuildsDirectory}/Boost")
	set(BuildDirectoryCaption "The Boost build path")
	set(BoostBuildDirectory "${BuildDirectoryDefault}" CACHE PATH "${BuildDirectoryCaption}")

	set(InstallDirectoryDefault "${BoostBuildDirectory}/${Md5}/build/${Platform}/install")
	set(InstallDirectoryCaption "The Boost install path")
	set(BoostInstallDirectory "${InstallDirectoryDefault}" CACHE PATH "${InstallDirectoryCaption}")

	if(NOT EXISTS "${BoostInstallDirectory}")
		set(BoostBuildDirectory "${BuildDirectoryDefault}" CACHE PATH "${BuildDirectoryCaption}" FORCE)

		execute_process(
			COMMAND "${CMAKE_COMMAND}" -E make_directory "${BoostBuildDirectory}"
			WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
			RESULT_VARIABLE Status
		)
		if(NOT ${Status} EQUAL 0)
			message(FATAL_ERROR "The directory \"${BoostBuildDirectory}\" could not be created: ${Status}")
		endif()

		BuildBoost("${BoostBuildDirectory}" "${Platform}" ${MajorVersion} ${MinorVersion} ${Extension} ${Md5} "${Icu4cInstallDirectory}")

		get_filename_component(BoostInstallDirectory "${InstallDirectoryDefault}" REALPATH)
		set(BoostInstallDirectory "${BoostInstallDirectory}" CACHE PATH "${InstallDirectoryCaption}" FORCE)
	endif()

	if(WIN32)
		# Determine MSVC version string used in Boost library names.
		# From: http://www.cmake.org/pipermail/cmake/2012-March/049464.html
		set(MsvcVersionMinimum 1600) # Visual Studio 2010
		set(MsvcVersion ${MSVC_VERSION})
		if(${MsvcVersion} LESS ${MsvcVersionMinimum})
			set(MsvcVersion ${MsvcVersionMinimum})
		endif()
		math(EXPR MsvcVersion "((${MsvcVersion} - 600) / 10)") # Only works for Visual Studio 7.1 and higher

		set(Suffix -${MajorVersion}_${MinorVersion})
		set(Prefix lib)
		set(DebugSuffix -vc${MsvcVersion}-mt-gd${Suffix})
		set(ReleaseSuffix -vc${MsvcVersion}-mt${Suffix})

		set(${IncludeDirectoryVariable} "${BoostInstallDirectory}/include/boost${Suffix}" PARENT_SCOPE)
	else()
		set(${IncludeDirectoryVariable} "${BoostInstallDirectory}/include" PARENT_SCOPE)
	endif()

	find_library(PrgExecMonitorDebugLibrary ${Prefix}boost_prg_exec_monitor${DebugSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(PrgExecMonitorReleaseLibrary ${Prefix}boost_prg_exec_monitor${ReleaseSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(TestExecMonitorDebugLibrary ${Prefix}boost_test_exec_monitor${DebugSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(TestExecMonitorReleaseLibrary ${Prefix}boost_test_exec_monitor${ReleaseSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(UnitTestFrameworkDebugLibrary ${Prefix}boost_unit_test_framework${DebugSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(UnitTestFrameworkReleaseLibrary ${Prefix}boost_unit_test_framework${ReleaseSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(LocaleDebugLibrary ${Prefix}boost_locale${DebugSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(LocaleReleaseLibrary ${Prefix}boost_locale${ReleaseSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(SystemDebugLibrary ${Prefix}boost_system${DebugSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(SystemReleaseLibrary ${Prefix}boost_system${ReleaseSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(ThreadDebugLibrary ${Prefix}boost_thread${DebugSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)
	find_library(ThreadReleaseLibrary ${Prefix}boost_thread${ReleaseSuffix} "${BoostInstallDirectory}/lib" NO_DEFAULT_PATH)

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
