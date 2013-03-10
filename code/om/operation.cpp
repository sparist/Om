/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operation_

	#include "om/operation.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(OperationTest)

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#ifndef Om_Macros_Precompilation_

		#include <cassert>
		#include <stdexcept>

	#endif

// MARK: - Om::Operation

	#define Type_ \
	Om::Operation

// MARK: public (non-static)

inline Type_::~Operation() {}

inline void Type_::GiveElements(Queue &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::GiveElements(Queue &) const {
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
	Queue &
) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline bool Type_::TakeQuotedElements(
	Evaluation &,
	Queue const &
) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

// MARK: protected (non-static)

inline Type_::Operation() {}

	#undef Type_

#endif
