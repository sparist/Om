/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Sinks_IteratorSink_

	#include "om/sinks/iterator_sink.hpp"

#else

// MARK: - Om::Sinks::IteratorSink

	#define Template_ \
	template < \
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
inline Type_::IteratorSink(ThisIterator theIterator) :
thisIterator(theIterator)
{}

Template_
inline Type_ & Type_::operator =(IteratorSink theIteratorSink) {
	this->Swap(theIteratorSink);
	return *this;
}

Template_
inline void Type_::Push(ThisItem & theItem) {
	*this->thisIterator++ = theItem;
}

Template_
inline void Type_::Swap(IteratorSink & theIteratorSink) {
	boost::swap(
		this->thisIterator,
		theIteratorSink.thisIterator
	);
	return *this;
}

	#undef Type_
	#undef Template_

// MARK: - boost::

template <
	typename TheItem,
	typename TheIterator
>
inline void boost::swap(
	Om::Sinks::IteratorSink<
		TheItem,
		TheIterator
	> & theFirst,
	Om::Sinks::IteratorSink<
		TheItem,
		TheIterator
	> & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
