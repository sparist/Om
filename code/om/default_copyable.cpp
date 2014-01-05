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

#ifndef Om_DefaultCopyable_

	#include "om/default_copyable.hpp"

#else

// MARK: - Om::DefaultCopyable

	#define Template_ \
	template < \
		typename ThisImplementation, \
		typename ThisInterface \
	>

	#define Type_ \
	Om::DefaultCopyable< \
		ThisImplementation, \
		ThisInterface \
	>

// MARK: public (non-static)

Template_
inline Type_::~DefaultCopyable() {}

Template_
inline std::auto_ptr<Om::Copyable> Type_::Copy() const {
	assert(
		dynamic_cast<ThisImplementation const *>(this)
	);
	return std::auto_ptr<Copyable>(
		new ThisImplementation(
			static_cast<ThisImplementation const &>(*this)
		)
	);
}

	#undef Type_
	#undef Template_

#endif
