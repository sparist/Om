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

#ifndef Om_DefaultCopyable_

	#define Om_DefaultCopyable_ \
	Om::DefaultCopyable

	#include "om/copyable.hpp"

namespace Om {

	// MARK: - Om::DefaultCopyable

	/*!
	\brief
		A partial implementation of Copyable.
	\todo
		Restore default ThisInterface argument when <a href="https://bugzilla.gnome.org/show_bug.cgi?id=739863">Doxygen bug 739863</a> is fixed.
	*/
	template <
		typename ThisImplementation,
		typename ThisInterface
	>
	class DefaultCopyable:
	public ThisInterface {

		template <typename TheCopyable>
		friend std::auto_ptr<TheCopyable> Copy(TheCopyable const &);

	public: // MARK: public (non-static)

		virtual ~DefaultCopyable() = 0;

		/*!
		\return
			An owner pointer to a copy.
		*/
		virtual std::auto_ptr<Copyable> Copy() const;

	private: // MARK: private (non-static)

		DefaultCopyable & operator =(DefaultCopyable const &);

	};

}

	#include "om/default_copyable.cpp"

#endif
