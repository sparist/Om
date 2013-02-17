cmake_minimum_required( VERSION 2.8.8 )

project( Om )

set( CMAKE_SUPPRESS_REGENERATION TRUE )

if( MSVC )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX /wd4355 /wd4505 /wd4706 /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS" )
elseif( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wcast-align -Wcast-qual -Wdisabled-optimization -Wempty-body -Werror -Wfloat-equal -Wformat=2 -Winit-self -Winline -Winvalid-pch -Wmissing-field-initializers -Wmissing-format-attribute -Woverlength-strings -Wpacked -Wpointer-arith -Wredundant-decls -Wvariadic-macros" )
endif()

set( UnitTest "" CACHE PATH "The UnitTest library build directory path" )
set( Boost "" CACHE PATH "The Boost library build directory path" )
set( Icu "" CACHE PATH "The ICU library build directory path" )

file( WRITE "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "#if !defined( Om_Internal_ )\n" )
file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "\n" )
file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "\t#define Om_Internal_\n" )
file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "\n" )

aux_source_directory( "${CMAKE_CURRENT_SOURCE_DIR}/code/" Cpp_Code )
aux_source_directory( "${CMAKE_CURRENT_SOURCE_DIR}/code/om/" Cpp_Code_Om )
aux_source_directory( "${CMAKE_CURRENT_SOURCE_DIR}/code/om/operations/" Cpp_Code_Om_Operations )
aux_source_directory( "${CMAKE_CURRENT_SOURCE_DIR}/code/om/sinks/" Cpp_Code_Om_Sinks )
aux_source_directory( "${CMAKE_CURRENT_SOURCE_DIR}/code/om/sources/" Cpp_Code_Om_Sources )
aux_source_directory( "${CMAKE_CURRENT_SOURCE_DIR}/code/om/symbols/" Cpp_Code_Om_Symbols )

file( GLOB Hpp_Code "${CMAKE_CURRENT_SOURCE_DIR}/code/*.hpp" )
file( GLOB Hpp_Code_Om "${CMAKE_CURRENT_SOURCE_DIR}/code/om/*.hpp" )
file( GLOB Hpp_Code_Om_Operations "${CMAKE_CURRENT_SOURCE_DIR}/code/om/operations/*.hpp" )
file( GLOB Hpp_Code_Om_Sinks "${CMAKE_CURRENT_SOURCE_DIR}/code/om/sinks/*.hpp" )
file( GLOB Hpp_Code_Om_Sources "${CMAKE_CURRENT_SOURCE_DIR}/code/om/sources/*.hpp" )
file( GLOB Hpp_Code_Om_Symbols "${CMAKE_CURRENT_SOURCE_DIR}/code/om/symbols/*.hpp" )

file( GLOB Dox_Code "${CMAKE_CURRENT_SOURCE_DIR}/code/*.dox" )
file( GLOB Dox_Code_Om "${CMAKE_CURRENT_SOURCE_DIR}/code/om/*.dox" )
file( GLOB Dox_Code_Om_Operations "${CMAKE_CURRENT_SOURCE_DIR}/code/om/operations/*.dox" )
file( GLOB Dox_Code_Om_Sinks "${CMAKE_CURRENT_SOURCE_DIR}/code/om/sinks/*.dox" )
file( GLOB Dox_Code_Om_Sources "${CMAKE_CURRENT_SOURCE_DIR}/code/om/sources/*.dox" )
file( GLOB Dox_Code_Om_Symbols "${CMAKE_CURRENT_SOURCE_DIR}/code/om/symbols/*.dox" )

set( Hpp
	${Hpp_Code}
	${Hpp_Code_Om}
	${Hpp_Code_Om_Operations}
	${Hpp_Code_Om_Sinks}
	${Hpp_Code_Om_Sources}
	${Hpp_Code_Om_Symbols}
)

set( Cpp
	${Cpp_Code}
	${Cpp_Code_Om}
	${Cpp_Code_Om_Operations}
	${Cpp_Code_Om_Sinks}
	${Cpp_Code_Om_Sources}
	${Cpp_Code_Om_Symbols}
)

set( Dox
	${Dox_Code}
	${Dox_Code_Om}
	${Dox_Code_Om_Operations}
	${Dox_Code_Om_Sinks}
	${Dox_Code_Om_Sources}
	${Dox_Code_Om_Symbols}
)

set( Code
	${Hpp}
	${Cpp}
	${Dox}
)

foreach( header_path ${Hpp} )
	string( REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/code/" "" header "${header_path}" )
	file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "\t#include \"${header}\"\n" )
endforeach()
file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "\n" )
file( APPEND "${CMAKE_CURRENT_SOURCE_DIR}/code/om/internal.hpp" "#endif\n" )

set( PrecompiledHeader code/om/external.hpp )
set( PrecompiledSource code/om/external.cpp )

source_group( "Source Files" FILES ${Cpp_Code} )
source_group( "Source Files\\om" FILES ${Cpp_Code_Om} )
source_group( "Source Files\\om\\operations" FILES ${Cpp_Code_Om_Operations} )
source_group( "Source Files\\om\\sinks" FILES ${Cpp_Code_Om_Sinks} )
source_group( "Source Files\\om\\sources" FILES ${Cpp_Code_Om_Sources} )
source_group( "Source Files\\om\\symbols" FILES ${Cpp_Code_Om_Symbols} )

source_group( "Header Files" FILES ${Hpp_Code} )
source_group( "Header Files\\om" FILES ${Hpp_Code_Om} )
source_group( "Header Files\\om\\operations" FILES ${Hpp_Code_Om_Operations} )
source_group( "Header Files\\om\\sinks" FILES ${Hpp_Code_Om_Sinks} )
source_group( "Header Files\\om\\sources" FILES ${Hpp_Code_Om_Sources} )
source_group( "Header Files\\om\\symbols" FILES ${Hpp_Code_Om_Symbols} )

source_group( "Doxygen Files" FILES ${Dox_Code} )
source_group( "Doxygen Files\\om" FILES ${Dox_Code_Om} )
source_group( "Doxygen Files\\om\\operations" FILES ${Dox_Code_Om_Operations} )
source_group( "Doxygen Files\\om\\sinks" FILES ${Dox_Code_Om_Sinks} )
source_group( "Doxygen Files\\om\\sources" FILES ${Dox_Code_Om_Sources} )
source_group( "Doxygen Files\\om\\symbols" FILES ${Dox_Code_Om_Symbols} )

include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/code" )
if( MSVC )
	include_directories( "${Boost}/include/boost-1_53" )
else()
	include_directories( "${Boost}/include" )
endif()
if( UnitTest )
	include_directories( "${UnitTest}/src" )
endif()

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

	if( UnitTest )
		find_library( UnitTestDebugLibrary "UnitTest++.vsnet2010" "${UnitTest}/Debug" NO_DEFAULT_PATH )
		find_library( UnitTestReleaseLibrary "UnitTest++.vsnet2010" "${UnitTest}/Release" NO_DEFAULT_PATH )
	endif()

	find_library( BoostChronoDebugLibrary libboost_chrono-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH )
	find_library( BoostChronoReleaseLibrary libboost_chrono-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH )

	find_library( BoostLocaleDebugLibrary libboost_locale-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH )
	find_library( BoostLocaleReleaseLibrary libboost_locale-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH )

	find_library( BoostSystemDebugLibrary libboost_system-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH )
	find_library( BoostSystemReleaseLibrary libboost_system-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH )

	find_library( BoostThreadDebugLibrary libboost_thread-vc100-mt-gd-1_53 "${Boost}/lib" NO_DEFAULT_PATH )
	find_library( BoostThreadReleaseLibrary libboost_thread-vc100-mt-1_53 "${Boost}/lib" NO_DEFAULT_PATH )

	find_library( IcuDataLibrary icudt "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuI18nDebugLibrary icuind "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuI18nReleaseLibrary icuin "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuIoDebugLibrary icuiod "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuIoReleaseLibrary icuio "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuLeDebugLibrary iculed "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuLeReleaseLibrary icule "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuLxDebugLibrary iculxd "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuLxReleaseLibrary iculx "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuTestDebugLibrary icutestd "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuTestReleaseLibrary icutest "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuTuDebugLibrary icutud "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuTuReleaseLibrary icutu "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuUcDebugLibrary icuucd "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuUcReleaseLibrary icuuc "${Icu}/lib" NO_DEFAULT_PATH )
else()
	add_custom_target( "Om.Documentation"
		COMMAND mkdir -p products/documentation/doxygen
		COMMAND doxygen doxygen/Doxyfile
		COMMENT "Generating Documentation..."
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		VERBATIM
	)

	if( UnitTest )
		find_library( UnitTestReleaseLibrary "UnitTest++" "${UnitTest}" NO_DEFAULT_PATH )
		set( UnitTestDebugLibrary ${UnitTestReleaseLibrary} )
	endif()

	find_library( BoostLocaleReleaseLibrary boost_locale "${Boost}/lib" NO_DEFAULT_PATH )
	set( BoostLocaleDebugLibrary ${BoostLocaleReleaseLibrary} )

	find_library( BoostSystemReleaseLibrary boost_system "${Boost}/lib" NO_DEFAULT_PATH )
	set( BoostSystemDebugLibrary ${BoostSystemReleaseLibrary} )

	find_library( BoostThreadReleaseLibrary boost_thread "${Boost}/lib" NO_DEFAULT_PATH )
	set( BoostThreadDebugLibrary ${BoostThreadReleaseLibrary} )

	find_library( IcuDataLibrary icudata "${Icu}/lib" NO_DEFAULT_PATH )

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

macro( om_target_link_libraries target )
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
		"${IcuDataLibrary}"
	
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

	if( MSVC )
		add_custom_command( TARGET ${target} POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icudt49.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/testplug.dll"
				"$<TARGET_FILE_DIR:${target}>"
	
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icuin49.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icuio49.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icule49.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/iculx49.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icutest49.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icutu49.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icuuc49.dll"
				"$<TARGET_FILE_DIR:${target}>"
	
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icuin49d.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icuio49d.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icule49d.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/iculx49d.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icutest49d.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icutu49d.dll"
				"$<TARGET_FILE_DIR:${target}>"
			COMMAND "${CMAKE_COMMAND}" -E copy
				"${Icu}/bin/icuuc49d.dll"
				"$<TARGET_FILE_DIR:${target}>"
	
			VERBATIM
		)
	else()
		set_target_properties( ${target} PROPERTIES
			XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/${PrecompiledHeader}"
			XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES"
		)
	endif()
endmacro()

if( UnitTest )
	set_target_properties( "Om.Test" PROPERTIES COMPILE_FLAGS -DOm_Macros_Test_ )

	target_link_libraries( "Om.Test"
		debug "${UnitTestDebugLibrary}"
		optimized "${UnitTestReleaseLibrary}"
	)
endif()

om_target_link_libraries( "Om" )
om_target_link_libraries( "Om.Test" )
