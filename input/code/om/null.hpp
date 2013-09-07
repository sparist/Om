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

#ifndef Om_Null_

	#define Om_Null_ \
	Om::Null

	#include "om/code_point.hpp"
	#include "om/default_element.hpp"

	#ifndef Om_Macros_Precompilation_

		#include "boost/swap.hpp"

	#endif

	#define Om_Null_GetName_() \
	"null"

namespace Om {

	// MARK: - Om::Null

	/*!
	\brief
		The \ref om__null__ Element implementation.
	*/
	class Null :
	public DefaultElement<Null>
	{

	public: // MARK: public (static)

		/*!
		\return
			The static Null. This can be a mutable reference because Null is immutable regardless.
		*/
		static Null & Get();

		static char const * GetName();

	public: // MARK: public (non-static)

		Null();

		/*!
		\brief
			Swallows the next CodePoint in the Source.
		*/
		explicit Null(
			Source<CodePoint const> &
		);

		Null & operator =(Null const &);

		virtual Program & operator *();

		virtual Program const & operator *() const;

		virtual void Clear();

		virtual bool Equals(Element const &) const;

		virtual bool Equals(Program const &) const;

		virtual std::auto_ptr<
			Source<Element>
		> GetElementRange();

		virtual std::auto_ptr<
			Source<Element const>
		> GetElementRange() const;

		virtual void GiveElements(Consumer &);

		virtual void GiveElements(Consumer &) const;

		virtual bool IsEmpty() const;

		virtual bool Merge(Operator &);

		virtual bool Merge(Operator const &);

		virtual bool Merge(Separator &);

		virtual bool Merge(Separator const &);

		virtual void ReadElements(Parser &);

		virtual void ReadQuotedElements(Parser &);

		virtual void Swap(Null &);

		virtual void TakeElements(Producer &);

		virtual void TakeElements(Producer const &);

		template <typename TheOperand>
		void TakeOperand(TheOperand &);

		template <typename TheOperator>
		void TakeOperator(TheOperator &);

		template <typename TheProducer>
		void TakeQuotedProducer(TheProducer &);

		template <typename TheSeparator>
		void TakeSeparator(TheSeparator &);

	};

}

namespace boost {

	// MARK: - boost::

	template <>
	void swap(
		Om::Null &,
		Om::Null &
	);

}

	#include "om/null.cpp"

#endif
