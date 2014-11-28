/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Language_Atom_

	#define Om_Language_Atom_ \
	Om::Language::Atom

	#include "om/language/element.hpp"

namespace Om {

	namespace Language {

		// MARK: - Om::Language::Atom

		/*!
		\brief
			An atomic Element defined by a string.
		*/
		class Atom:
		public Element {

		public: // MARK: public (non-static)

			virtual Program & operator *();

			virtual Program const & operator *() const;

		private: // MARK: private (non-static)

			Atom & operator =(Atom const &);

		};

		// MARK: - Om::Language::

		/*!
		\return
			An owner pointer to a new copy.
		\note
			Required by boost::ptr_container classes.
		*/
		Atom * new_clone(Atom const &);

	}

}

	#include "om/language/atom.cpp"

#endif
