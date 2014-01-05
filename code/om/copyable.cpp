/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Copyable_

	#include "om/copyable.hpp"

#else

	#ifndef Om_Macro_Precompilation_

		#include <cassert>
		#include <stdexcept>

	#endif

// MARK: - Om::Copyable

	#define Type_ \
	Om::Copyable

// MARK: public (non-static)

inline Type_::~Copyable() {}

inline std::auto_ptr<Type_> Type_::Copy() const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

	#undef Type_

// MARK: - Om::

template <typename TheCopyable>
inline std::auto_ptr<TheCopyable> Om::Copy(TheCopyable const & theCopyable) {
	return std::auto_ptr<TheCopyable>(
		static_cast<TheCopyable *>(
			theCopyable.Copy().release()
		)
	);
}

#endif
