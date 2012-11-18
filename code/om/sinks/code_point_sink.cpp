/*!
\file
	\brief
		Om cpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if defined( Om_Sinks_CodePointSink_ )

	#include "om/utf8.hpp"

// MARK: Om::Sinks::CodePointSink

	#define Template_ template< typename ThisCodeUnitIterator >

	#define Type_ Om::Sinks::CodePointSink< ThisCodeUnitIterator >

// MARK: public (non-static)

Template_
inline Type_::CodePointSink( ThisCodeUnitIterator theCodeUnitIterator )
:
thisCodeUnitIterator( theCodeUnitIterator )
{
}

Template_
inline Type_ & Type_::operator =( CodePointSink theCodePointSink )
{
	this->Swap( theCodePointSink );
	return( *this );
}

Template_
inline void Type_::Push( CodePoint const & theCodePoint )
{
	Utf8::encode( theCodePoint, thisCodeUnitIterator );
}

Template_
inline void Type_::Swap( CodePointSink & theCodePointSink )
{
	boost::swap(
		this->thisCodeUnitIterator,
		theCodePointSink.thisCodeUnitIterator
	);
	return( *this );
}

// MARK: -
// MARK: boost

template< typename ThisCodeUnitIterator >
inline void boost::swap(
	Om::Sinks::CodePointSink< ThisCodeUnitIterator > & theFirst,
	Om::Sinks::CodePointSink< ThisCodeUnitIterator > & theSecond
)
{
	theFirst.Swap( theSecond );
}

	#undef Type_
	#undef Template_

#else
	#include "om/sinks/code_point_sink.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Sinks
	{
		// MARK: -
		SUITE( CodePointSink )
		{
			TEST( General )
			{
				typedef std::back_insert_iterator< std::string > Iterator;
				std::string theString;
				Iterator theIterator( theString );
				CodePointSink< Iterator > theSink( theIterator );
				theSink.Push( 510U );
				CHECK_EQUAL( "\xC7\xBE", theString );
				theSink.Push( 65U );
				CHECK_EQUAL( "\xC7\xBE""A", theString );
			}
		}
	}
}

	#endif

#endif
