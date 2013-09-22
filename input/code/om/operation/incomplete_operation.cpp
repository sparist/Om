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

#ifndef Om_Operation_IncompleteOperation_

	#include "om/operation/incomplete_operation.hpp"

#else

	#ifndef Om_Macros_Precompilation_

		#include <cassert>
		#include <stdexcept>

	#endif

// MARK: - Om::Operation::IncompleteOperation

	#define Type_ \
	Om::Operation::IncompleteOperation

// MARK: public (non-static)

inline Type_::~IncompleteOperation() {}

inline void Type_::GiveElements(Consumer &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::GiveElements(Consumer &) const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline bool Type_::ReadQuotedElements(
	Evaluation &,
	Parser &
) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline bool Type_::TakeElement(
	Evaluation &,
	Operand &
) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline bool Type_::TakeElement(
	Evaluation &,
	Operand const &
) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline bool Type_::TakeQuotedElements(
	Evaluation &,
	Producer &
) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline bool Type_::TakeQuotedElements(
	Evaluation &,
	Producer const &
) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

// MARK: protected (non-static)

inline Type_::IncompleteOperation() {}

	#undef Type_

#endif
