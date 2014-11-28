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

#ifndef Om_Source_CodePointStringFrontSource_

	#include "om/source/code_point_string_front_source.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Source {

		BOOST_AUTO_TEST_SUITE(CodePointStringFrontSourceTest)

			BOOST_AUTO_TEST_CASE(ValidTest) {
				std::string theString(
					"P" /* ASCII character */
					"o"
					"\xCC\x88" /* Combining multi-byte character */
					"r" /* ASCII character */
					"k" /* ASCII character */
					"\xE2\x98\xB9" /* Non-combining multi-byte character */
				);

				CodePointStringFrontSource<std::string::const_iterator> theSource(
					theString.begin(),
					theString.end()
				);

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"P",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"o",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"\xCC\x88",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"r",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"k",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"\xE2\x98\xB9",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					true,
					!theSource
				);
			}

			BOOST_AUTO_TEST_CASE(InvalidNoTrailingTest) {
				std::string theString(
					"\xE2"
					"!"
				);

				CodePointStringFrontSource<std::string::const_iterator> theSource(
					theString.begin(),
					theString.end()
				);

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"\xEF\xBF\xBD",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"!",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					true,
					!theSource
				);
			}

			BOOST_AUTO_TEST_CASE(InvalidInsufficientTrailingTest) {
				std::string theString(
					"\xE2\x98"
					"!"
				);

				CodePointStringFrontSource<std::string::const_iterator> theSource(
					theString.begin(),
					theString.end()
				);

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"\xEF\xBF\xBD",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"!",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					true,
					!theSource
				);
			}

			BOOST_AUTO_TEST_CASE(InvalidExtraTrailingTest) {
				std::string theString(
					"\xE2\x98\xB9" /* Valid */
					"\xB9" /* Invalid */
					"!"
				);

				CodePointStringFrontSource<std::string::const_iterator> theSource(
					theString.begin(),
					theString.end()
				);

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"\xE2\x98\xB9",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"\xEF\xBF\xBD",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"!",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					true,
					!theSource
				);
			}

			BOOST_AUTO_TEST_CASE(InvalidMissingLeadingTest) {
				std::string theString(
					"\xB9" /* Invalid */
					"!"
				);

				CodePointStringFrontSource<std::string::const_iterator> theSource(
					theString.begin(),
					theString.end()
				);

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"\xEF\xBF\xBD",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"!",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					true,
					!theSource
				);
			}

			BOOST_AUTO_TEST_CASE(InvalidEarlyTerminationTest) {
				std::string theString(
					"\xE2\x98" /* Invalid */
				);

				CodePointStringFrontSource<std::string::const_iterator> theSource(
					theString.begin(),
					theString.end()
				);

				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					"\xEF\xBF\xBD",
					*theSource
				);
				theSource.Pop();

				BOOST_CHECK_EQUAL(
					true,
					!theSource
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/utf8.hpp"

// MARK: - Om::Source::CodePointStringFrontSource

	#define Template_ \
	template <typename ThisStringIterator>

	#define Type_ \
	Om::Source::CodePointStringFrontSource<ThisStringIterator>

// MARK: public (non-static)

Template_
inline Type_::CodePointStringFrontSource(
	ThisStringIterator theStringStart,
	ThisStringIterator const theStringEnd
):
thisStringIterator(theStringStart),
thisStringEnd(theStringEnd),
thisCodePoint() {
	this->Update();
}

Template_
inline Type_ & Type_::operator =(CodePointStringFrontSource theCodePointStringFrontSource) {
	this->Swap(theCodePointStringFrontSource);
	return *this;
}

Template_
inline bool Type_::operator !() const {
	return this->thisCodePoint.empty();
}

Template_
inline std::string & Type_::operator *() const {
	return this->thisCodePoint;
}

Template_
inline bool Type_::Equals(CodePointStringFrontSource const & theCodePointStringFrontSource) const {
	return this->thisStringIterator == theCodePointStringFrontSource.thisStringIterator;
}

Template_
inline void Type_::Pop() {
	this->thisCodePoint.clear();
	this->Update();
}

Template_
inline void Type_::Swap(CodePointStringFrontSource & theCodePointStringFrontSource) {
	boost::swap(
		this->thisStringIterator,
		theCodePointStringFrontSource.thisStringIterator
	);
	boost::swap(
		this->thisStringEnd,
		theCodePointStringFrontSource.thisStringEnd
	);
	boost::swap(
		this->thisCodePoint,
		theCodePointStringFrontSource.thisCodePoint
	);
}

// MARK: private (non-static)

Template_
inline void Type_::Update() {
	assert(
		this->thisCodePoint.empty()
	);
	if (this->thisStringEnd == this->thisStringIterator) {
		return;
	}
	char theCodeUnit = *this->thisStringIterator;
	++this->thisStringIterator;
	if (
		Utf8::is_lead(theCodeUnit)
	) {
		this->thisCodePoint.push_back(theCodeUnit);
		for (
			int theTrailCount = Utf8::trail_length(theCodeUnit);
			;
			--theTrailCount
		) {
			if (!theTrailCount) {
				return;
			}
			if (
				this->thisStringEnd == this->thisStringIterator ||
				!Utf8::is_trail(theCodeUnit = *this->thisStringIterator)
			) {
				break;
			}
			this->thisCodePoint.push_back(theCodeUnit);
			++this->thisStringIterator;
		}
	}
	this->thisCodePoint = "\xEF\xBF\xBD" /* Replacement character */;
}

	#undef Type_
	#undef Template_

// MARK: - Om::Source::

	#define Template_ \
	template <typename TheStringIterator>

	#define Type_ \
	Om::Source::CodePointStringFrontSource<TheStringIterator>

Template_
inline bool Om::Source::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return theFirst.Equals(theSecond);
}

Template_
inline bool Om::Source::operator !=(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return !theFirst.Equals(theSecond);
}

// MARK: - boost::

Template_
inline void boost::swap(
	Type_ & theFirst,
	Type_ & theSecond
) {
	theFirst.Swap(theSecond);
}

	#undef Type_
	#undef Template_

#endif
