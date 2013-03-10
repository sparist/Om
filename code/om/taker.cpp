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

#ifndef Om_Taker_

	#include "om/taker.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(TakerTest)

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

// MARK: - Om::Taker

	#define Template_ \
	template <typename ThisImplementation>

	#define Type_ \
	Om::Taker<ThisImplementation>

// MARK: public (non-static)

Template_
inline Type_::~Taker() {}

Template_
inline void Type_::Take(ThisImplementation & theTaker) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this).Swap(theTaker);
}

Template_
inline void Type_::Take(ThisImplementation const & theTaker) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this) = theTaker;
}

	#undef Type_
	#undef Template_

#endif
