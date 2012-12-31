/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.1
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
#if defined( Om_Sources_IteratorSource_ )

// MARK: Om::Sources::IteratorSource

	#define Template_ template< typename ThisItem, typename ThisIterator >

	#define Type_ Om::Sources::IteratorSource< ThisItem, ThisIterator >

// MARK: public (non-static)

Template_
inline Type_::IteratorSource( ThisIterator const theIterator )
:
thisIterator( theIterator )
{
}

Template_
inline Type_ & Type_::operator =( IteratorSource theIteratorSource )
{
	this->Swap( theIteratorSource );
	return( *this );
}

Template_
inline bool Type_::operator ==( IteratorSource const & theSource ) const
{
	return(
		this->thisIterator == theSource.thisIterator ||
		( !*this->thisIterator && !*theSource.thisIterator )
	);
}

Template_
inline bool Type_::operator !() const
{
	return( !*this->thisIterator );
}

Template_
inline ThisItem & Type_::operator *() const
{
	assert( !!*this->thisIterator );
	return( *this->thisIterator );
}

Template_
inline void Type_::Pop()
{
	assert( !!*this->thisIterator );
	++this->thisIterator;
}

Template_
inline void Type_::Swap( IteratorSource & theIteratorSource )
{
	boost::swap(
		this->thisIterator,
		theIteratorSource.thisIterator
	);
}

	#undef Type_
	#undef Template_

// MARK: -
// MARK: boost

template< typename ThisItem, typename ThisIterator >
inline void boost::swap(
	Om::Sources::IteratorSource< ThisItem, ThisIterator > & theFirst,
	Om::Sources::IteratorSource< ThisItem, ThisIterator > & theSecond
)
{
	theFirst.Swap( theSecond );
}

#else
	#include "om/sources/iterator_source.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/sinks/container_back_sink.hpp"
		#include "UnitTest++.h"

namespace Om
{
	// MARK: -
	SUITE( IteratorSource )
	{
		namespace
		{
			static void CopyWithIterators(
				char const theCodeUnitIterator[],
				std::string & theSinkString
			)
			{
				typedef char const * Iterator;
				typedef Sources::IteratorSource< char const, Iterator > Source;
				Source theSource( theCodeUnitIterator );
				Source const theSourceEnd( "" );

				typedef Sinks::ContainerBackSink<
					char const,
					std::string
				> Sink;
				Sink theSink( theSinkString );

				std::copy( theSource, theSourceEnd, theSink );
			}

			struct Item
			{
				Item( char theCodeUnit )
				:
				thisCodeUnit( theCodeUnit )
				{
				}

				bool operator !() const
				{
					return( !this->thisCodeUnit );
				}

				char thisCodeUnit;
			};
		}

		TEST( General )
		{
			typedef Item * Iterator;
			typedef Sources::IteratorSource< Item, Iterator > Source;

			Item theSourceArray[] = { '0', '1', '2', 0 };
			Source theSource( theSourceArray );
			Item theSourceArrayEnd[] = { 0 };
			Source const theSourceEnd( theSourceArrayEnd );

			CHECK( theSourceEnd != theSource );
			CHECK_EQUAL( '0', theSource->thisCodeUnit );

			++theSource;
			CHECK( theSourceEnd != theSource );
			CHECK_EQUAL( '1', ( *theSource ).thisCodeUnit );

			Source theIterator = ++theSource;
			CHECK( theSourceEnd != theSource );
			CHECK_EQUAL( '2', theIterator->thisCodeUnit );
			CHECK_EQUAL( '2', theSource->thisCodeUnit );

			theIterator->thisCodeUnit = '3';
			( *theSource ).thisCodeUnit = '4';
			CHECK_EQUAL( '4', ( *theIterator ).thisCodeUnit );
			CHECK_EQUAL( '4', theSource->thisCodeUnit );
			CHECK_EQUAL( '0', theSourceArray[ 0 ].thisCodeUnit );
			CHECK_EQUAL( '1', theSourceArray[ 1 ].thisCodeUnit );
			CHECK_EQUAL( '4', theSourceArray[ 2 ].thisCodeUnit );
			CHECK_EQUAL( 0, theSourceArray[ 3 ].thisCodeUnit );

			++theSource;
			CHECK( theSourceEnd == theSource );
		}

		TEST( CopyMultipleItems )
		{
			char const theSourceNullTerminatedString[] = "01";
			std::string theSinkString;
			CopyWithIterators( theSourceNullTerminatedString, theSinkString );

			CHECK_EQUAL( theSourceNullTerminatedString, theSinkString );
		}

		TEST( CopySingleItem )
		{
			char const theSourceNullTerminatedString[] = "0";
			std::string theSinkString;
			CopyWithIterators( theSourceNullTerminatedString, theSinkString );

			CHECK_EQUAL( theSourceNullTerminatedString, theSinkString );
		}

		TEST( CopyNoItems )
		{
			char const theSourceNullTerminatedString[] = "";
			std::string theSinkString;
			CopyWithIterators( theSourceNullTerminatedString, theSinkString );

			CHECK_EQUAL( theSourceNullTerminatedString, theSinkString );
		}
	}
}

	#endif

#endif
