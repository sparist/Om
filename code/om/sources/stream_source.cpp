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

#if defined( Om_Sources_StreamSource_ )

// MARK: Om::Sources::StreamSource

	#define Template_ \
	template< typename ThisItem >

	#define Type_ \
	Om::Sources::StreamSource< ThisItem >

// MARK: public (non-static)

Template_
inline Type_::StreamSource():
thisStreamIterator(),
thisItem()
{
}

Template_
inline Type_::StreamSource( std::istream & theStream ):
thisStreamIterator( theStream ),
thisItem()
{
}

Template_
inline Type_ & Type_::operator =( StreamSource theStreamSource )
{
	this->Swap( theStreamSource );
	return( *this );
}

Template_
inline bool Type_::operator ==( StreamSource const & theSource ) const
{
	return( this->thisStreamIterator == theSource.thisStreamIterator );
}

Template_
inline bool Type_::operator !() const
{
	return( StreamIterator() == this->thisStreamIterator );
}

Template_
inline ThisItem const & Type_::operator *() const
{
	assert( StreamIterator() != this->thisStreamIterator );
	this->thisItem = *this->thisStreamIterator;
	return( *this->thisItem );
}

Template_
inline void Type_::Pop()
{
	assert( StreamIterator() != this->thisStreamIterator );
	++this->thisStreamIterator;
}

Template_
inline void Type_::Swap( StreamSource & theStreamSource )
{
	boost::swap(
		this->thisStreamIterator,
		theStreamSource.thisStreamIterator
	);
	this->thisItem.swap( theStreamSource.thisItem );
}

	#undef Type_
	#undef Template_

// MARK: -
// MARK: boost

template< typename ThisItem >
inline void boost::swap(
	Om::Sources::StreamSource< ThisItem > & theFirst,
	Om::Sources::StreamSource< ThisItem > & theSecond
)
{
	theFirst.Swap( theSecond );
}

#else

	#include "om/sources/stream_source.hpp"

#endif
