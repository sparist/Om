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
	\author
		Jason Erb
*/

#ifndef Om_Source_DefaultSource_

	#include "om/source/default_source.hpp"

#else

// MARK: - Om::Source::DefaultSource

	#define Template_ \
	template < \
		typename ThisItem, \
		typename ThisImplementation \
	>

	#define Type_ \
	Om::Source::DefaultSource< \
		ThisItem, \
		ThisImplementation \
	>

// MARK: public (non-static)

Template_
inline Type_::~DefaultSource() {}

Template_
inline ThisImplementation & Type_::operator ++() {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	assert(*this);
	this->Pop();
	return static_cast<ThisImplementation &>(*this);
}

Template_
inline ThisImplementation Type_::operator ++(int) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	ThisImplementation theSource(
		static_cast<ThisImplementation &>(*this)
	);
	++*this;
	return theSource;
}

Template_
inline bool Type_::Equals(
	Source<ThisItem> const & theSource
) const {
	assert(
		dynamic_cast<ThisImplementation const *>(this)
	);
	ThisImplementation const * const theImplementation = dynamic_cast<ThisImplementation const *>(&theSource);
	return (
		theImplementation &&
		theImplementation->Equals(
			static_cast<ThisImplementation const &>(*this)
		)
	);
}

	#undef Type_
	#undef Template_

#endif
