cmake_minimum_required( VERSION 2.8.10 )

project( Om )

set( Boost "" CACHE PATH "The Boost library build directory path" )
set( Icu "" CACHE PATH "The ICU library build directory path" )

set( CMAKE_SUPPRESS_REGENERATION TRUE )

set( OmTestCompileFlags "-DOm_Macros_Test_ -DBOOST_TEST_ALTERNATIVE_INIT_API" )

if( MSVC )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4355" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4505" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4706" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_SCL_SECURE_NO_WARNINGS" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa" )

	add_definitions( -DU_STATIC_IMPLEMENTATION=1 )

	include_directories( SYSTEM "${Boost}/include/boost-1_53" )
else()
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdisabled-optimization" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wempty-body" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winline" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winvalid-pch" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-field-initializers" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-format-attribute" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverlength-strings" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpacked" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvariadic-macros" )

	set( OmTestCompileFlags "${OmTestCompileFlags} -Wno-format-nonliteral" )
	set( OmTestCompileFlags "${OmTestCompileFlags} -Wno-unneeded-internal-declaration" )
	set( OmTestCompileFlags "${OmTestCompileFlags} -Wno-unused-variable" )

	add_definitions( -DOm_Macros_Precompilation_ )

	include_directories( SYSTEM "${Boost}/include" )
endif()

include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/code" )

file( GLOB_RECURSE new_list RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/code/*.*" )
foreach( file_path ${new_list} )
	get_filename_component( dir_path "${file_path}" PATH )
	set( dir_list ${dir_list} "${dir_path}" )
endforeach()
list( REMOVE_DUPLICATES dir_list )
foreach( OmSourceFolder ${dir_list} )
	string( REPLACE "/" "\\" OmSourceGroup "${OmSourceFolder}" )

	aux_source_directory( "${CMAKE_CURRENT_SOURCE_DIR}/${OmSourceFolder}" Cpp_Code )
	source_group( "Source Files\\${OmSourceGroup}" FILES ${Cpp_Code} )
	list( APPEND Cpp ${Cpp_Code} )

	file( GLOB Hpp_Code "${CMAKE_CURRENT_SOURCE_DIR}/${OmSourceFolder}/*.hpp" )
	source_group( "Header Files\\${OmSourceGroup}" FILES ${Hpp_Code} )
	list( APPEND Hpp ${Hpp_Code} )

	file( GLOB Dox_Code "${CMAKE_CURRENT_SOURCE_DIR}/${OmSourceFolder}/*.dox" )
	source_group( "Doxygen Files\\${OmSourceGroup}" FILES ${Dox_Code} )
	list( APPEND Dox ${Dox_Code} )
endforeach()

set( Code
	${Hpp}
	${Cpp}
	${Dox}
)

file( WRITE "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "#if !defined( Om_Internal_ )\n" )
file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "\n" )
file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "\t#define Om_Internal_\n" )
file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "\n" )
foreach( header_path ${Hpp} )
	string( REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/code/" "" header "${header_path}" )
	file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "\t#include \"${header}\"\n" )
endforeach()
file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "\n" )
file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "#endif\n" )

add_executable( "Om" ${Code} )
add_executable( "Om.Test" ${Cpp} )

if( MSVC )
	add_custom_target( "Om.Documentation"
		COMMAND if not exist products mkdir products
		COMMAND if not exist products\\documentation mkdir products\\documentation
		COMMAND if not exist products\\documentation\\doxygen mkdir products\\documentation\\doxygen
		COMMAND ( type doxygen\\Doxyfile && echo WARN_FORMAT = "$file($line): $text" ) | doxygen -
		COMMENT "Generating Documentation..."
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		VERBATIM
	)

	find_library( BoostPrgExecMonitorDebugLibrary libboost_prg_exec_monitor-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH )
	find_library( BoostPrgExecMonitorReleaseLibrary libboost_prg_exec_monitor-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH )

	find_library( BoostTestExecMonitorDebugLibrary libboost_test_exec_monitor-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH )
	find_library( BoostTestExecMonitorReleaseLibrary libboost_test_exec_monitor-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH )

	find_library( BoostUnitTestFrameworkDebugLibrary libboost_unit_test_framework-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH )
	find_library( BoostUnitTestFrameworkReleaseLibrary libboost_unit_test_framework-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH )

	find_library( BoostChronoDebugLibrary libboost_chrono-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH )
	find_library( BoostChronoReleaseLibrary libboost_chrono-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH )

	find_library( BoostLocaleDebugLibrary libboost_locale-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH )
	find_library( BoostLocaleReleaseLibrary libboost_locale-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH )

	find_library( BoostSystemDebugLibrary libboost_system-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH )
	find_library( BoostSystemReleaseLibrary libboost_system-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH )

	find_library( BoostThreadDebugLibrary libboost_thread-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH )
	find_library( BoostThreadReleaseLibrary libboost_thread-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH )

	find_library( IcuDataDebugLibrary sicudtd "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuDataReleaseLibrary sicudt "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuI18nDebugLibrary sicuind "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuI18nReleaseLibrary sicuin "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuIoDebugLibrary sicuiod "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuIoReleaseLibrary sicuio "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuLeDebugLibrary siculed "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuLeReleaseLibrary sicule "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuLxDebugLibrary siculxd "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuLxReleaseLibrary siculx "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuTestDebugLibrary sicutestd "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuTestReleaseLibrary sicutest "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuTuDebugLibrary sicutud "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuTuReleaseLibrary sicutu "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuUcDebugLibrary sicuucd "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuUcReleaseLibrary sicuuc "${Icu}/lib" NO_DEFAULT_PATH )
else()
	add_custom_target( "Om.Documentation"
		COMMAND mkdir -p products/documentation/doxygen
		COMMAND doxygen doxygen/Doxyfile
		COMMENT "Generating Documentation..."
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		VERBATIM
	)

	find_library( BoostPrgExecMonitorReleaseLibrary boost_prg_exec_monitor "${Boost}/lib" NO_DEFAULT_PATH )
	set( BoostPrgExecMonitorDebugLibrary ${BoostPrgExecMonitorReleaseLibrary} )

	find_library( BoostTestExecMonitorReleaseLibrary boost_test_exec_monitor "${Boost}/lib" NO_DEFAULT_PATH )
	set( BoostTestExecMonitorDebugLibrary ${BoostTestExecMonitorReleaseLibrary} )

	find_library( BoostUnitTestFrameworkReleaseLibrary boost_unit_test_framework "${Boost}/lib" NO_DEFAULT_PATH )
	set( BoostUnitTestFrameworkDebugLibrary ${BoostUnitTestFrameworkReleaseLibrary} )

	find_library( BoostLocaleReleaseLibrary boost_locale "${Boost}/lib" NO_DEFAULT_PATH )
	set( BoostLocaleDebugLibrary ${BoostLocaleReleaseLibrary} )

	find_library( BoostSystemReleaseLibrary boost_system "${Boost}/lib" NO_DEFAULT_PATH )
	set( BoostSystemDebugLibrary ${BoostSystemReleaseLibrary} )

	find_library( BoostThreadReleaseLibrary boost_thread "${Boost}/lib" NO_DEFAULT_PATH )
	set( BoostThreadDebugLibrary ${BoostThreadReleaseLibrary} )

	find_library( IcuDataReleaseLibrary icudata "${Icu}/lib" NO_DEFAULT_PATH )
	set( IcuDataDebugLibrary ${IcuDataReleaseLibrary} )

	find_library( IcuI18nReleaseLibrary icui18n "${Icu}/lib" NO_DEFAULT_PATH )
	set( IcuI18nDebugLibrary ${IcuI18nReleaseLibrary} )

	find_library( IcuIoReleaseLibrary icuio "${Icu}/lib" NO_DEFAULT_PATH )
	set( IcuIoDebugLibrary ${IcuIoReleaseLibrary} )

	find_library( IcuLeReleaseLibrary icule "${Icu}/lib" NO_DEFAULT_PATH )
	set( IcuLeDebugLibrary ${IcuLeReleaseLibrary} )

	find_library( IcuLxReleaseLibrary iculx "${Icu}/lib" NO_DEFAULT_PATH )
	set( IcuLxDebugLibrary ${IcuLxReleaseLibrary} )

	find_library( IcuTestReleaseLibrary icutest "${Icu}/lib" NO_DEFAULT_PATH )
	set( IcuTestDebugLibrary ${IcuTestReleaseLibrary} )

	find_library( IcuTuReleaseLibrary icutu "${Icu}/lib" NO_DEFAULT_PATH )
	set( IcuTuDebugLibrary ${IcuTuReleaseLibrary} )

	find_library( IcuUcReleaseLibrary icuuc "${Icu}/lib" NO_DEFAULT_PATH )
	set( IcuUcDebugLibrary ${IcuUcReleaseLibrary} )
endif()

function( om_target_link_libraries target )
	target_link_libraries( ${target}
		debug "${BoostLocaleDebugLibrary}"
		optimized "${BoostLocaleReleaseLibrary}"

		debug "${BoostSystemDebugLibrary}"
		optimized "${BoostSystemReleaseLibrary}"

		debug "${BoostThreadDebugLibrary}"
		optimized "${BoostThreadReleaseLibrary}"

		debug "${BoostChronoDebugLibrary}"
		optimized "${BoostChronoReleaseLibrary}"
	)

	target_link_libraries( ${target}
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

	if( NOT MSVC )
		set_target_properties( ${target} PROPERTIES
			XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/code/om/external.hpp"
			XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES"
		)
	endif()
endfunction()

om_target_link_libraries( "Om" )
om_target_link_libraries( "Om.Test" )

target_link_libraries( "Om.Test"
	debug "${BoostPrgExecMonitorDebugLibrary}"
	optimized "${BoostPrgExecMonitorReleaseLibrary}"

	debug "${BoostTestExecMonitorDebugLibrary}"
	optimized "${BoostTestExecMonitorReleaseLibrary}"

	debug "${BoostUnitTestFrameworkDebugLibrary}"
	optimized "${BoostUnitTestFrameworkReleaseLibrary}"
)

set_target_properties( "Om.Test" PROPERTIES COMPILE_FLAGS "${OmTestCompileFlags}" )

enable_testing()
add_test( "Om.Test.Build" "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target "Om.Test" )
add_test( "Om.Test.Run" "Om.Test" )
set_tests_properties( "Om.Test.Run" PROPERTIES DEPENDS "Om.Test.Build" )
