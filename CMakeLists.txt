cmake_minimum_required( VERSION 2.8.8 )

project( Om )

set( CMAKE_SUPPRESS_REGENERATION TRUE )

if( MSVC )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX /wd4355 /wd4505 /wd4706" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_SCL_SECURE_NO_WARNINGS" )
elseif( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
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
endif()

set( UnitTest ""
	CACHE PATH "The UnitTest library build directory path"
)
set( Boost ""
	CACHE PATH "The Boost library build directory path"
)
set( Icu ""
	CACHE PATH "The ICU library build directory path"
)

if( UnitTest )
	add_definitions( -DOm_Macros_Test_ )
endif()

aux_source_directory(
	"${CMAKE_CURRENT_SOURCE_DIR}/code/"
	Cpp_Code
)
aux_source_directory(
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/"
	Cpp_Code_Om
)
aux_source_directory(
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/operations/"
	Cpp_Code_Om_Operations
)
aux_source_directory(
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/sinks/"
	Cpp_Code_Om_Sinks
)
aux_source_directory(
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/sources/"
	Cpp_Code_Om_Sources
)
aux_source_directory(
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/symbols/"
	Cpp_Code_Om_Symbols
)

file( GLOB Hpp_Code
	"${CMAKE_CURRENT_SOURCE_DIR}/code/*.hpp"
)
file( GLOB Hpp_Code_Om
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/*.hpp"
)
file( GLOB Hpp_Code_Om_Operations
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/operations/*.hpp"
)
file( GLOB Hpp_Code_Om_Sinks
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/sinks/*.hpp"
)
file( GLOB Hpp_Code_Om_Sources
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/sources/*.hpp"
)
file( GLOB Hpp_Code_Om_Symbols
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/symbols/*.hpp"
)

file( GLOB Dox_Code
	"${CMAKE_CURRENT_SOURCE_DIR}/code/*.dox"
)
file( GLOB Dox_Code_Om
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/*.dox"
)
file( GLOB Dox_Code_Om_Operations
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/operations/*.dox"
)
file( GLOB Dox_Code_Om_Sinks
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/sinks/*.dox"
)
file( GLOB Dox_Code_Om_Sources
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/sources/*.dox"
)
file( GLOB Dox_Code_Om_Symbols
	"${CMAKE_CURRENT_SOURCE_DIR}/code/om/symbols/*.dox"
)

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

set( PrecompiledHeader code/external.hpp )
set( PrecompiledSource code/external.cpp )

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

include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/code" "${UnitTest}/src" )
if( MSVC )
	include_directories( "${Boost}" )
else()
	include_directories( "${Boost}/include" )
endif()

add_executable( Om ${Code} )

if( MSVC )
	if( UnitTest )
		find_library( UnitTestDebugLibrary
			"UnitTest++.vsnet2010" "${UnitTest}/Debug" NO_DEFAULT_PATH
		)
	
		find_library( UnitTestReleaseLibrary
			"UnitTest++.vsnet2010" "${UnitTest}/Release" NO_DEFAULT_PATH
		)

		target_link_libraries( Om
			debug "${UnitTestDebugLibrary}"
			optimized "${UnitTestReleaseLibrary}"
		)	
	endif()

	find_library( BoostChronoDebugLibrary
		libboost_chrono-vc100-mt-gd-1_52 "${Boost}/stage/lib" NO_DEFAULT_PATH
	)
	find_library( BoostLocaleDebugLibrary
		libboost_locale-vc100-mt-gd-1_52 "${Boost}/stage/lib" NO_DEFAULT_PATH
	)
	find_library( BoostSystemDebugLibrary
		libboost_system-vc100-mt-gd-1_52 "${Boost}/stage/lib" NO_DEFAULT_PATH
	)
	find_library( BoostThreadDebugLibrary
		libboost_thread-vc100-mt-gd-1_52 "${Boost}/stage/lib" NO_DEFAULT_PATH
	)

	find_library( BoostChronoReleaseLibrary
		libboost_chrono-vc100-mt-1_52 "${Boost}/stage/lib" NO_DEFAULT_PATH
	)
	find_library( BoostLocaleReleaseLibrary
		libboost_locale-vc100-mt-1_52 "${Boost}/stage/lib" NO_DEFAULT_PATH
	)
	find_library( BoostSystemReleaseLibrary
		libboost_system-vc100-mt-1_52 "${Boost}/stage/lib" NO_DEFAULT_PATH
	)
	find_library( BoostThreadReleaseLibrary
		libboost_thread-vc100-mt-1_52 "${Boost}/stage/lib" NO_DEFAULT_PATH
	)

	target_link_libraries( Om
		debug "${BoostLocaleDebugLibrary}"
		debug "${BoostSystemDebugLibrary}"
		debug "${BoostThreadDebugLibrary}"
		debug "${BoostChronoDebugLibrary}"
		optimized "${BoostLocaleReleaseLibrary}"
		optimized "${BoostSystemReleaseLibrary}"
		optimized "${BoostThreadReleaseLibrary}"
		optimized "${BoostChronoReleaseLibrary}"
	)

	find_library( IcuDataLibrary icudt "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuI18nDebugLibrary icuind "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuIoDebugLibrary icuiod "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuLeDebugLibrary iculed "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuLxDebugLibrary iculxd "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuTestDebugLibrary icutestd "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuTuDebugLibrary icutud "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuUcDebugLibrary icuucd "${Icu}/lib" NO_DEFAULT_PATH )

	find_library( IcuI18nReleaseLibrary icuin "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuIoReleaseLibrary icuio "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuLeReleaseLibrary icule "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuLxReleaseLibrary iculx "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuTestReleaseLibrary icutest "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuTuReleaseLibrary icutu "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuUcReleaseLibrary icuuc "${Icu}/lib" NO_DEFAULT_PATH )

	target_link_libraries( Om
		"${IcuDataLibrary}"
		debug "${IcuI18nDebugLibrary}"
		debug "${IcuIoDebugLibrary}"
		debug "${IcuLeDebugLibrary}"
		debug "${IcuLxDebugLibrary}"
		debug "${IcuTestDebugLibrary}"
		debug "${IcuTuDebugLibrary}"
		debug "${IcuUcDebugLibrary}"
		optimized "${IcuI18nReleaseLibrary}"
		optimized "${IcuIoReleaseLibrary}"
		optimized "${IcuLeReleaseLibrary}"
		optimized "${IcuLxReleaseLibrary}"
		optimized "${IcuTestReleaseLibrary}"
		optimized "${IcuTuReleaseLibrary}"
		optimized "${IcuUcReleaseLibrary}"
	)

	add_custom_target( "Om Documentation"
		COMMAND if not exist products mkdir products
		COMMAND if not exist products\\doxygen mkdir products\\doxygen
		COMMAND ( type doxygen\\Doxyfile && echo WARN_FORMAT = "$file($line): $text" ) | doxygen -
		COMMENT "Generating Documentation..."
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	)

	add_custom_command( TARGET Om POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icudt49.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/testplug.dll"
			"$<TARGET_FILE_DIR:Om>"

		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icuin49.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icuio49.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icule49.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/iculx49.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icutest49.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icutu49.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icuuc49.dll"
			"$<TARGET_FILE_DIR:Om>"

		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icuin49d.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icuio49d.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icule49d.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/iculx49d.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icutest49d.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icutu49d.dll"
			"$<TARGET_FILE_DIR:Om>"
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${Icu}/bin/icuuc49d.dll"
			"$<TARGET_FILE_DIR:Om>"
	)
else()
	set_target_properties( Om PROPERTIES
		XCODE_ATTRIBUTE_GCC_PREFIX_HEADER
			"${CMAKE_CURRENT_SOURCE_DIR}/${PrecompiledHeader}"
		XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES"
	)

	if( UnitTest )
		find_library( UnitTestLibrary "UnitTest++" "${UnitTest}" NO_DEFAULT_PATH )
		target_link_libraries( Om
			"${UnitTestLibrary}"
		)
	endif()

	find_library( BoostLocaleLibrary
		boost_locale "${Boost}/lib" NO_DEFAULT_PATH
	)
	find_library( BoostSystemLibrary
		boost_system "${Boost}/lib" NO_DEFAULT_PATH
	)
	find_library( BoostThreadLibrary
		boost_thread "${Boost}/lib" NO_DEFAULT_PATH
	)
	target_link_libraries( Om
		"${BoostLocaleLibrary}"
		"${BoostSystemLibrary}"
		"${BoostThreadLibrary}"
	)

	find_library( IcuDataLibrary icudata "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuI18nLibrary icui18n "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuIoLibrary icuio "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuLeLibrary icule "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuLxLibrary iculx "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuTestLibrary icutest "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuTuLibrary icutu "${Icu}/lib" NO_DEFAULT_PATH )
	find_library( IcuUcLibrary icuuc "${Icu}/lib" NO_DEFAULT_PATH )
	target_link_libraries( Om
		"${IcuDataLibrary}"
		"${IcuI18nLibrary}"
		"${IcuIoLibrary}"
		"${IcuLeLibrary}"
		"${IcuLxLibrary}"
		"${IcuTestLibrary}"
		"${IcuTuLibrary}"
		"${IcuUcLibrary}"
	)

	add_custom_target( "Om Documentation"
		COMMAND mkdir -p products/doxygen
		COMMAND doxygen doxygen/Doxyfile
		COMMENT "Generating Documentation..."
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		VERBATIM
	)
endif()
