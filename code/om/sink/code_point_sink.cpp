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

#ifndef Om_Sink_CodePointSink_

	#include "om/sink/code_point_sink.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Sink {

		BOOST_AUTO_TEST_SUITE(CodePointSinkTest)

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				typedef std::back_insert_iterator<std::string> Iterator;
				std::string theString;
				Iterator theIterator(theString);
				CodePointSink<Iterator> theSink(theIterator);
				theSink.Push(510U);
				BOOST_CHECK_EQUAL(
					"\xC7\xBE",
					theString
				);
				theSink.Push(65U);
				BOOST_CHECK_EQUAL(
					(
						"\xC7\xBE"
						"A"
					),
					theString
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/utf8.hpp"

// MARK: - Om::Sink::CodePointSink

	#define Template_ \
	template <typename ThisCodeUnitIterator>

	#define Type_ \
	Om::Sink::CodePointSink<ThisCodeUnitIterator>

// MARK: public (non-static)

Template_
inline Type_::CodePointSink(ThisCodeUnitIterator theCodeUnitIterator):
thisCodeUnitIterator(theCodeUnitIterator) {}

Template_
inline Type_ & Type_::operator =(CodePointSink theCodePointSink) {
	this->Swap(theCodePointSink);
	return *this;
}

Template_
inline void Type_::Push(CodePoint const & theCodePoint) {
	Utf8::encode(
		theCodePoint,
		thisCodeUnitIterator
	);
}

Template_
inline void Type_::Swap(CodePointSink & theCodePointSink) {
	boost::swap(
		this->thisCodeUnitIterator,
		theCodePointSink.thisCodeUnitIterator
	);
}

	#undef Type_
	#undef Template_

// MARK: - boost::

template <typename TheCodeUnitIterator>
inline void boost::swap(
	Om::Sink::CodePointSink<TheCodeUnitIterator> & theFirst,
	Om::Sink::CodePointSink<TheCodeUnitIterator> & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
