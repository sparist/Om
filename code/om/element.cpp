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

#ifndef Om_Element_

	#include "om/element.hpp"

#else

// MARK: - Om::Element

	#define Type_ \
	Om::Element

// MARK: public (non-static)

inline Type_::~Element() {}

inline Om::Program & Type_::operator *() {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline Om::Program const & Type_::operator *() const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline Om::Program * Type_::operator ->() {
	return &**this;
}

inline Om::Program const * Type_::operator ->() const {
	return &**this;
}

inline bool Type_::Equals(Element const &) const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline std::auto_ptr<
	Om::Source::Source<Om::Element>
> Type_::GetElementRange() {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline bool Type_::Merge(Operator &) {
	return false;
}

inline bool Type_::Merge(Operator const &) {
	return false;
}

inline bool Type_::Merge(Separator &) {
	return false;
}

inline bool Type_::Merge(Separator const &) {
	return false;
}

// MARK: - Om::

inline bool Om::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return theFirst.Equals(theSecond);
}

inline bool Om::operator !=(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return !theFirst.Equals(theSecond);
}

inline Type_ * Om::new_clone(Type_ const & theCopyable) {
	return Copy(theCopyable).release();
}

	#undef Type_

#endif
