/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Sources_CodePointSource_ )

	#include "om/sources/code_point_source.hpp"

	#if defined( Om_Macros_Test_ )

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Sources {

		BOOST_AUTO_TEST_SUITE( CodePointSourceTest )

			BOOST_AUTO_TEST_CASE( GeneralTest ) {
				std::string theString(
					"\xC7\xBE"
					"A"
				);
				CodePointSource< std::string::const_iterator > theSource(
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

// MARK: - Om::Sources::CodePointSource

	#define Template_ \
	template< typename ThisCodeUnitIterator >

	#define Type_ \
	Om::Sources::CodePointSource< ThisCodeUnitIterator >

// MARK: public (non-static)

Template_
inline Type_::CodePointSource(
	ThisCodeUnitIterator theInputStart,
	ThisCodeUnitIterator const theInputEnd
):
thisInputIterator( theInputStart ),
thisInputEnd( theInputEnd ),
thisCodePoint() {
	this->Pop();
}

Template_
inline Type_ & Type_::operator =( CodePointSource theCodePointSource ) {
	this->Swap( theCodePointSource );
	return( *this );
}

Template_
inline bool Type_::operator ==( CodePointSource const & theSource ) const {
	return( this->thisInputIterator == theSource.thisInputIterator );
}

Template_
inline bool Type_::operator !() const {
	return( !this->thisCodePoint );
}

Template_
inline Om::CodePoint const & Type_::operator *() const {
	assert( this->thisCodePoint );
	return( this->thisCodePoint );
}

Template_
inline void Type_::Pop() {
	if( this->thisInputEnd == this->thisInputIterator ) {
		this->thisCodePoint = 0;
	} else {
		this->thisCodePoint = Utf8::decode(
			this->thisInputIterator,
			this->thisInputEnd
		);
		switch( this->thisCodePoint ) {
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
inline void Type_::Swap( CodePointSource & theCodePointSource ) {
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

// MARK: - Om::Sources::CodePointSource< char const * >

	#define Type_ \
	Om::Sources::CodePointSource< char const * >

// MARK: public (non-static)

inline Type_::CodePointSource(
	char const theCodeUnitIterator[]
):
CodePointSource< CodeUnitSource >(
	CodeUnitSource( theCodeUnitIterator ),
	CodeUnitSource( "" )
) {}

	#undef Type_

// MARK: - boost

template< typename ThisCodeUnitIterator >
inline void boost::swap(
	Om::Sources::CodePointSource< ThisCodeUnitIterator > & theFirst,
	Om::Sources::CodePointSource< ThisCodeUnitIterator > & theSecond
) {
	theFirst.Swap( theSecond );
}

#endif
