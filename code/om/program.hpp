/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Program_

	#define Om_Program_ \
	Om::Program

	#include "om/giveable.hpp"
	#include "om/queue.hpp"
	#include "om/shareable.hpp"

namespace Om {

	//! \cond
	class Element;

	template <typename ThisItem>
	class Source;
	//! \endcond

	// MARK: - Om::Program

	/*!
	\brief
		The \ref om__programs__ "Program" implementation.

	A Program is a Giveable, Shareable Queue whose entire state is represented by an Element collection.

	Each concrete derivation must have a GetName() function that returns a null-terminated, NFD-normalized UTF-8 string to be used as a corresponding Operator name.
	*/
	class Program:
	public Giveable,
	public Queue,
	public Shareable<> {

	public: // MARK: public (non-static)

		virtual ~Program() = 0;

		virtual bool operator ==(Program const &) const = 0;

		bool operator !=(Program const &) const;

		/*!
		\return
			A non-null owner pointer to a new Element range.
		*/
		virtual std::auto_ptr<
			Source<Element const>
		> GetElementRange() const = 0;

		virtual std::auto_ptr<Program> GiveProgram();

		virtual std::auto_ptr<Program> GiveProgram() const;

	private: // MARK: private (non-static)

		Program & operator =(Program const &);

	};

}

	#include "om/program.cpp"

#endif
