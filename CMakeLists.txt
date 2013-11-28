cmake_minimum_required(VERSION 2.8.7)

project(Om)

# Prevent implicit CMake calls on project modification.
set(CMAKE_SUPPRESS_REGENERATION TRUE)

# Set a default build type if none was specified.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to 'Debug' as none was specified.")
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

	# Set the possible values of build type for cmake-gui.
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Set global compilation flags.
if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX /wd4355 /wd4505 /wd4706 /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS /EHa")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wcast-align -Wcast-qual -Wdisabled-optimization -Wempty-body -Werror -Wfloat-equal -Wformat=2 -Winit-self -Winline -Winvalid-pch -Wmissing-field-initializers -Wmissing-format-attribute -Woverlength-strings -Wpacked -Wpointer-arith -Wredundant-decls -Wvariadic-macros")
endif()

# Set global definitions.
if(WIN32)
	add_definitions(-DU_STATIC_IMPLEMENTATION=1) # For ICU4C
elseif(UNIX)
	add_definitions(-DU_CHARSET_IS_UTF8=1) # For ICU4C
endif()

# Set main directories.
set(Build "${CMAKE_BINARY_DIR}/../..")
set(Builds "${Build}/..")

# Set name for build folders, based on OS and compiler.
if(CMAKE_CL_64)
	set(PlatformBits -64)
endif()
set(Platform "${CMAKE_SYSTEM}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}${PlatformBits}")

# Set up ICU4C.
# Note that ICU4C does not support spaces in the path.
get_filename_component(Icu4cBuildDefault "${Builds}/Icu4c" REALPATH)
set(Icu4cBuildCaption "The ICU4C build path")
set(Icu4cBuild "${Icu4cBuildDefault}" CACHE PATH "${Icu4cBuildCaption}")
set(Icu4cMajorVersion 52)
set(Icu4cMinorVersion 1)
set(Icu4cExtension tgz)
set(Icu4cMd5 9e96ed4c1d99c0d14ac03c140f9f346c)
set(Icu4cInstallDefault "${Icu4cBuild}/${Icu4cMd5}/build/${Platform}/install")
set(Icu4cInstallCaption "The ICU4C install path")
set(Icu4cInstall "${Icu4cInstallDefault}" CACHE PATH "${Icu4cInstallCaption}")
if(NOT EXISTS "${Icu4cInstall}")
	set(Icu4cBuild "${Icu4cBuildDefault}" CACHE PATH "${Icu4cBuildCaption}" FORCE)

	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${Icu4cBuild}"
		WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "The directory \"${Icu4cBuild}\" could not be created: ${Status}")
	endif()

	execute_process(
		COMMAND "${CMAKE_COMMAND}" -D Name=${Platform} -D MajorVersion=${Icu4cMajorVersion} -D MinorVersion=${Icu4cMinorVersion} -D Extension=${Icu4cExtension} -D Md5=${Icu4cMd5} -P "${CMAKE_SOURCE_DIR}/dependencies/Icu4c/build.cmake"
		WORKING_DIRECTORY "${Icu4cBuild}"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "ICU4C is unavailable.")
	endif()
endif()
get_filename_component(Icu4cInstall "${Icu4cInstall}" REALPATH)
set(Icu4cInstall "${Icu4cInstall}" CACHE PATH "${Icu4cInstallCaption}" FORCE)
if(WIN32)
	find_library(Icu4cI18nDebugLibrary sicuind "${Icu4cInstall}/lib" NO_DEFAULT_PATH)
	find_library(Icu4cI18nReleaseLibrary sicuin "${Icu4cInstall}/lib" NO_DEFAULT_PATH)

	find_library(Icu4cUcDebugLibrary sicuucd "${Icu4cInstall}/lib" NO_DEFAULT_PATH)
	find_library(Icu4cUcReleaseLibrary sicuuc "${Icu4cInstall}/lib" NO_DEFAULT_PATH)

	find_library(Icu4cDataDebugLibrary sicudtd "${Icu4cInstall}/lib" NO_DEFAULT_PATH)
	find_library(Icu4cDataReleaseLibrary sicudt "${Icu4cInstall}/lib" NO_DEFAULT_PATH)
else()
	find_library(Icu4cI18nReleaseLibrary icui18n "${Icu4cInstall}/lib" NO_DEFAULT_PATH)
	set(Icu4cI18nDebugLibrary ${Icu4cI18nReleaseLibrary})

	find_library(Icu4cUcReleaseLibrary icuuc "${Icu4cInstall}/lib" NO_DEFAULT_PATH)
	set(Icu4cUcDebugLibrary ${Icu4cUcReleaseLibrary})

	find_library(Icu4cDataReleaseLibrary icudata "${Icu4cInstall}/lib" NO_DEFAULT_PATH)
	set(Icu4cDataDebugLibrary ${Icu4cDataReleaseLibrary})
endif()

# Set up Boost.
get_filename_component(BoostBuildDefault "${Builds}/Boost" REALPATH)
set(BoostBuildCaption "The Boost build path")
set(BoostBuild "${BoostBuildDefault}" CACHE PATH "${BoostBuildCaption}")
set(BoostMajorVersion 1)
set(BoostMinorVersion 55)
if(WIN32)
	set(BoostExtension zip)
	set(BoostMd5 8aca361a4713a1f491b0a5e33fee0f1f)
else()
	set(BoostExtension tar.gz)
	set(BoostMd5 93780777cfbf999a600f62883bd54b17)
endif()
set(BoostInstallDefault "${BoostBuild}/${BoostMd5}/build/${Platform}/install")
set(BoostInstallCaption "The Boost install path")
set(BoostInstall "${BoostInstallDefault}" CACHE PATH "${BoostInstallCaption}")
if(NOT EXISTS "${BoostInstall}")
	set(BoostBuild "${BoostBuildDefault}" CACHE PATH "${BoostBuildCaption}" FORCE)

	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${BoostBuild}"
		WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "The directory \"${BoostBuild}\" could not be created: ${Status}")
	endif()

	execute_process(
		COMMAND "${CMAKE_COMMAND}" -D Name=${Platform} -D MajorVersion=${BoostMajorVersion} -D MinorVersion=${BoostMinorVersion} -D Extension=${BoostExtension} -D Md5=${BoostMd5} -D Icu4c=${Icu4cInstall} -P "${CMAKE_SOURCE_DIR}/dependencies/Boost/build.cmake"
		WORKING_DIRECTORY "${BoostBuild}"
		RESULT_VARIABLE Status
	)
	if(NOT ${Status} EQUAL 0)
		message(FATAL_ERROR "Boost is unavailable.")
	endif()
endif()
get_filename_component(BoostInstall "${BoostInstall}" REALPATH)
set(BoostInstall "${BoostInstall}" CACHE PATH "${BoostInstallCaption}" FORCE)
if(WIN32)
	# Determine MSVC version string used in Boost library names.
	# From: http://www.cmake.org/pipermail/cmake/2012-March/049464.html
	set(MsvcVersionMinimum 1600) # Visual Studio 2010
	set(MsvcVersion ${MSVC_VERSION})
	if(${MsvcVersion} LESS ${MsvcVersionMinimum})
		set(MsvcVersion ${MsvcVersionMinimum})
	endif()
	math(EXPR BoostMsvcVersion "((${MsvcVersion} - 600) / 10)") # Only works for Visual Studio 7.1 and higher

	set(BoostSuffix -${BoostMajorVersion}_${BoostMinorVersion})
	set(BoostDebugSuffix -vc${BoostMsvcVersion}-mt-gd${BoostSuffix})
	set(BoostReleaseSuffix -vc${BoostMsvcVersion}-mt${BoostSuffix})

	find_library(BoostPrgExecMonitorDebugLibrary libboost_prg_exec_monitor${BoostDebugSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)
	find_library(BoostPrgExecMonitorReleaseLibrary libboost_prg_exec_monitor${BoostReleaseSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)

	find_library(BoostTestExecMonitorDebugLibrary libboost_test_exec_monitor${BoostDebugSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)
	find_library(BoostTestExecMonitorReleaseLibrary libboost_test_exec_monitor${BoostReleaseSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)

	find_library(BoostUnitTestFrameworkDebugLibrary libboost_unit_test_framework${BoostDebugSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)
	find_library(BoostUnitTestFrameworkReleaseLibrary libboost_unit_test_framework${BoostReleaseSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)

	find_library(BoostLocaleDebugLibrary libboost_locale${BoostDebugSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)
	find_library(BoostLocaleReleaseLibrary libboost_locale${BoostReleaseSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)

	find_library(BoostSystemDebugLibrary libboost_system${BoostDebugSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)
	find_library(BoostSystemReleaseLibrary libboost_system${BoostReleaseSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)

	find_library(BoostThreadDebugLibrary libboost_thread${BoostDebugSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)
	find_library(BoostThreadReleaseLibrary libboost_thread${BoostReleaseSuffix} "${BoostInstall}/lib" NO_DEFAULT_PATH)

	set(SystemIncludeDirectories "${BoostInstall}/include/boost${BoostSuffix}")
else()
	find_library(BoostPrgExecMonitorReleaseLibrary boost_prg_exec_monitor "${BoostInstall}/lib" NO_DEFAULT_PATH)
	set(BoostPrgExecMonitorDebugLibrary ${BoostPrgExecMonitorReleaseLibrary})

	find_library(BoostTestExecMonitorReleaseLibrary boost_test_exec_monitor "${BoostInstall}/lib" NO_DEFAULT_PATH)
	set(BoostTestExecMonitorDebugLibrary ${BoostTestExecMonitorReleaseLibrary})

	find_library(BoostUnitTestFrameworkReleaseLibrary boost_unit_test_framework "${BoostInstall}/lib" NO_DEFAULT_PATH)
	set(BoostUnitTestFrameworkDebugLibrary ${BoostUnitTestFrameworkReleaseLibrary})

	find_library(BoostLocaleReleaseLibrary boost_locale "${BoostInstall}/lib" NO_DEFAULT_PATH)
	set(BoostLocaleDebugLibrary ${BoostLocaleReleaseLibrary})

	find_library(BoostSystemReleaseLibrary boost_system "${BoostInstall}/lib" NO_DEFAULT_PATH)
	set(BoostSystemDebugLibrary ${BoostSystemReleaseLibrary})

	find_library(BoostThreadReleaseLibrary boost_thread "${BoostInstall}/lib" NO_DEFAULT_PATH)
	set(BoostThreadDebugLibrary ${BoostThreadReleaseLibrary})

	set(SystemIncludeDirectories "${BoostInstall}/include")
endif()

# Configure include paths.
include_directories(SYSTEM ${SystemIncludeDirectories})
include_directories("${CMAKE_SOURCE_DIR}/code")

# Add each directory as a source group (sorted).
file(GLOB_RECURSE Files "${CMAKE_SOURCE_DIR}/code/*.*")
foreach(File ${Files})
	get_filename_component(Directory "${File}" PATH)
	list(APPEND Directories "${Directory}")
endforeach()
list(REMOVE_DUPLICATES Directories)
list(SORT Directories)
foreach(Directory ${Directories})
	file(RELATIVE_PATH RelativeDirectory "${CMAKE_SOURCE_DIR}/code" "${Directory}")
	string(REPLACE "/" "\\" SourceGroup "${RelativeDirectory}")

	file(GLOB DirectoryCppFiles "${Directory}/*.cpp")
	list(SORT DirectoryCppFiles)
	source_group("Source Files\\${SourceGroup}" FILES ${DirectoryCppFiles})
	set(CppFiles ${CppFiles} ${DirectoryCppFiles})

	file(GLOB DirectoryHppFiles "${Directory}/*.hpp")
	list(SORT DirectoryHppFiles)
	source_group("Header Files\\${SourceGroup}" FILES ${DirectoryHppFiles})
	set(HppFiles ${HppFiles} ${DirectoryHppFiles})

	file(GLOB DirectoryDoxFiles "${Directory}/*.dox")
	list(SORT DirectoryDoxFiles)
	source_group("Doxygen Files\\${SourceGroup}" FILES ${DirectoryDoxFiles})
	set(DoxFiles ${DoxFiles} ${DirectoryDoxFiles})
endforeach()

# Add executable targets.
add_executable("Om.Interpreter" ${CppFiles} ${HppFiles})
add_executable("Om.Test" ${CppFiles})

# Add documentation target.
if(WIN32)
	set(DoxygenCommand ( type ..\\documentation\\Doxyfile && echo OUTPUT_DIRECTORY = "${Build}/documentation" && echo WARN_FORMAT = "$file($line): $text" ) | doxygen -)
else()
	set(DoxygenCommand eval "( cat ../documentation/Doxyfile && echo OUTPUT_DIRECTORY = \\\"${Build}/documentation\\\" ) | doxygen -")
endif()
add_custom_target("Om.Documentation" ALL
	COMMAND "${CMAKE_COMMAND}" -E make_directory "${Build}/documentation"
	COMMAND ${DoxygenCommand}
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/code"
	COMMENT "Generating documentation..."
	VERBATIM
	SOURCES ${DoxFiles}
)

# "om.internal": Populate with complete sorted list of unique headers.
set(Internal "${CMAKE_SOURCE_DIR}/code/om.internal")
file(WRITE "${Internal}" "")
foreach(HppFile ${HppFiles})
	file(RELATIVE_PATH RelativeHppFile "${CMAKE_SOURCE_DIR}/code" "${HppFile}")
	file(APPEND "${Internal}" "#include \"${RelativeHppFile}\"\n")
endforeach()

# "om.external": Configure for precompilation.
if("${CMAKE_GENERATOR}" STREQUAL Xcode)
	add_definitions(-DOm_Macro_Precompilation_)

	set_target_properties("Om.Interpreter" "Om.Test"
		PROPERTIES
			XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${CMAKE_SOURCE_DIR}/code/om.external"
			XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES"
	)
endif()

# Configure executable targets.
function(ConfigureExecutable Target)
	# Link Boost.
	target_link_libraries(${Target}
		debug "${BoostLocaleDebugLibrary}"
		optimized "${BoostLocaleReleaseLibrary}"

		debug "${BoostSystemDebugLibrary}"
		optimized "${BoostSystemReleaseLibrary}"

		debug "${BoostThreadDebugLibrary}"
		optimized "${BoostThreadReleaseLibrary}"
	)

	# Link ICU4C.
	target_link_libraries(${Target}
		debug "${Icu4cI18nDebugLibrary}"
		optimized "${Icu4cI18nReleaseLibrary}"

		debug "${Icu4cUcDebugLibrary}"
		optimized "${Icu4cUcReleaseLibrary}"

		debug "${Icu4cDataDebugLibrary}"
		optimized "${Icu4cDataReleaseLibrary}"
	)

	# Link additional libraries required on Linux.
	if(UNIX AND NOT APPLE)
		target_link_libraries(${Target} pthread rt dl)
	endif()

	# Add post-build event that copies executables.
	add_custom_command(
		TARGET ${Target}
		POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:${Target}> "${Build}/executables/${Platform}/$<CONFIGURATION>/$<TARGET_FILE_NAME:${Target}>"
		COMMENT "Generating ${Target} executables..."
		VERBATIM
	)
endfunction()
ConfigureExecutable("Om.Interpreter")
ConfigureExecutable("Om.Test")

# Link Boost.Test libraries.
target_link_libraries("Om.Test"
	debug "${BoostPrgExecMonitorDebugLibrary}"
	optimized "${BoostPrgExecMonitorReleaseLibrary}"

	debug "${BoostTestExecMonitorDebugLibrary}"
	optimized "${BoostTestExecMonitorReleaseLibrary}"

	debug "${BoostUnitTestFrameworkDebugLibrary}"
	optimized "${BoostUnitTestFrameworkReleaseLibrary}"
)

# Configure Om.Test.
set(TestCompileFlags "-DOm_Macro_Test_ -DBOOST_TEST_ALTERNATIVE_INIT_API")
set(TestLinkFlags "")
if(NOT WIN32)
	# Disable warnings generated by Boost.Test.
	set(TestCompileFlags "${TestCompileFlags} -Wno-format-nonliteral -Wno-unneeded-internal-declaration")

	# Analyze test coverage.
	set(TestCompileFlags "${TestCompileFlags} -fprofile-arcs -ftest-coverage")
	set(TestLinkFlags "${TestLinkFlags} -fprofile-arcs -ftest-coverage")

	# Add pre-build event that cleans profiler information.
	add_custom_command(
		TARGET "Om.Test"
		PRE_BUILD
		COMMAND rm -f "\${OBJECT_FILE_DIR_normal}/\${CURRENT_ARCH}/*.gcda"
		COMMENT "Cleaning profiler information..."
	)
endif()
set_target_properties("Om.Test" PROPERTIES COMPILE_FLAGS "${TestCompileFlags}")
set_target_properties("Om.Test" PROPERTIES LINK_FLAGS "${TestLinkFlags}")

# Add RUN_TESTS target.
enable_testing()
add_test("Om.Test.Build" "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target "Om.Test")
add_test("Om.Test.Run" "Om.Test")
set_tests_properties("Om.Test.Run" PROPERTIES DEPENDS "Om.Test.Build")
