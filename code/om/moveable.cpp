/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Moveable_ )

	#include "om/moveable.hpp"

	#if defined( Om_Macros_Test_ )

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE( MoveableTest )
	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#if !defined( Om_Macros_Precompilation_ )

		#include <cassert>
		#include <stdexcept>

	#endif

// MARK: - Om::Moveable

	#define Type_ \
	Om::Moveable

// MARK: public (non-static)

inline Type_::~Moveable() {}

// MARK: private (non-static)

inline Type_ * Type_::Move() {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

	#undef Type_

#endif
