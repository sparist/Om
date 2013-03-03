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

#if !defined( Om_Giveable_ )

	#include "om/giveable.hpp"

	#if defined( Om_Macros_Test_ )

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE( GiveableTest )
	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

// MARK: - Om::Giveable

	#define Type_ \
	Om::Giveable

// MARK: public (non-static)

inline Type_::~Giveable() {}

	#undef Type_

#endif
