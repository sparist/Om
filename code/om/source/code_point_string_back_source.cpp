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

#ifndef Om_Source_CodePointStringBackSource_

	#include "om/source/code_point_string_back_source.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Source {

		BOOST_AUTO_TEST_SUITE(CodePointStringBackSourceTest)

			BOOST_AUTO_TEST_CASE(ValidTest) {
				std::string theString(
					"P" /* ASCII character */
					"o"
					"\xCC\x88" /* Combining multi-byte character */
					"r" /* ASCII character */
					"k" /* ASCII character */
					"\xE2\x98\xB9" /* Non-combining multi-byte character */
				);

				CodePointStringBackSource<std::string::const_iterator> theSource(
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
					"k",
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
					"\xCC\x88",
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
					"P",
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

				CodePointStringBackSource<std::string::const_iterator> theSource(
					theString.begin(),
					theString.end()
				);

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

			BOOST_AUTO_TEST_CASE(InvalidInsufficientTrailingTest) {
				std::string theString(
					"\xE2\x98"
					"!"
				);

				CodePointStringBackSource<std::string::const_iterator> theSource(
					theString.begin(),
					theString.end()
				);

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

			BOOST_AUTO_TEST_CASE(InvalidExtraTrailingTest) {
				std::string theString(
					"\xE2\x98\xB9" /* Valid */
					"\xB9" /* Invalid */
					"!"
				);

				CodePointStringBackSource<std::string::const_iterator> theSource(
					theString.begin(),
					theString.end()
				);

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
					"\xE2\x98\xB9",
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

				CodePointStringBackSource<std::string::const_iterator> theSource(
					theString.begin(),
					theString.end()
				);

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

			BOOST_AUTO_TEST_CASE(InvalidEarlyTerminationTest) {
				std::string theString(
					"\xE2\x98" /* Invalid */
				);

				CodePointStringBackSource<std::string::const_iterator> theSource(
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

// MARK: - Om::Source::CodePointStringBackSource

	#define Template_ \
	template <typename ThisStringIterator>

	#define Type_ \
	Om::Source::CodePointStringBackSource<ThisStringIterator>

// MARK: public (non-static)

Template_
inline Type_::CodePointStringBackSource(
	ThisStringIterator theStringStart,
	ThisStringIterator const theStringEnd
):
thisStringIterator(theStringStart),
thisCodePointIterator(theStringEnd),
thisCodePointEnd(theStringEnd),
thisCodePoint() {
	this->Update();
}

Template_
inline Type_ & Type_::operator =(CodePointStringBackSource theCodePointStringBackSource) {
	this->Swap(theCodePointStringBackSource);
	return *this;
}

Template_
inline bool Type_::operator !() const {
	return this->thisCodePointEnd == this->thisCodePointIterator;
}

Template_
inline std::string & Type_::operator *() const {
	assert(this->thisCodePointEnd != this->thisCodePointIterator);
	return this->thisCodePoint;
}

Template_
inline bool Type_::Equals(CodePointStringBackSource const & theCodePointStringBackSource) const {
	return this->thisCodePointIterator == theCodePointStringBackSource.thisCodePointIterator;
}

Template_
inline void Type_::Pop() {
	assert(this->thisCodePointEnd != this->thisCodePointIterator);
	this->thisCodePointEnd = this->thisCodePointIterator;
	this->thisCodePoint.clear();
	this->Update();
}

Template_
inline void Type_::Swap(CodePointStringBackSource & theCodePointStringBackSource) {
	boost::swap(
		this->thisStringIterator,
		theCodePointStringBackSource.thisStringIterator
	);
	boost::swap(
		this->thisCodePointIterator,
		theCodePointStringBackSource.thisCodePointIterator
	);
	boost::swap(
		this->thisCodePointEnd,
		theCodePointStringBackSource.thisCodePointEnd
	);
	boost::swap(
		this->thisCodePoint,
		theCodePointStringBackSource.thisCodePoint
	);
}

// MARK: private (non-static)

Template_
inline void Type_::Update() {
	assert(this->thisCodePointEnd == this->thisCodePointIterator);
	assert(
		this->thisCodePoint.empty()
	);
	if (this->thisStringIterator == this->thisCodePointIterator) {
		return;
	}
	for (
		int theTrailCount = 0;
		;
		++theTrailCount
	) {
		assert(this->thisStringIterator != this->thisCodePointIterator);
		char const theCodeUnit = *--this->thisCodePointIterator;
		if (
			Utf8::is_lead(theCodeUnit)
		) {
			int const theCorrectTrailCount = Utf8::trail_length(theCodeUnit);
			if (theCorrectTrailCount == theTrailCount) {
				this->thisCodePoint.assign(
					this->thisCodePointIterator,
					this->thisCodePointEnd
				);
				return;
			}
			if (theCorrectTrailCount < theTrailCount) {
				this->thisCodePointIterator += (theCorrectTrailCount + 1);
			}
			break;
		}
		if (this->thisStringIterator == this->thisCodePointIterator) {
			break;
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
	Om::Source::CodePointStringBackSource<TheStringIterator>

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
