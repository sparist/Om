/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Element_

	#define Om_Element_ \
	Om::Element

	#include "om/program.hpp"

namespace Om {

	// MARK: - Om::Element

	/*!
	\brief
		A Program that contains a single elemental item (or none, when IsEmpty() returns true).
	*/
	class Element :
	public Program {

	public: // MARK: public (non-static)

		virtual ~Element() = 0;

		/*!
		\return
			The wrapped Program (Null if none).
		*/
		virtual Program & operator *() = 0;

		/*!
		\overload
		*/
		virtual Program const & operator *() const = 0;

		Program * operator ->();

		Program const * operator ->() const;

		using Program::Equals;

		virtual bool Equals(Element const &) const = 0;

		using Program::GetElementRange;

		/*!
		\return
			An Element range containing only this Element.
		*/
		virtual std::auto_ptr<
			Source::Source<Element>
		> GetElementRange() = 0;

		/*!
		\return
			True if the Element could be merged.
		*/
		virtual bool Merge(Operator &);

		/*!
		\overload
		*/
		virtual bool Merge(Operator const &);

		/*!
		\overload
		*/
		virtual bool Merge(Separator &);

		/*!
		\overload
		*/
		virtual bool Merge(Separator const &);

	private: // MARK: private (non-static)

		Element & operator =(Element const &);

	};

	// MARK: - Om::

	bool operator ==(
		Element const &,
		Element const &
	);

	bool operator !=(
		Element const &,
		Element const &
	);

	/*!
	\return
		An owner pointer to a new copy.
	\note
		Required by boost::ptr_container classes.
	*/
	Element * new_clone(Element const &);

}

	#include "om/element.cpp"

#endif
