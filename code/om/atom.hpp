/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
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
#if !defined( Om_Atom_ )
	#define Om_Atom_ Om::Atom

	#include "om/element.hpp"

namespace Om
{
	// MARK: - Om::Atom
	/*!
	\brief
		A leaf Element defined by a string.
	*/
	struct Atom
	:
	Element
	{
	public: // MARK: public (non-static)

		virtual Program & operator *();

		virtual Program const & operator *() const;

	private: // MARK: private (non-static)

		Atom & operator =( Atom const & );
	};

	// MARK: - Om
	/*!
	\cond internal_symbols
	\return
		An owner pointer to a new copy.
	\note
		Required by boost#ptr_container classes.
	*/
	Atom * new_clone( Atom const & );
	/*!
	\endcond
	*/
}

	#include "om/atom.cpp"
#endif
