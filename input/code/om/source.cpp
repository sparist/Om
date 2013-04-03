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

#ifndef Om_Source_

	#include "om/source.hpp"

#else

	#ifndef Om_Macros_Precompilation_

		#include <cassert>
		#include <stdexcept>

	#endif

// MARK: - Om::Source

	#define Template_ \
	template <typename ThisItem>

	#define Type_ \
	Om::Source<ThisItem>

// MARK: public (non-static)

Template_
inline Type_::~Source() {}

Template_
inline ThisItem & Type_::operator *() const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

Template_
inline ThisItem * Type_::operator ->() const {
	return &**this;
}

Template_
inline bool Type_::operator !() const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

Template_
inline Type_::operator Boolean() const {
	return (
		!*this ?
		0 :
		&Source::UncomparableBoolean
	);
}

Template_
inline bool Type_::Equals(Source const &) const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

Template_
inline void Type_::Pop() {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

// MARK: private (non-static)

Template_
inline void Type_::UncomparableBoolean() const {}

	#undef Type_
	#undef Template_

// MARK: - Om::

	#define Template_ \
	template <typename TheItem>

	#define Type_ \
	Om::Source<TheItem>

Template_
inline bool Om::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return theFirst.Equals(theSecond);
}

Template_
inline bool Om::operator !=(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return !theFirst.Equals(theSecond);
}

	#undef Type_
	#undef Template_

#endif
