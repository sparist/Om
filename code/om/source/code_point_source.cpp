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

#ifndef Om_Source_CodePointSource_

	#include "om/source/code_point_source.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Source {

		BOOST_AUTO_TEST_SUITE(CodePointSourceTest)

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				std::string theString(
					"\xC7\xBE"
					"A"
				);
				CodePointSource<std::string::const_iterator> theSource(
					theString.begin(),
					theString.end()
				);
				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					510U,
					*theSource
				);
				theSource.Pop();
				BOOST_CHECK_EQUAL(
					false,
					!theSource
				);
				BOOST_CHECK_EQUAL(
					65U,
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

	#ifndef Om_Macro_Precompilation_

		#include "boost/swap.hpp"

	#endif

// MARK: - Om::Source::CodePointSource

	#define Template_ \
	template <typename ThisCodeUnitIterator>

	#define Type_ \
	Om::Source::CodePointSource<ThisCodeUnitIterator>

// MARK: public (non-static)

Template_
inline Type_::CodePointSource(
	ThisCodeUnitIterator theInputStart,
	ThisCodeUnitIterator const theInputEnd
):
thisInputIterator(theInputStart),
thisInputEnd(theInputEnd),
thisCodePoint() {
	this->Pop();
}

Template_
inline Type_ & Type_::operator =(CodePointSource theCodePointSource) {
	this->Swap(theCodePointSource);
	return *this;
}

Template_
inline bool Type_::operator !() const {
	return !this->thisCodePoint;
}

Template_
inline Om::CodePoint const & Type_::operator *() const {
	assert(this->thisCodePoint);
	return this->thisCodePoint;
}

Template_
inline bool Type_::Equals(CodePointSource const & theCodePointSource) const {
	return this->thisInputIterator == theCodePointSource.thisInputIterator;
}

Template_
inline void Type_::Pop() {
	if (this->thisInputEnd == this->thisInputIterator) {
		this->thisCodePoint = 0;
	} else {
		this->thisCodePoint = Utf8::decode(
			this->thisInputIterator,
			this->thisInputEnd
		);
		switch (this->thisCodePoint) {
		default:
			return;
		case boost::locale::utf::incomplete:
			// Fall through.
		case boost::locale::utf::illegal:
			this->thisCodePoint = 0xFFFD /* Replacement character */;
			// Fall through.
		}
	}
}

Template_
inline void Type_::Swap(CodePointSource & theCodePointSource) {
	boost::swap(
		this->thisInputIterator,
		theCodePointSource.thisInputIterator
	);
	boost::swap(
		this->thisInputEnd,
		theCodePointSource.thisInputEnd
	);
	boost::swap(
		this->thisCodePoint,
		theCodePointSource.thisCodePoint
	);
}

	#undef Type_
	#undef Template_

// MARK: - Om::Source::CodePointSource<char const *>

	#define Type_ \
	Om::Source::CodePointSource<char const *>

// MARK: public (non-static)

inline Type_::CodePointSource(
	char const theCodeUnitIterator[]
):
CodePointSource<CodeUnitSource>(
	CodeUnitSource(theCodeUnitIterator),
	CodeUnitSource("")
) {}

	#undef Type_

// MARK: - Om::Source::

	#define Template_ \
	template <typename TheCodeUnitIterator>

	#define Type_ \
	Om::Source::CodePointSource<TheCodeUnitIterator>

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
