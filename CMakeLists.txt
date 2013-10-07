cmake_minimum_required(VERSION 2.8.7)

project(Om)

# Prevent implicit CMake calls on project modification.
set(CMAKE_SUPPRESS_REGENERATION TRUE)

# Set global compilation flags.
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4355")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4505")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4706")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_SCL_SECURE_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdisabled-optimization")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wempty-body")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winline")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winvalid-pch")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-field-initializers")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-format-attribute")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverlength-strings")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpacked")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvariadic-macros")
endif()

# Set global definitions.
if(MSVC)
	add_definitions(-DU_STATIC_IMPLEMENTATION=1) # For ICU
else()
	add_definitions(-DU_CHARSET_IS_UTF8=1) # For ICU
endif()

# Set generate command for external dependencies.
if(MSVC)
	set(GenerateCommand generate.bat)
else()
	set(GenerateCommand ./generate.sh)
endif()

# Set ICU directory path, downloading and building as necessary.
set(IcuDefault "${CMAKE_CURRENT_SOURCE_DIR}/input/dependencies/Icu4c/output/artifacts")
set(IcuCaption "The ICU4C library artifact directory path")
set(Icu ${IcuDefault} CACHE PATH ${IcuCaption})
if(NOT EXISTS "${Icu}")
	message("ICU4C not found. Downloading and building...")
	set(Icu ${IcuDefault} CACHE PATH ${IcuCaption} FORCE)
	execute_process(
		COMMAND "${GenerateCommand}"
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input/dependencies/Icu4c"
	)
endif()

# Set Boost directory path, downloading and building as necessary.
set(BoostDefault "${CMAKE_CURRENT_SOURCE_DIR}/input/dependencies/Boost/output/artifacts")
set(BoostCaption "The Boost library artifact directory path")
set(Boost ${BoostDefault} CACHE PATH ${BoostCaption})
if(NOT EXISTS "${Boost}")
	message("Boost not found. Downloading and building...")
	set(Boost "${BoostDefault}" CACHE PATH ${BoostCaption} FORCE)
	execute_process(
		COMMAND "${GenerateCommand}" "${Icu}"
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input/dependencies/Boost"
	)
endif()

# Set dependency library and include paths.
if(MSVC)
	# Determine MSVC version string used in Boost library names.
	# From: http://www.cmake.org/pipermail/cmake/2012-March/049464.html
	set(MsvcVersionMinimum 1600) # Visual Studio 2010
	set(MsvcVersion ${MSVC_VERSION})
	if(${MsvcVersion} LESS ${MsvcVersionMinimum})
		set(MsvcVersion ${MsvcVersionMinimum})
	endif()
	math(EXPR BoostMsvcVersion "((${MsvcVersion} - 600) / 10)") # Only works for Visual Studio 7.1 and higher

	# Set Boost version for library names.
	set(BoostVersion 1_53)

	find_library(BoostPrgExecMonitorDebugLibrary libboost_prg_exec_monitor-vc${BoostMsvcVersion}-mt-gd-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostPrgExecMonitorReleaseLibrary libboost_prg_exec_monitor-vc${BoostMsvcVersion}-mt-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostTestExecMonitorDebugLibrary libboost_test_exec_monitor-vc${BoostMsvcVersion}-mt-gd-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostTestExecMonitorReleaseLibrary libboost_test_exec_monitor-vc${BoostMsvcVersion}-mt-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostUnitTestFrameworkDebugLibrary libboost_unit_test_framework-vc${BoostMsvcVersion}-mt-gd-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostUnitTestFrameworkReleaseLibrary libboost_unit_test_framework-vc${BoostMsvcVersion}-mt-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostLocaleDebugLibrary libboost_locale-vc${BoostMsvcVersion}-mt-gd-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostLocaleReleaseLibrary libboost_locale-vc${BoostMsvcVersion}-mt-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostSystemDebugLibrary libboost_system-vc${BoostMsvcVersion}-mt-gd-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostSystemReleaseLibrary libboost_system-vc${BoostMsvcVersion}-mt-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostThreadDebugLibrary libboost_thread-vc${BoostMsvcVersion}-mt-gd-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostThreadReleaseLibrary libboost_thread-vc${BoostMsvcVersion}-mt-${BoostVersion} "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(IcuI18nDebugLibrary sicuind "${Icu}/lib" NO_DEFAULT_PATH)
	find_library(IcuI18nReleaseLibrary sicuin "${Icu}/lib" NO_DEFAULT_PATH)

	find_library(IcuUcDebugLibrary sicuucd "${Icu}/lib" NO_DEFAULT_PATH)
	find_library(IcuUcReleaseLibrary sicuuc "${Icu}/lib" NO_DEFAULT_PATH)

	find_library(IcuDataDebugLibrary sicudtd "${Icu}/lib" NO_DEFAULT_PATH)
	find_library(IcuDataReleaseLibrary sicudt "${Icu}/lib" NO_DEFAULT_PATH)

	set(SystemIncludeDirectories "${Boost}/include/boost-${BoostVersion}")
else()
	find_library(BoostPrgExecMonitorReleaseLibrary boost_prg_exec_monitor "${Boost}/lib" NO_DEFAULT_PATH)
	set(BoostPrgExecMonitorDebugLibrary ${BoostPrgExecMonitorReleaseLibrary})

	find_library(BoostTestExecMonitorReleaseLibrary boost_test_exec_monitor "${Boost}/lib" NO_DEFAULT_PATH)
	set(BoostTestExecMonitorDebugLibrary ${BoostTestExecMonitorReleaseLibrary})

	find_library(BoostUnitTestFrameworkReleaseLibrary boost_unit_test_framework "${Boost}/lib" NO_DEFAULT_PATH)
	set(BoostUnitTestFrameworkDebugLibrary ${BoostUnitTestFrameworkReleaseLibrary})

	find_library(BoostLocaleReleaseLibrary boost_locale "${Boost}/lib" NO_DEFAULT_PATH)
	set(BoostLocaleDebugLibrary ${BoostLocaleReleaseLibrary})

	find_library(BoostSystemReleaseLibrary boost_system "${Boost}/lib" NO_DEFAULT_PATH)
	set(BoostSystemDebugLibrary ${BoostSystemReleaseLibrary})

	find_library(BoostThreadReleaseLibrary boost_thread "${Boost}/lib" NO_DEFAULT_PATH)
	set(BoostThreadDebugLibrary ${BoostThreadReleaseLibrary})

	find_library(IcuI18nReleaseLibrary icui18n "${Icu}/lib" NO_DEFAULT_PATH)
	set(IcuI18nDebugLibrary ${IcuI18nReleaseLibrary})

	find_library(IcuUcReleaseLibrary icuuc "${Icu}/lib" NO_DEFAULT_PATH)
	set(IcuUcDebugLibrary ${IcuUcReleaseLibrary})

	find_library(IcuDataReleaseLibrary icudata "${Icu}/lib" NO_DEFAULT_PATH)
	set(IcuDataDebugLibrary ${IcuDataReleaseLibrary})

	set(SystemIncludeDirectories "${Boost}/include")
endif()

# Configure include paths.
include_directories(SYSTEM ${SystemIncludeDirectories})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/input/code")

# Add each directory as a source group (sorted).
file(GLOB_RECURSE Files "${CMAKE_CURRENT_SOURCE_DIR}/input/code/*.*")
foreach(File ${Files})
	get_filename_component(Directory "${File}" PATH)
	list(APPEND Directories "${Directory}")
endforeach()
list(REMOVE_DUPLICATES Directories)
list(SORT Directories)
foreach(Directory ${Directories})
	file(RELATIVE_PATH RelativeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/input/code" "${Directory}")
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
if(MSVC)
	set(DoxygenCommand (type ..\\documentation\\Doxyfile && echo WARN_FORMAT = "$file($line): $text") | doxygen -)
else()
	set(DoxygenCommand doxygen ../documentation/Doxyfile)
endif()
add_custom_target("Om.Documentation" ALL
	COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/output/artifacts/Doxygen"
	COMMAND ${DoxygenCommand}
	COMMENT "Generating Documentation..."
	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input/code"
	SOURCES ${DoxFiles}
)

# "om.internal": Populate with complete sorted list of unique headers.
set(Internal "${CMAKE_CURRENT_SOURCE_DIR}/input/code/om/om.internal")
file(WRITE "${Internal}" "")
foreach(HppFile ${HppFiles})
	file(RELATIVE_PATH RelativeHppFile "${CMAKE_CURRENT_SOURCE_DIR}/input/code" "${HppFile}")
	file(APPEND "${Internal}" "#include \"${RelativeHppFile}\"\n")
endforeach()

# "om.external": Configure for precompilation.
if(APPLE)
	add_definitions(-DOm_Macro_Precompilation_)

	set_target_properties("Om.Interpreter" "Om.Test"
		PROPERTIES
			XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/input/code/om/om.external"
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

	# Link ICU.
	target_link_libraries(${Target}
		debug "${IcuI18nDebugLibrary}"
		optimized "${IcuI18nReleaseLibrary}"

		debug "${IcuUcDebugLibrary}"
		optimized "${IcuUcReleaseLibrary}"

		debug "${IcuDataDebugLibrary}"
		optimized "${IcuDataReleaseLibrary}"
	)

	# Link additional libraries required on Linux.
	if(UNIX AND NOT APPLE)
		target_link_libraries(${Target} pthread rt dl)
	endif()

	# Add post-build event that copies artifacts.
	add_custom_command(
		TARGET ${Target}
		POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:${Target}> "${CMAKE_CURRENT_SOURCE_DIR}/output/artifacts/${CMAKE_GENERATOR}/$<CONFIGURATION>/$<TARGET_FILE_NAME:${Target}>"
		COMMENT Generating ${Target} artifacts...
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
if(NOT MSVC)
	# Disable warnings generated by Boost.Test.
	set(TestCompileFlags "${TestCompileFlags} -Wno-format-nonliteral")
	set(TestCompileFlags "${TestCompileFlags} -Wno-unneeded-internal-declaration")
	set(TestCompileFlags "${TestCompileFlags} -Wno-unused-variable")

	# Analyze test coverage.
	set(TestCompileFlags "${TestCompileFlags} -fprofile-arcs -ftest-coverage")
	set(TestLinkFlags "${TestLinkFlags} -fprofile-arcs -ftest-coverage")

	# Add pre-build event that cleans profiler information.
	add_custom_command(
		TARGET "Om.Test"
		PRE_BUILD
		COMMAND rm -f "\${OBJECT_FILE_DIR_normal}/\${CURRENT_ARCH}/*.gcda"
		COMMENT Cleaning profiler information...
	)
endif()
set_target_properties("Om.Test" PROPERTIES COMPILE_FLAGS "${TestCompileFlags}")
set_target_properties("Om.Test" PROPERTIES LINK_FLAGS "${TestLinkFlags}")

# Add RUN_TESTS target.
enable_testing()
add_test("Om.Test.Build" "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target "Om.Test")
add_test("Om.Test.Run" "Om.Test")
set_tests_properties("Om.Test.Run" PROPERTIES DEPENDS "Om.Test.Build")
