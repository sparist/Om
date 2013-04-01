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

#ifndef Om_Giveable_

	#include "om/giveable.hpp"

#else

// MARK: - Om::Giveable

	#define Type_ \
	Om::Giveable

// MARK: public (non-static)

inline Type_::~Giveable() {}

	#undef Type_

// MARK: - Om::

template <typename TheGiveable>
inline std::auto_ptr<TheGiveable> Om::Give(TheGiveable & theGiveable) {
	return Move(theGiveable);
}

template <typename TheGiveable>
inline std::auto_ptr<TheGiveable> Om::Give(
	std::auto_ptr<TheGiveable> & theGiveable
) {
	return theGiveable;
}

template <typename TheGiveable>
inline std::auto_ptr<TheGiveable> Om::Give(TheGiveable const & theGiveable) {
	return Copy(theGiveable);
}

template <typename TheGiveable>
inline std::auto_ptr<TheGiveable> Om::Give(
	std::auto_ptr<TheGiveable> const & theGiveable
) {
	return (
		theGiveable.get() ?
		Give(*theGiveable) :
		std::auto_ptr<TheGiveable>()
	);
}

#endif
