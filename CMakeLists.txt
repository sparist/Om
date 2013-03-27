cmake_minimum_required(VERSION 2.8.10)

project(Om)

# Prevent implicit CMake calls on project modification
set(CMAKE_SUPPRESS_REGENERATION TRUE)

# Global compile flags
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

# Global definitions
if(MSVC)
	add_definitions(-DU_STATIC_IMPLEMENTATION=1) # For ICU
else()
	add_definitions(-DU_CHARSET_IS_UTF8=1) # For ICU
endif()

# Boost path
set(BoostDefault "${CMAKE_CURRENT_SOURCE_DIR}/input/external/output/artifacts/boost")
set(BoostCaption "The Boost library build directory path")
set(Boost "${BoostDefault}" CACHE PATH "${BoostCaption}")
if(NOT EXISTS "${Boost}")
	set(Boost "${BoostDefault}" CACHE PATH "${BoostCaption}" FORCE)
endif()

# ICU path
set(IcuDefault "${CMAKE_CURRENT_SOURCE_DIR}/input/external/output/artifacts/icu4c")
set(IcuCaption "The ICU4C library build directory path")
set(Icu "${IcuDefault}" CACHE PATH "${IcuCaption}")
if(NOT EXISTS "${Icu}")
	set(Icu "${IcuDefault}" CACHE PATH "${IcuCaption}" FORCE)
endif()

# External paths
if((NOT EXISTS "${Boost}") OR (NOT EXISTS "${Icu}"))
	if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input/icu4c")
		file(
			DOWNLOAD "http://download.icu-project.org/files/icu4c/51.1/icu4c-51_1-src.tgz" "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input/icu4c.tgz"
			SHOW_PROGRESS
			EXPECTED_MD5 "6eef33b229d0239d654983028c9c7053"
		)
		execute_process(
			COMMAND "${CMAKE_COMMAND}" -E tar xvzf icu4c.tgz
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input"
		)
		file(RENAME "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input/icu" "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input/icu4c")
	endif()
	if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input/boost")
		if(MSVC)
			file(
				DOWNLOAD "http://sourceforge.net/projects/boost/files/boost/1.53.0/boost_1_53_0.zip/download" "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input/boost.zip"
				SHOW_PROGRESS
				EXPECTED_MD5 "c618e030fd4882e4dbacf54baf824544"
			)
			execute_process(
				COMMAND "${CMAKE_COMMAND}" -E tar xvzf boost.zip
				WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input"
			)
		else()
			file(
				DOWNLOAD "http://sourceforge.net/projects/boost/files/boost/1.53.0/boost_1_53_0.tar.gz/download" "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input/boost.tar.gz"
				SHOW_PROGRESS
				EXPECTED_MD5 "57a9e2047c0f511c4dfcf00eb5eb2fbb"
			)
			execute_process(
				COMMAND "${CMAKE_COMMAND}" -E tar xvzf boost.tar.gz boost
				WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input"
			)
		endif()
		file(
			RENAME "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input/boost_1_53_0" "${CMAKE_CURRENT_SOURCE_DIR}/input/external/input/boost"
		)
	endif()

	if(MSVC)
		execute_process(
			COMMAND make.external.bat
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		)
	else()
		execute_process(
			COMMAND ./make.external.sh
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		)
	endif()
endif()

# Library paths
if(MSVC)
	find_library(BoostPrgExecMonitorDebugLibrary libboost_prg_exec_monitor-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostPrgExecMonitorReleaseLibrary libboost_prg_exec_monitor-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostTestExecMonitorDebugLibrary libboost_test_exec_monitor-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostTestExecMonitorReleaseLibrary libboost_test_exec_monitor-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostUnitTestFrameworkDebugLibrary libboost_unit_test_framework-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostUnitTestFrameworkReleaseLibrary libboost_unit_test_framework-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostChronoDebugLibrary libboost_chrono-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostChronoReleaseLibrary libboost_chrono-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostLocaleDebugLibrary libboost_locale-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostLocaleReleaseLibrary libboost_locale-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostSystemDebugLibrary libboost_system-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostSystemReleaseLibrary libboost_system-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

	find_library(BoostThreadDebugLibrary libboost_thread-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH)
	find_library(BoostThreadReleaseLibrary libboost_thread-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH)

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

# Include paths
if(MSVC)
	include_directories(SYSTEM "${Boost}/include/boost-1_53")
else()
	include_directories(SYSTEM "${Boost}/include")
endif()
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/input/internal/code")

# Source groups and code paths
function(om_populate_code)
	file(GLOB_RECURSE Files "${CMAKE_CURRENT_SOURCE_DIR}/input/internal/code/*.*")
	foreach(File ${Files})
		get_filename_component(Directory "${File}" PATH)
		list(APPEND Directories "${Directory}")
	endforeach()
	list(REMOVE_DUPLICATES Directories)
	list(SORT Directories)

	foreach(Directory ${Directories})
		file(RELATIVE_PATH RelativeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/input/internal/code" "${Directory}")
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

	set(Cpp ${CppFiles} PARENT_SCOPE)
	set(Hpp ${HppFiles} PARENT_SCOPE)
	set(Dox ${DoxFiles} PARENT_SCOPE)
endfunction()
om_populate_code()

# Internal header
function(om_populate_internal)
	set(InternalHeader "${CMAKE_CURRENT_SOURCE_DIR}/input/internal/code/om.internal")
	file(WRITE "${InternalHeader}" "")
	foreach(HeaderFile ${Hpp})
		file(RELATIVE_PATH RelativeHeaderFile "${CMAKE_CURRENT_SOURCE_DIR}/input/internal/code" "${HeaderFile}")
		file(APPEND "${InternalHeader}" "#include \"${RelativeHeaderFile}\"\n")
	endforeach()
endfunction()
om_populate_internal()

# Targets
add_executable("Om" ${Cpp} ${Hpp} ${Dox})
add_executable("Om.Test" ${Cpp})
if(MSVC)
	add_custom_target("Om.Documentation"
		COMMAND if not exist ..\\..\\..\\output mkdir ..\\..\\..\\output
		COMMAND if not exist ..\\..\\..\\output\\documentation mkdir ..\\..\\..\\output\\documentation
		COMMAND if not exist ..\\..\\..\\output\\documentation\\doxygen mkdir ..\\..\\..\\output\\documentation\\doxygen
		COMMAND (type ..\\doxygen\\Doxyfile && echo WARN_FORMAT = "$file($line): $text") | doxygen -
		COMMENT "Generating Documentation..."
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input/internal/code"
		VERBATIM
	)
else()
	add_custom_target("Om.Documentation"
		COMMAND mkdir -p ../../../output/documentation/doxygen
		COMMAND doxygen ../doxygen/Doxyfile
		COMMENT "Generating Documentation..."
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input/internal/code"
		VERBATIM
	)
endif()

# Linking
function(om_target_link_libraries target)
	target_link_libraries(${target}
		debug "${BoostLocaleDebugLibrary}"
		optimized "${BoostLocaleReleaseLibrary}"

		debug "${BoostSystemDebugLibrary}"
		optimized "${BoostSystemReleaseLibrary}"

		debug "${BoostThreadDebugLibrary}"
		optimized "${BoostThreadReleaseLibrary}"

		debug "${BoostChronoDebugLibrary}"
		optimized "${BoostChronoReleaseLibrary}"
	)

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
endfunction()
om_target_link_libraries("Om")
om_target_link_libraries("Om.Test")
target_link_libraries("Om.Test"
	debug "${BoostPrgExecMonitorDebugLibrary}"
	optimized "${BoostPrgExecMonitorReleaseLibrary}"

	debug "${BoostTestExecMonitorDebugLibrary}"
	optimized "${BoostTestExecMonitorReleaseLibrary}"

	debug "${BoostUnitTestFrameworkDebugLibrary}"
	optimized "${BoostUnitTestFrameworkReleaseLibrary}"
)

# Precompiled headers
if(NOT MSVC)
	add_definitions(-DOm_Macros_Precompilation_)

	set_target_properties("Om" "Om.Test" PROPERTIES
		XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/input/internal/code/om.external"
		XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES"
	)
endif()

# Om.Test compile and link flags
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
endif()
set_target_properties("Om.Test" PROPERTIES COMPILE_FLAGS "${OmTestCompileFlags}")
set_target_properties("Om.Test" PROPERTIES LINK_FLAGS "${OmTestLinkFlags}")

# RUN_TESTS target
enable_testing()
add_test("Om.Test.Build" "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target "Om.Test")
add_test("Om.Test.Run" "Om.Test")
set_tests_properties("Om.Test.Run" PROPERTIES DEPENDS "Om.Test.Build")
