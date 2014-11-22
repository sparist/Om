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

# Set name for build folders, based on OS and compiler.
if(CMAKE_CL_64)
	set(PlatformBits -64)
endif()
set(Platform "${CMAKE_SYSTEM}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}${PlatformBits}")

# Set builds directory.
set(BuildsDirectory "${CMAKE_BINARY_DIR}" CACHE PATH "The builds directory path")

# Set up ICU4C.
if(WIN32)
	add_definitions(-DU_STATIC_IMPLEMENTATION=1)
elseif(UNIX)
	add_definitions(-DU_CHARSET_IS_UTF8=1)
endif()
include("${CMAKE_SOURCE_DIR}/dependencies/Icu4c/build.cmake")
SetUpIcu4c("${BuildsDirectory}" "${Platform}"
	Icu4cInstallDirectory
	Icu4cI18nDebugLibrary Icu4cI18nReleaseLibrary
	Icu4cUcDebugLibrary Icu4cUcReleaseLibrary
	Icu4cDataDebugLibrary Icu4cDataReleaseLibrary
)

# Set up Boost.
include("${CMAKE_SOURCE_DIR}/dependencies/Boost/build.cmake")
SetUpBoost("${BuildsDirectory}" "${Platform}" "${Icu4cInstallDirectory}"
	SystemIncludeDirectories
	BoostPrgExecMonitorDebugLibrary BoostPrgExecMonitorReleaseLibrary
	BoostTestExecMonitorDebugLibrary BoostTestExecMonitorReleaseLibrary
	BoostUnitTestFrameworkDebugLibrary BoostUnitTestFrameworkReleaseLibrary
	BoostLocaleDebugLibrary BoostLocaleReleaseLibrary
	BoostSystemDebugLibrary BoostSystemReleaseLibrary
	BoostThreadDebugLibrary BoostThreadReleaseLibrary
)

# Set Om build directory.
set(BuildDirectory "${BuildsDirectory}/Om" CACHE PATH "The Om build directory path")

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

	file(GLOB DirectoryHppFiles "${Directory}/*.hpp")
	list(SORT DirectoryHppFiles)
	source_group("Header Files\\${SourceGroup}" FILES ${DirectoryHppFiles})
	set(HppFiles ${HppFiles} ${DirectoryHppFiles})

	file(GLOB DirectoryCppFiles "${Directory}/*.cpp")
	list(SORT DirectoryCppFiles)
	source_group("Source Files\\${SourceGroup}" FILES ${DirectoryCppFiles})
	set(CppFiles ${CppFiles} ${DirectoryCppFiles})
endforeach()

# Add executable targets.
add_executable("Om.Interpreter" ${HppFiles} ${CppFiles})
add_executable("Om.Test" ${CppFiles})

# Add documentation target.
if(WIN32)
	set(DoxygenCommand ( type ..\\documentation\\Doxyfile && echo OUTPUT_DIRECTORY = "${BuildDirectory}/documentation" && echo WARN_FORMAT = "$file($line): $text" ) | doxygen -)
else()
	set(DoxygenCommand PATH=$ENV{PATH} eval "( cat ../documentation/Doxyfile && echo OUTPUT_DIRECTORY = \\\"${BuildDirectory}/documentation\\\" ) | doxygen -")
endif()
add_custom_target("Om.Documentation"
	ALL
	COMMAND "${CMAKE_COMMAND}" -E make_directory "${BuildDirectory}/documentation"
	COMMAND ${DoxygenCommand}
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/code"
	COMMENT "Generating documentation"
	VERBATIM
	SOURCES ${HppFiles} ${CppFiles}
)

# For writing, use Windows line endings to allow for platform consistency
# (since "\n" is interpreted as the native line ending).
if(WIN32)
	set(LineEnding \n)
else()
	set(LineEnding \r\n)
endif()

# "om.internal": Populate with complete sorted list of unique headers.
set(Internal "${CMAKE_SOURCE_DIR}/code/om.internal")
file(WRITE "${Internal}" "")
foreach(HppFile ${HppFiles})
	file(RELATIVE_PATH RelativeHppFile "${CMAKE_SOURCE_DIR}/code" "${HppFile}")
	file(APPEND "${Internal}" "#include \"${RelativeHppFile}\"${LineEnding}")
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
		debug "${BoostLocaleDebugLibrary}" optimized "${BoostLocaleReleaseLibrary}"
		debug "${BoostSystemDebugLibrary}" optimized "${BoostSystemReleaseLibrary}"
		debug "${BoostThreadDebugLibrary}" optimized "${BoostThreadReleaseLibrary}"
	)

	# Link ICU4C.
	target_link_libraries(${Target}
		debug "${Icu4cI18nDebugLibrary}" optimized "${Icu4cI18nReleaseLibrary}"
		debug "${Icu4cUcDebugLibrary}" optimized "${Icu4cUcReleaseLibrary}"
		debug "${Icu4cDataDebugLibrary}" optimized "${Icu4cDataReleaseLibrary}"
	)

	# Link additional libraries required on Linux.
	if(UNIX AND NOT APPLE)
		target_link_libraries(${Target} pthread rt dl)
	endif()

	# Add post-build event that copies executables.
	add_custom_command(
		TARGET ${Target}
		POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:${Target}> "${BuildDirectory}/executables/${Platform}/$<CONFIGURATION>/$<TARGET_FILE_NAME:${Target}>"
		COMMENT "Generating ${Target} executables"
		VERBATIM
	)
endfunction()
ConfigureExecutable("Om.Interpreter")
ConfigureExecutable("Om.Test")

# Link Boost.Test libraries.
target_link_libraries("Om.Test"
	debug "${BoostPrgExecMonitorDebugLibrary}" optimized "${BoostPrgExecMonitorReleaseLibrary}"
	debug "${BoostTestExecMonitorDebugLibrary}" optimized "${BoostTestExecMonitorReleaseLibrary}"
	debug "${BoostUnitTestFrameworkDebugLibrary}" optimized "${BoostUnitTestFrameworkReleaseLibrary}"
)

# Configure Om.Test.
set(TestCompileFlags "-DOm_Macro_Test_ -DBOOST_TEST_ALTERNATIVE_INIT_API")
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
		COMMENT "Cleaning profiler information"
	)
endif()
set_target_properties("Om.Test" PROPERTIES COMPILE_FLAGS "${TestCompileFlags}")
set_target_properties("Om.Test" PROPERTIES LINK_FLAGS "${TestLinkFlags}")

# Add RUN_TESTS target.
enable_testing()
add_test("Om.Test.Build" "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target "Om.Test")
add_test("Om.Test.Run" "Om.Test")
set_tests_properties("Om.Test.Run" PROPERTIES DEPENDS "Om.Test.Build")
