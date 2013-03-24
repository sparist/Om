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

#ifndef Om_Consumer_

	#include "om/consumer.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(ConsumerTest)

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#ifndef Om_Macros_Precompilation_

		#include <cassert>
		#include <stdexcept>

	#endif

// MARK: - Om::Consumer

	#define Type_ \
	Om::Consumer

// MARK: public (non-static)

inline Type_::~Consumer() {}

inline void Type_::ReadElements(Parser &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::ReadQuotedElements(Parser &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Operand &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Operand const &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Operator &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Operator const &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Separator &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Separator const &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElements(Producer &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElements(Producer const &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeQuotedElements(Producer &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeQuotedElements(Producer const &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

	#undef Type_

#endif
