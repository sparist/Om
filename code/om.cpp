/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_

	#include "om.hpp"

	#ifdef Om_Macro_Test_

		#include "boost/test/included/unit_test.hpp"

bool init_unit_test() {
	boost::debug::detect_memory_leaks(false);
	Om::Language::System::Get().Initialize("en_US.UTF-8");
	return true;
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
	assert(0 < theArgumentCount);
	assert(theArgumentArray);

	Om::Language::System::Get().Initialize(
		1 < theArgumentCount ?
		theArgumentArray[1] :
		"en_US.UTF-8"
	);

	typedef Om::Source::StreamSource<> CodeUnitSource;
	CodeUnitSource theCodeUnitSource(std::cin);
	Om::Source::CodePointSource<CodeUnitSource> theCodePointSource(
		theCodeUnitSource,
		CodeUnitSource()
	);

	typedef Om::Sink::StreamSink<> CodeUnitSink;
	CodeUnitSink theCodeUnitSink(std::cout);
	Om::Sink::CodePointSink<CodeUnitSink> theCodePointSink(theCodeUnitSink);

	Om::Language::System::Get().Evaluate(
		theCodePointSource,
		theCodePointSink
	);

	return EXIT_SUCCESS;
}

	#endif

#endif
