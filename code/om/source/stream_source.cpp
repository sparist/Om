/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Source_StreamSource_

	#include "om/source/stream_source.hpp"

#else

// MARK: - Om::Source::StreamSource

	#define Template_ \
	template <typename ThisItem>

	#define Type_ \
	Om::Source::StreamSource<ThisItem>

// MARK: public (non-static)

Template_
inline Type_::StreamSource():
thisStreamIterator(),
thisItem() {}

Template_
inline Type_::StreamSource(std::istream & theStream):
thisStreamIterator(theStream),
thisItem() {}

Template_
inline Type_ & Type_::operator =(StreamSource theStreamSource) {
	this->Swap(theStreamSource);
	return *this;
}

Template_
inline bool Type_::operator !() const {
	return StreamIterator() == this->thisStreamIterator;
}

Template_
inline ThisItem const & Type_::operator *() const {
	assert(
		StreamIterator() != this->thisStreamIterator
	);
	this->thisItem = *this->thisStreamIterator;
	return *this->thisItem;
}

Template_
inline bool Type_::Equals(StreamSource const & theStreamSource) const {
	return this->thisStreamIterator == theStreamSource.thisStreamIterator;
}

Template_
inline void Type_::Pop() {
	assert(
		StreamIterator() != this->thisStreamIterator
	);
	++this->thisStreamIterator;
}

Template_
inline void Type_::Swap(StreamSource & theStreamSource) {
	boost::swap(
		this->thisStreamIterator,
		theStreamSource.thisStreamIterator
	);
	this->thisItem.swap(theStreamSource.thisItem);
}

	#undef Type_
	#undef Template_

// MARK: - Om::Source::

	#define Template_ \
	template <typename TheItem>

	#define Type_ \
	Om::Source::StreamSource<TheItem>

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
