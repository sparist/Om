/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Sources_CodePointStringFrontSource_ )

	#include "om/utf8.hpp"

// MARK: Om::Sources::CodePointStringFrontSource

	#define Template_ \
	template< typename ThisStringIterator >

	#define Type_ \
	Om::Sources::CodePointStringFrontSource< ThisStringIterator >

// MARK: public (non-static)

Template_
inline Type_::CodePointStringFrontSource(
	ThisStringIterator theStringStart,
	ThisStringIterator const theStringEnd
):
thisStringIterator( theStringStart ),
thisStringEnd( theStringEnd ),
thisCodePoint()
{
	this->Update();
}

Template_
inline Type_ & Type_::operator =( CodePointStringFrontSource theCodePointStringFrontSource )
{
	this->Swap( theCodePointStringFrontSource );
	return( *this );
}

Template_
inline bool Type_::operator ==( CodePointStringFrontSource const & theSource ) const
{
	return( this->thisStringIterator == theSource.thisStringIterator );
}

Template_
inline bool Type_::operator !() const
{
	return( this->thisCodePoint.empty() );
}

Template_
inline std::string & Type_::operator *() const
{
	return( this->thisCodePoint );
}

Template_
inline void Type_::Pop()
{
	this->thisCodePoint.clear();
	this->Update();
}

Template_
inline void Type_::Swap( CodePointStringFrontSource & theCodePointStringFrontSource )
{
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
inline void Type_::Update()
{
	assert( this->thisCodePoint.empty() );
	if( this->thisStringEnd == this->thisStringIterator ){
		return;
	}
	char theCodeUnit = *this->thisStringIterator;
	++this->thisStringIterator;
	if(
		Utf8::is_lead( theCodeUnit )
	){
		this->thisCodePoint.push_back( theCodeUnit );
		for(
			int theTrailCount = Utf8::trail_length( theCodeUnit );
			;
			--theTrailCount
		){
			if( !theTrailCount ){
				return;
			}
			if(
				this->thisStringEnd == this->thisStringIterator or
				!Utf8::is_trail( theCodeUnit = *this->thisStringIterator )
			){
				break;
			}
			this->thisCodePoint.push_back( theCodeUnit );
			++this->thisStringIterator;
		}
	}
	this->thisCodePoint = "\xEF\xBF\xBD" /* Replacement character */;
}

	#undef Type_
	#undef Template_

// MARK: -
// MARK: boost

template< typename ThisStringIterator >
inline void boost::swap(
	Om::Sources::CodePointStringFrontSource< ThisStringIterator > & theFirst,
	Om::Sources::CodePointStringFrontSource< ThisStringIterator > & theSecond
)
{
	theFirst.Swap( theSecond );
}

#else

	#include "om/sources/code_point_string_front_source.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Sources
	{
		// MARK: -
		SUITE( CodePointStringFrontSource )
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
					CodePointStringFrontSource< std::string::const_iterator > theSource(
						theString.begin(),
						theString.end()
					);

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
						"\xCC\x88",
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
						"k",
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
			}

			TEST( InvalidNoTrailing )
			{
				std::string theString(
					"\xE2"
					"!"
				);

				CodePointStringFrontSource< std::string::const_iterator > theSource(
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
					false,
					!theSource
				);
				CHECK_EQUAL(
					"!",
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

				CodePointStringFrontSource< std::string::const_iterator > theSource(
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
					false,
					!theSource
				);
				CHECK_EQUAL(
					"!",
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

				CodePointStringFrontSource< std::string::const_iterator > theSource(
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
					"\xEF\xBF\xBD",
					*theSource
				);
				theSource.Pop();

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

				CodePointStringFrontSource< std::string::const_iterator > theSource(
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
					false,
					!theSource
				);
				CHECK_EQUAL(
					"!",
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

				CodePointStringFrontSource< std::string::const_iterator > theSource(
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
