/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if defined( Om_Atom_ )

	#include "om/null.hpp"

// MARK: Om::Atom

	#define Type_ Om::Atom

// MARK: public (non-static)

inline Om::Program & Type_::operator *()
{
	return( Null::Get() );
}

inline Om::Program const & Type_::operator *() const
{
	return( Null::Get() );
}

	#undef Type_

// MARK: -
// MARK: Om

inline Om::Atom * Om::new_clone( Atom const & theAtom )
{
	return( Copy( theAtom ).release() );
}

#else
	#include "om/atom.hpp"
#endif
