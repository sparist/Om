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

#ifndef Om_Atom_

	#include "om/atom.hpp"

#else

	#include "om/null.hpp"

// MARK: - Om::Atom

	#define Type_ \
	Om::Atom

// MARK: public (non-static)

inline Om::Program & Type_::operator *() {
	return Null::Get();
}

inline Om::Program const & Type_::operator *() const {
	return Null::Get();
}

	#undef Type_

// MARK: - Om::

inline Om::Atom * Om::new_clone(Atom const & theAtom) {
	return Copy(theAtom).release();
}

#endif
