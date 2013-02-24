/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_ )

	#include "om.hpp"

	#if defined( Om_Macros_Test_ )

		#define BOOST_TEST_MODULE \
		OmTest

		#include <boost/test/included/unit_test.hpp>

bool init_unit_test() {
	Om::System::Get().Initialize( "en_US.UTF-8" );
	return( true );
}

	#else

/*!
\param theArgumentCount
	The argument count; must be greater than 0.
\param theArgumentArray
	The argument array contains (in order):
	-	The program invocation.
	-	<em>(Optional)</em> A valid UTF-8 <a href="http://userguide.icu-project.org/locale">locale string</a>; defaults to "en_US.UTF-8".
*/
int main(
	int const theArgumentCount,
	char const * const theArgumentArray[]
) {
	assert( 0 < theArgumentCount );
	assert( theArgumentArray );

	Om::System::Get().Initialize(
		( 1 < theArgumentCount )?
		theArgumentArray[ 1 ]:
		"en_US.UTF-8"
	);

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

	return( EXIT_SUCCESS );
}

	#endif

#endif
