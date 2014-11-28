/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Language_Element_

	#include "om/language/element.hpp"

#else

// MARK: - Om::Language::Element

	#define Type_ \
	Om::Language::Element

// MARK: public (non-static)

inline Type_::~Element() {}

inline Om::Language::Program & Type_::operator *() {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline Om::Language::Program const & Type_::operator *() const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline Om::Language::Program * Type_::operator ->() {
	return &**this;
}

inline Om::Language::Program const * Type_::operator ->() const {
	return &**this;
}

inline bool Type_::Equals(Element const &) const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline std::auto_ptr<
	Om::Source::Source<Om::Language::Element>
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

// MARK: - Om::Language::

inline bool Om::Language::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return theFirst.Equals(theSecond);
}

inline bool Om::Language::operator !=(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return !theFirst.Equals(theSecond);
}

inline Type_ * Om::Language::new_clone(Type_ const & theCopyable) {
	return Copy(theCopyable).release();
}

	#undef Type_

#endif
