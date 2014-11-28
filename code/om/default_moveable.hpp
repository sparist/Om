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

#ifndef Om_DefaultMoveable_

	#define Om_DefaultMoveable_ \
	Om::DefaultMoveable

	#include "om/moveable.hpp"

namespace Om {

	// MARK: - Om::DefaultMoveable

	/*!
	\brief
		A partial implementation of Moveable.
	\todo
		Restore default ThisInterface argument when <a href="https://bugzilla.gnome.org/show_bug.cgi?id=739863">Doxygen bug 739863</a> is fixed.
	*/
	template <
		typename ThisImplementation,
		typename ThisInterface
	>
	class DefaultMoveable:
	public ThisInterface {

		template <typename TheMoveable>
		friend std::auto_ptr<TheMoveable> Move(TheMoveable &);

	public: // MARK: public (non-static)

		virtual ~DefaultMoveable() = 0;

		/*!
		\return
			An owner pointer to a moved object.
		*/
		virtual std::auto_ptr<Moveable> Move();

	private: // MARK: private (non-static)

		DefaultMoveable & operator =(DefaultMoveable const &);

	};

}

	#include "om/default_moveable.cpp"

#endif
