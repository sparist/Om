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

#ifndef Om_Sources_SingletonSource_

	#include "om/sources/singleton_source.hpp"

#else

// MARK: - Om::Sources::SingletonSource

	#define Template_ \
	template <typename ThisItem>

	#define Type_ \
	Om::Sources::SingletonSource<ThisItem>

// MARK: public (non-static)

Template_
inline Type_::SingletonSource():
thisItem() {}

Template_
inline Type_::SingletonSource(ThisItem & theItem):
thisItem(&theItem) {}

Template_
inline Type_ & Type_::operator =(SingletonSource theSingletonSource) {
	this->Swap(theSingletonSource);
	return *this;
}

Template_
inline bool Type_::operator !() const {
	return !this->thisItem;
}

Template_
inline ThisItem & Type_::operator *() const {
	assert(this->thisItem);
	return *this->thisItem;
}

Template_
inline bool Type_::Equals(SingletonSource const & theSingletonSource) const {
	return this->thisItem == theSingletonSource.thisItem;
}

Template_
inline void Type_::Pop() {
	assert(this->thisItem);
	this->thisItem = 0;
}

Template_
inline void Type_::Swap(SingletonSource & theSingletonSource) {
	boost::swap(
		this->thisItem,
		theSingletonSource.thisItem
	);
}

	#undef Type_
	#undef Template_

// MARK: - Om::Sources::

	#define Template_ \
	template <typename TheItem>

	#define Type_ \
	Om::Sources::SingletonSource<TheItem>

Template_
inline bool Om::Sources::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return theFirst.Equals(theSecond);
}

Template_
inline bool Om::Sources::operator !=(
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
