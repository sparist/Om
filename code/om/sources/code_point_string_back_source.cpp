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

#if defined( Om_Sources_CodePointStringBackSource_ )

	#include "om/utf8.hpp"

// MARK: Om::Sources::CodePointStringBackSource

	#define Template_ \
	template< typename ThisStringIterator >

	#define Type_ \
	Om::Sources::CodePointStringBackSource< ThisStringIterator >

// MARK: public (non-static)

Template_
inline Type_::CodePointStringBackSource(
	ThisStringIterator theStringStart,
	ThisStringIterator const theStringEnd
):
thisStringIterator( theStringStart ),
thisCodePointIterator( theStringEnd ),
thisCodePointEnd( theStringEnd ),
thisCodePoint()
{
	this->Update();
}

Template_
inline Type_ & Type_::operator =( CodePointStringBackSource theCodePointStringBackSource )
{
	this->Swap( theCodePointStringBackSource );
	return( *this );
}

Template_
inline bool Type_::operator ==( CodePointStringBackSource const & theSource ) const
{
	return( this->thisCodePointIterator == theSource.thisCodePointIterator );
}

Template_
inline bool Type_::operator !() const
{
	return( this->thisCodePointEnd == this->thisCodePointIterator );
}

Template_
inline std::string & Type_::operator *() const
{
	assert( this->thisCodePointEnd != this->thisCodePointIterator );
	return( this->thisCodePoint );
}

Template_
inline void Type_::Pop()
{
	assert( this->thisCodePointEnd != this->thisCodePointIterator );
	this->thisCodePointEnd = this->thisCodePointIterator;
	this->thisCodePoint.clear();
	this->Update();
}

Template_
inline void Type_::Swap( CodePointStringBackSource & theCodePointStringBackSource )
{
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
inline void Type_::Update()
{
	assert( this->thisCodePointEnd == this->thisCodePointIterator );
	assert( this->thisCodePoint.empty() );
	if( this->thisStringIterator == this->thisCodePointIterator ){
		return;
	}
	for(
		int theTrailCount = 0;
		;
		++theTrailCount
	){
		assert( this->thisStringIterator != this->thisCodePointIterator );
		char const theCodeUnit = *--this->thisCodePointIterator;
		if(
			Utf8::is_lead( theCodeUnit )
		){
			int const theCorrectTrailCount = Utf8::trail_length( theCodeUnit );
			if( theCorrectTrailCount == theTrailCount ){
				this->thisCodePoint.assign(
					this->thisCodePointIterator,
					this->thisCodePointEnd
				);
				return;
			}
			if( theCorrectTrailCount < theTrailCount ){
				this->thisCodePointIterator += ( theCorrectTrailCount + 1 );
			}
			break;
		}
		if( this->thisStringIterator == this->thisCodePointIterator ){
			break;
		}
	}
	this->thisCodePoint = "\xEF\xBF\xBD" /* Replacement character */;
}

// MARK: -
// MARK: boost

template< typename ThisStringIterator >
inline void boost::swap(
	Om::Sources::CodePointStringBackSource< ThisStringIterator > & theFirst,
	Om::Sources::CodePointStringBackSource< ThisStringIterator > & theSecond
)
{
	theFirst.Swap( theSecond );
}

	#undef Type_
	#undef Template_

#else

	#include "om/sources/code_point_string_back_source.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Sources
	{
		// MARK: -
		SUITE( CodePointStringBackSource )
		{
			TEST( Valid )
			{
				std::string theString(
					"P" /* ASCII character */
					"o"
					"\xCC\x88" /* Combining multi-byte character */
					"r" /* ASCII character */
					"k" /* ASCII character */
					"\xE2\x98\xB9" /* Non-combining multi-byte character */
				);

				{
					CodePointStringBackSource< std::string::const_iterator > theSource(
						theString.begin(),
						theString.end()
					);

					CHECK_EQUAL(
						false,
						!theSource
					);
					CHECK_EQUAL(
						"\xE2\x98\xB9",
						*theSource
					);
					theSource.Pop();

					CHECK_EQUAL(
						false,
						!theSource
					);
					CHECK_EQUAL(
						"k",
						*theSource
					);
					theSource.Pop();

					CHECK_EQUAL(
						false,
						!theSource
					);
					CHECK_EQUAL(
						"r",
						*theSource
					);
					theSource.Pop();

					CHECK_EQUAL(
						false,
						!theSource
					);
					CHECK_EQUAL(
						"\xCC\x88",
						*theSource
					);
					theSource.Pop();

					CHECK_EQUAL(
						false,
						!theSource
					);
					CHECK_EQUAL(
						"o",
						*theSource
					);
					theSource.Pop();

					CHECK_EQUAL(
						false,
						!theSource
					);
					CHECK_EQUAL(
						"P",
						*theSource
					);
					theSource.Pop();

					CHECK_EQUAL(
						true,
						!theSource
					);
				}
			}

			TEST( InvalidNoTrailing )
			{
				std::string theString(
					"\xE2"
					"!"
				);

				CodePointStringBackSource< std::string::const_iterator > theSource(
					theString.begin(),
					theString.end()
				);

				CHECK_EQUAL(
					false,
					!theSource
				);
				CHECK_EQUAL(
					"!",
					*theSource
				);
				theSource.Pop();

				CHECK_EQUAL(
					false,
					!theSource
				);
				CHECK_EQUAL(
					"\xEF\xBF\xBD",
					*theSource
				);
				theSource.Pop();

				CHECK_EQUAL(
					true,
					!theSource
				);
			}

			TEST( InvalidInsufficientTrailing )
			{
				std::string theString(
					"\xE2\x98"
					"!"
				);

				CodePointStringBackSource< std::string::const_iterator > theSource(
					theString.begin(),
					theString.end()
				);

				CHECK_EQUAL(
					false,
					!theSource
				);
				CHECK_EQUAL(
					"!",
					*theSource
				);
				theSource.Pop();

				CHECK_EQUAL(
					false,
					!theSource
				);
				CHECK_EQUAL(
					"\xEF\xBF\xBD",
					*theSource
				);
				theSource.Pop();

				CHECK_EQUAL(
					true,
					!theSource
				);
			}

			TEST( InvalidExtraTrailing )
			{
				std::string theString(
					"\xE2\x98\xB9" /* Valid */
					"\xB9" /* Invalid */
					"!"
				);

				CodePointStringBackSource< std::string::const_iterator > theSource(
					theString.begin(),
					theString.end()
				);

				CHECK_EQUAL(
					false,
					!theSource
				);
				CHECK_EQUAL(
					"!",
					*theSource
				);
				theSource.Pop();

				CHECK_EQUAL(
					false,
					!theSource
				);
				CHECK_EQUAL(
					"\xEF\xBF\xBD",
					*theSource
				);
				theSource.Pop();

				CHECK_EQUAL(
					false,
					!theSource
				);
				CHECK_EQUAL(
					"\xE2\x98\xB9",
					*theSource
				);
				theSource.Pop();

				CHECK_EQUAL(
					true,
					!theSource
				);
			}

			TEST( InvalidMissingLeading )
			{
				std::string theString(
					"\xB9" /* Invalid */
					"!"
				);

				CodePointStringBackSource< std::string::const_iterator > theSource(
					theString.begin(),
					theString.end()
				);

				CHECK_EQUAL(
					false,
					!theSource
				);
				CHECK_EQUAL(
					"!",
					*theSource
				);
				theSource.Pop();

				CHECK_EQUAL(
					false,
					!theSource
				);
				CHECK_EQUAL(
					"\xEF\xBF\xBD",
					*theSource
				);
				theSource.Pop();

				CHECK_EQUAL(
					true,
					!theSource
				);
			}

			TEST( InvalidEarlyTermination )
			{
				std::string theString( "\xE2\x98" /* Invalid */ );

				CodePointStringBackSource< std::string::const_iterator > theSource(
					theString.begin(),
					theString.end()
				);

				CHECK_EQUAL(
					false,
					!theSource
				);
				CHECK_EQUAL(
					"\xEF\xBF\xBD",
					*theSource
				);
				theSource.Pop();

				CHECK_EQUAL(
					true,
					!theSource
				);
			}
		}
	}
}

	#endif

#endif
