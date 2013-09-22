/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Source_EmptySource_

	#include "om/source/empty_source.hpp"

#else

// MARK: - Om::Source::EmptySource

	#define Template_ \
	template <typename ThisItem>

	#define Type_ \
	Om::Source::EmptySource<ThisItem>

// MARK: public (static)

Template_
inline Type_ & Type_::Get() {
	static Type_ theEmptySource;
	return theEmptySource;
}

// MARK: public (non-static)

Template_
inline Type_::EmptySource() {}

Template_
inline Type_ & Type_::operator =(EmptySource) {
	return *this;
}

Template_
inline bool Type_::operator !() const {
	return true;
}

Template_
inline ThisItem & Type_::operator *() const {
	assert(0);
	throw std::logic_error("The source is empty.");
}

Template_
inline bool Type_::Equals(EmptySource const &) const {
	return true;
}

Template_
inline void Type_::Pop() {
	assert(0);
	throw std::logic_error("The source is empty.");
}

Template_
inline void Type_::Swap(EmptySource &) {}

	#undef Type_
	#undef Template_

// MARK: - Om::Source::

	#define Template_ \
	template <typename TheItem>

	#define Type_ \
	Om::Source::EmptySource<TheItem>

Template_
inline bool Om::Source::operator ==(
	Type_ const &,
	Type_ const &
) {
	return true;
}

Template_
inline bool Om::Source::operator !=(
	Type_ const &,
	Type_ const &
) {
	return false;
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
