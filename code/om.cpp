/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#include "om.hpp"

#include "om/sinks/stream_sink.hpp"
#include "om/sources/stream_source.hpp"
#include "om/system.hpp"
#if defined( Om_Macros_Test_ )
	#include "UnitTest++.h"
#endif

/*!
\param theArgumentCount
	The argument count; must be greater than 0.
\param theArgumentArray
	The argument array contains (in order):
	-	The program invocation.
	-	(optional) A valid UTF-8 locale string compatible with boost::locale.
*/
int main(
	int const theArgumentCount,
	char const * const theArgumentArray[]
)
{
	assert( 0 < theArgumentCount );
	assert( theArgumentArray );

	Om::System::Get().Initialize(
		( 1 < theArgumentCount ) ?
		theArgumentArray[1] :
		"en_US.UTF-8"
	);

#if defined( Om_Macros_Test_ )
	int const theResult = UnitTest::RunAllTests();
#endif

	typedef Om::Sources::StreamSource<> CodeUnitSource;
	CodeUnitSource theCodeUnitSource( std::cin );
	Om::Sources::CodePointSource< CodeUnitSource > theCodePointSource(
		theCodeUnitSource,
		CodeUnitSource()
	);

	typedef Om::Sinks::StreamSink<> CodeUnitSink;
	CodeUnitSink theCodeUnitSink( std::cout );
	Om::Sinks::CodePointSink< CodeUnitSink > theCodePointSink( theCodeUnitSink );

	Om::System::Get().Evaluate(
		theCodePointSource,
		theCodePointSink
	);

#if defined( Om_Macros_Test_ )
	return( theResult );
#else
	return( EXIT_SUCCESS );
#endif
}
