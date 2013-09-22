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

#ifndef Om_Sink_Sink_

	#include "om/sink/sink.hpp"

#else

	#ifndef Om_Macros_Precompilation_

		#include <cassert>
		#include <stdexcept>

	#endif

// MARK: - Om::Sink::Sink

	#define Template_ \
	template <typename ThisItem>

	#define Type_ \
	Om::Sink::Sink<ThisItem>

// MARK: public (non-static)

Template_
inline Type_::~Sink() {}

Template_
inline Type_ & Type_::operator =(ThisItem & theItem) {
	this->Push(theItem);
	return *this;
}

Template_
inline Type_ & Type_::operator *() {
	return *this;
}

Template_
inline Type_ * Type_::operator ->() {
	return this;
}

Template_
inline void Type_::Push(ThisItem &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

	#undef Type_
	#undef Template_

#endif
