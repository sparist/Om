/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_DefaultElement_

	#define Om_DefaultElement_ \
	Om::DefaultElement

	#include "om/default_program.hpp"

namespace Om {

	// MARK: - Om::DefaultElement

	/*!
	\brief
		A partial implementation of Element.
	*/
	template <
		typename ThisImplementation,
		typename ThisInterface = Element
	>
	class DefaultElement:
	public DefaultProgram<
		ThisImplementation,
		ThisInterface
	> {

	public: // MARK: public (non-static)

		virtual ~DefaultElement() = 0;

		using DefaultProgram<
			ThisImplementation,
			ThisInterface
		>::Equals;

		virtual bool Equals(Element const &) const;

		/*!
		\note
			This is a non-virtual declaration that will force a link error if undefined (which could cause infinite recursion in the other form).
		*/
		bool Equals(ThisImplementation const &) const;

		virtual std::auto_ptr<
			Source::Source<Element>
		> GetElementRange();

		virtual std::auto_ptr<
			Source::Source<Element const>
		> GetElementRange() const;

		virtual void GiveElements(Consumer &);

		virtual void GiveElements(Consumer &) const;

	private: // MARK: private (non-static)

		Element & operator =(Element const &);

	};

}

	#include "om/default_element.cpp"

#endif
