/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_DefaultMoveable_

	#include "om/default_moveable.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(DefaultMoveableTest)

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

// MARK: - Om::DefaultMoveable

	#define Template_ \
	template < \
		typename ThisImplementation, \
		typename ThisInterface \
	>

	#define Type_ \
	Om::DefaultMoveable< \
		ThisImplementation, \
		ThisInterface \
	>

// MARK: public (non-static)

Template_
inline Type_::~DefaultMoveable() {}

Template_
inline std::auto_ptr<Om::Moveable> Type_::Move() {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	std::auto_ptr<ThisImplementation> theMoveable(new ThisImplementation);
	assert(
		theMoveable.get()
	);
	theMoveable->Swap(
		static_cast<ThisImplementation &>(*this)
	);
	return std::auto_ptr<Moveable>(
		theMoveable.release()
	);
}

	#undef Type_
	#undef Template_

#endif
