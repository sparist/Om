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

#ifndef Om_Moveable_

	#include "om/moveable.hpp"

#else

	#ifndef Om_Macro_Precompilation_

		#include <cassert>
		#include <stdexcept>

	#endif

// MARK: - Om::Moveable

	#define Type_ \
	Om::Moveable

// MARK: public (non-static)

inline Type_::~Moveable() {}

inline std::auto_ptr<Type_> Type_::Move() {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

	#undef Type_

// MARK: - Om::

template <typename TheMoveable>
inline std::auto_ptr<TheMoveable> Om::Move(TheMoveable & theMoveable) {
	return std::auto_ptr<TheMoveable>(
		static_cast<TheMoveable *>(
			theMoveable.Move().release()
		)
	);
}

#endif
