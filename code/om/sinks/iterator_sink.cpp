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

#if defined( Om_Sinks_IteratorSink_ )

// MARK: Om::Sinks::IteratorSink

	#define Template_ \
	template< \
		typename ThisItem, \
		typename ThisIterator \
	>

	#define Type_ \
	Om::Sinks::IteratorSink< \
		ThisItem, \
		ThisIterator \
	>

// MARK: public (non-static)

Template_
inline Type_::IteratorSink( ThisIterator theIterator ):
thisIterator( theIterator )
{
}

Template_
inline Type_ & Type_::operator =( IteratorSink theIteratorSink )
{
	this->Swap( theIteratorSink );
	return( *this );
}

Template_
inline void Type_::Push( ThisItem & theItem )
{
	*this->thisIterator++ = theItem;
}

Template_
inline void Type_::Swap( IteratorSink & theIteratorSink )
{
	boost::swap(
		this->thisIterator,
		theIteratorSink.thisIterator
	);
	return( *this );
}

	#undef Type_
	#undef Template_

// MARK: -
// MARK: boost

template<
	typename ThisItem,
	typename ThisIterator
>
inline void boost::swap(
	Om::Sinks::IteratorSink<
		ThisItem,
		ThisIterator
	> & theFirst,
	Om::Sinks::IteratorSink<
		ThisItem,
		ThisIterator
	> & theSecond
)
{
	theFirst.Swap( theSecond );
}

#else

	#include "om/sinks/iterator_sink.hpp"

#endif
