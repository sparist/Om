cmake_minimum_required(VERSION 2.8.10)

project(Om)

# Prevent implicit CMake calls on project modification
set(CMAKE_SUPPRESS_REGENERATION TRUE)

# Set global compilation flags
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

# Set global definitions
if(MSVC)
	add_definitions(-DU_STATIC_IMPLEMENTATION=1) # For ICU
else()
	add_definitions(-DU_CHARSET_IS_UTF8=1) # For ICU
endif()

# Set generate command for external dependencies
if(MSVC)
	set(GenerateCommand generate.bat)
else()
	set(GenerateCommand ./generate.sh)
endif()

# Set ICU directory path, downloading and building as necessary
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

# Set Boost directory path, downloading and building as necessary
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

# Set dependency library paths
if(MSVC)
	# Determine MSVC version string used in Boost library names
	set(MsvcVersionMinimum 1600)
	set(MsvcVersion ${MSVC_VERSION})
	if(${MsvcVersion} LESS ${MsvcVersionMinimum})
		set(MsvcVersion ${MsvcVersionMinimum})
	endif()
	math(EXPR BoostMsvcVersion "((${MsvcVersion} - 600) / 10)") # Only works for Visual Studio 7.1 and higher

	find_library(BoostPrgExecMonitorDebugLibrary libboost_prg_exec_monitor-vc${BoostMsvcVersion}-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostPrgExecMonitorReleaseLibrary libboost_prg_exec_monitor-vc${BoostMsvcVersion}-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostTestExecMonitorDebugLibrary libboost_test_exec_monitor-vc${BoostMsvcVersion}-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostTestExecMonitorReleaseLibrary libboost_test_exec_monitor-vc${BoostMsvcVersion}-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostUnitTestFrameworkDebugLibrary libboost_unit_test_framework-vc${BoostMsvcVersion}-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostUnitTestFrameworkReleaseLibrary libboost_unit_test_framework-vc${BoostMsvcVersion}-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostLocaleDebugLibrary libboost_locale-vc${BoostMsvcVersion}-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostLocaleReleaseLibrary libboost_locale-vc${BoostMsvcVersion}-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostSystemDebugLibrary libboost_system-vc${BoostMsvcVersion}-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostSystemReleaseLibrary libboost_system-vc${BoostMsvcVersion}-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostThreadDebugLibrary libboost_thread-vc${BoostMsvcVersion}-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostThreadReleaseLibrary libboost_thread-vc${BoostMsvcVersion}-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(IcuDataDebugLibrary sicudtd "${Icu}/lib" NO_DEFAULT_PATH)
	find_library(IcuDataReleaseLibrary sicudt "${Icu}/lib" NO_DEFAULT_PATH)

	find_library(IcuI18nDebugLibrary sicuind "${Icu}/lib" NO_DEFAULT_PATH)
	find_library(IcuI18nReleaseLibrary sicuin "${Icu}/lib" NO_DEFAULT_PATH)

	find_library(IcuIoDebugLibrary sicuiod "${Icu}/lib" NO_DEFAULT_PATH)
	find_library(IcuIoReleaseLibrary sicuio "${Icu}/lib" NO_DEFAULT_PATH)

	find_library(IcuLeDebugLibrary siculed "${Icu}/lib" NO_DEFAULT_PATH)
	find_library(IcuLeReleaseLibrary sicule "${Icu}/lib" NO_DEFAULT_PATH)

	find_library(IcuLxDebugLibrary siculxd "${Icu}/lib" NO_DEFAULT_PATH)
	find_library(IcuLxReleaseLibrary siculx "${Icu}/lib" NO_DEFAULT_PATH)

	find_library(IcuTestDebugLibrary sicutestd "${Icu}/lib" NO_DEFAULT_PATH)
	find_library(IcuTestReleaseLibrary sicutest "${Icu}/lib" NO_DEFAULT_PATH)

	find_library(IcuTuDebugLibrary sicutud "${Icu}/lib" NO_DEFAULT_PATH)
	find_library(IcuTuReleaseLibrary sicutu "${Icu}/lib" NO_DEFAULT_PATH)

	find_library(IcuUcDebugLibrary sicuucd "${Icu}/lib" NO_DEFAULT_PATH)
	find_library(IcuUcReleaseLibrary sicuuc "${Icu}/lib" NO_DEFAULT_PATH)
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

	find_library(IcuDataReleaseLibrary icudata "${Icu}/lib" NO_DEFAULT_PATH)
	set(IcuDataDebugLibrary ${IcuDataReleaseLibrary})

	find_library(IcuI18nReleaseLibrary icui18n "${Icu}/lib" NO_DEFAULT_PATH)
	set(IcuI18nDebugLibrary ${IcuI18nReleaseLibrary})

	find_library(IcuIoReleaseLibrary icuio "${Icu}/lib" NO_DEFAULT_PATH)
	set(IcuIoDebugLibrary ${IcuIoReleaseLibrary})

	find_library(IcuLeReleaseLibrary icule "${Icu}/lib" NO_DEFAULT_PATH)
	set(IcuLeDebugLibrary ${IcuLeReleaseLibrary})

	find_library(IcuLxReleaseLibrary iculx "${Icu}/lib" NO_DEFAULT_PATH)
	set(IcuLxDebugLibrary ${IcuLxReleaseLibrary})

	find_library(IcuTestReleaseLibrary icutest "${Icu}/lib" NO_DEFAULT_PATH)
	set(IcuTestDebugLibrary ${IcuTestReleaseLibrary})

	find_library(IcuTuReleaseLibrary icutu "${Icu}/lib" NO_DEFAULT_PATH)
	set(IcuTuDebugLibrary ${IcuTuReleaseLibrary})

	find_library(IcuUcReleaseLibrary icuuc "${Icu}/lib" NO_DEFAULT_PATH)
	set(IcuUcDebugLibrary ${IcuUcReleaseLibrary})
endif()

# Configure include paths
if(MSVC)
	include_directories(SYSTEM "${Boost}/include/boost-1_53")
else()
	include_directories(SYSTEM "${Boost}/include")
endif()
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/input/code")

# Get sorted list of unique directories
file(GLOB_RECURSE Files "${CMAKE_CURRENT_SOURCE_DIR}/input/code/*.*")
foreach(File ${Files})
	get_filename_component(Directory "${File}" PATH)
	list(APPEND Directories "${Directory}")
endforeach()
list(REMOVE_DUPLICATES Directories)
list(SORT Directories)

# Add each directory as a source group
foreach(Directory ${Directories})
	file(RELATIVE_PATH RelativeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/input/code" "${Directory}")
	string(REPLACE "/" "\\" SourceGroup "${RelativeDirectory}")

	file(GLOB LocalCppFiles "${Directory}/*.cpp")
	list(SORT LocalCppFiles)
	source_group("Source Files\\${SourceGroup}" FILES ${LocalCppFiles})
	set(CppFiles ${CppFiles} ${LocalCppFiles})

	file(GLOB LocalHppFiles "${Directory}/*.hpp")
	list(SORT LocalHppFiles)
	source_group("Header Files\\${SourceGroup}" FILES ${LocalHppFiles})
	set(HppFiles ${HppFiles} ${LocalHppFiles})

	file(GLOB LocalDoxFiles "${Directory}/*.dox")
	list(SORT LocalDoxFiles)
	source_group("Doxygen Files\\${SourceGroup}" FILES ${LocalDoxFiles})
	set(DoxFiles ${DoxFiles} ${LocalDoxFiles})
endforeach()

# Add executable targets
add_executable("Om" ${CppFiles} ${HppFiles})
add_executable("Om.Test" ${CppFiles})

# Add documentation target
if(MSVC)
	set(DoxygenCommand (type ..\\documentation\\Doxyfile && echo WARN_FORMAT = "$file($line): $text") | doxygen -)
else()
	set(DoxygenCommand doxygen ../documentation/Doxyfile)
endif()
add_custom_target("Om.Documentation"
	COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/output/artifacts/Doxygen"
	COMMAND ${DoxygenCommand}
	COMMENT "Generating Documentation..."
	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input/code"
	SOURCES ${DoxFiles}
)

# om.internal: Populate with complete sorted list of unique headers
set(InternalHeader "${CMAKE_CURRENT_SOURCE_DIR}/input/code/om.internal")
file(WRITE "${InternalHeader}" "")
foreach(HeaderFile ${HppFiles})
	file(RELATIVE_PATH RelativeHeaderFile "${CMAKE_CURRENT_SOURCE_DIR}/input/code" "${HeaderFile}")
	file(APPEND "${InternalHeader}" "#include \"${RelativeHeaderFile}\"\n")
endforeach()

# om.external: Configure for precompilation
if(APPLE)
	add_definitions(-DOm_Macros_Precompilation_)

	set_target_properties("Om" "Om.Test"
		PROPERTIES
			XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/input/code/om.external"
			XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES"
	)
endif()

# Configure executable targets
function(om_configure_executable target)
	# Link Boost
	target_link_libraries(${target}
		debug "${BoostLocaleDebugLibrary}"
		optimized "${BoostLocaleReleaseLibrary}"

		debug "${BoostSystemDebugLibrary}"
		optimized "${BoostSystemReleaseLibrary}"

		debug "${BoostThreadDebugLibrary}"
		optimized "${BoostThreadReleaseLibrary}"
	)

	# Link ICU
	target_link_libraries(${target}
		debug "${IcuDataDebugLibrary}"
		optimized "${IcuDataReleaseLibrary}"

		debug "${IcuI18nDebugLibrary}"
		optimized "${IcuI18nReleaseLibrary}"

		debug "${IcuIoDebugLibrary}"
		optimized "${IcuIoReleaseLibrary}"

		debug "${IcuLeDebugLibrary}"
		optimized "${IcuLeReleaseLibrary}"

		debug "${IcuLxDebugLibrary}"
		optimized "${IcuLxReleaseLibrary}"

		debug "${IcuTestDebugLibrary}"
		optimized "${IcuTestReleaseLibrary}"

		debug "${IcuTuDebugLibrary}"
		optimized "${IcuTuReleaseLibrary}"

		debug "${IcuUcDebugLibrary}"
		optimized "${IcuUcReleaseLibrary}"
	)

	# Add post-build event that copies artifacts
	add_custom_command(
		TARGET ${target}
		POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:${target}> "${CMAKE_CURRENT_SOURCE_DIR}/output/artifacts/${CMAKE_GENERATOR}/$<CONFIGURATION>/$<TARGET_FILE_NAME:${target}>"
		COMMENT Generating ${target} artifacts...
		VERBATIM
	)
endfunction()
om_configure_executable("Om")
om_configure_executable("Om.Test")

# Link Boost.Test libraries
target_link_libraries("Om.Test"
	debug "${BoostPrgExecMonitorDebugLibrary}"
	optimized "${BoostPrgExecMonitorReleaseLibrary}"

	debug "${BoostTestExecMonitorDebugLibrary}"
	optimized "${BoostTestExecMonitorReleaseLibrary}"

	debug "${BoostUnitTestFrameworkDebugLibrary}"
	optimized "${BoostUnitTestFrameworkReleaseLibrary}"
)

# Configure Om.Test
set(OmTestCompileFlags "-DOm_Macros_Test_ -DBOOST_TEST_ALTERNATIVE_INIT_API")
set(OmTestLinkFlags "")
if(NOT MSVC)
	# Disable warnings generated by Boost.Test
	set(OmTestCompileFlags "${OmTestCompileFlags} -Wno-format-nonliteral")
	set(OmTestCompileFlags "${OmTestCompileFlags} -Wno-unneeded-internal-declaration")
	set(OmTestCompileFlags "${OmTestCompileFlags} -Wno-unused-variable")

	# Analyze test coverage
	set(OmTestCompileFlags "${OmTestCompileFlags} -fprofile-arcs -ftest-coverage")
	set(OmTestLinkFlags "${OmTestLinkFlags} -fprofile-arcs -ftest-coverage")

	# Add pre-build event that cleans profiler information
	add_custom_command(
		TARGET "Om.Test"
		PRE_BUILD
		COMMAND rm -f "\${OBJECT_FILE_DIR_normal}/\${CURRENT_ARCH}/*.gcda"
		COMMENT Cleaning profiler information...
	)
endif()
set_target_properties("Om.Test" PROPERTIES COMPILE_FLAGS "${OmTestCompileFlags}")
set_target_properties("Om.Test" PROPERTIES LINK_FLAGS "${OmTestLinkFlags}")

# Add RUN_TESTS target
enable_testing()
add_test("Om.Test.Build" "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target "Om.Test")
add_test("Om.Test.Run" "Om.Test")
set_tests_properties("Om.Test.Run" PROPERTIES DEPENDS "Om.Test.Build")
