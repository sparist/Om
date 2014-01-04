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

#ifndef Om_Expression_

	#define Om_Expression_ \
	Om::Expression

	#include "om/form.hpp"

	#ifndef Om_Macro_Precompilation_

		#include "boost/optional.hpp"

	#endif

	#define Om_Expression_GetName_() \
	"expression"

namespace Om {

	// MARK: - Om::Expression

	/*!
	\brief
		The \ref om__expression__ Program implementation.
	*/
	class Expression:
	public DefaultProgram<Expression> {

	public: // MARK: public (static)

		class ElementRange;

		/*!
		\brief
			An Expression Form range.
		*/
		template <typename ThisForm>
		class FormRange;

		static char const * GetName();

	public: // MARK: public (non-static)

		Expression();

		Expression & operator =(Expression);

		void BackGiveForm(Consumer &);

		void BackGiveTerm(Consumer &);

		void BackPopTerm();

		template <typename TheOperand>
		void BackTakeOperand(TheOperand &);

		template <typename TheOperator>
		void BackTakeOperator(TheOperator &);

		template <typename TheProducer>
		void BackTakeQuotedProducer(TheProducer &);

		virtual void Clear();

		void FrontGiveForm(Consumer &);

		void FrontGiveTerm(Consumer &);

		void FrontPopTerm();

		template <typename TheOperand>
		void FrontTakeOperand(TheOperand &);
		
		template <typename TheOperator>
		void FrontTakeOperator(TheOperator &);

		template <typename TheProducer>
		void FrontTakeQuotedProducer(TheProducer &);

		virtual std::auto_ptr<
			Source::Source<Element const>
		> GetElementRange() const;

		virtual void GiveElements(Consumer &);

		virtual void GiveElements(Consumer &) const;

		virtual bool IsEmpty() const;

		virtual void ReadElements(Parser &);

		virtual void ReadQuotedElements(Parser &);

		void Swap(Expression &);

		void TakeElements(Expression &);

		void TakeElements(Expression const &);

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

	private: // MARK: private (static)

		typedef std::deque<Form> FormDeque;

		/*!
		\param theConsumer
			The Consumer.
		\param theCurrent
			The current Form iterator.
		\param theEnd
			The end Form iterator.
		*/
		template <typename TheFormIterator>
		static void GiveElements(
			Consumer & theConsumer,
			TheFormIterator theCurrent,
			TheFormIterator const theEnd
		);

	private: // MARK: private (non-static)

		Form & GetBackTaker();

		Form & GetFrontTaker();

		FormDeque thisFormDeque;

	};

	// MARK: - Om::Expression::FormRange<Form>

	/*!
	\brief
		A mutable Expression Form range.
	*/
	template <>
	class Expression::FormRange<Form>:
	public Source::CollectionFrontSource<
		Form,
		FormDeque::iterator
	> {

	public: // MARK: public (non-static)

		explicit FormRange(Expression &);

	};

	// MARK: - Om::Expression::FormRange<Form const>

	/*!
	\brief
		An immutable Expression Form range.
	*/
	template <>
	class Expression::FormRange<Form const>:
	public Source::CollectionFrontSource<
		Form const,
		FormDeque::const_iterator
	> {

	public: // MARK: public (non-static)

		explicit FormRange(Expression const &);

	};

	// MARK: - Om::Expression::ElementRange

	/*!
	\brief
		An Expression Element range.
	*/
	class Expression::ElementRange:
	public Source::DefaultSource<
		Element const,
		ElementRange
	> {

	public: // MARK: public (non-static)

		explicit ElementRange(Expression const &);

		virtual bool operator !() const;

		virtual Element const & operator *() const;

		using Om::Source::DefaultSource<
			Element const,
			ElementRange
		>::Equals;

		bool Equals(ElementRange const &) const;

		void End();

		virtual void Pop();

	private: // MARK: private (non-static)

		/*!
		\brief
			The #FormDeque iterator.
		*/
		FormDeque::const_iterator thisFormIterator;

		/*!
		\brief
			The #FormDeque end.
		*/
		FormDeque::const_iterator thisFormEnd;

		/*!
		\brief
			The Element range for the current Form.
		*/
		boost::optional<Form::ElementRange> thisFormElementRange;

	};

	// MARK: - Om::

	bool operator ==(
		Expression::ElementRange const &,
		Expression::ElementRange const &
	);

	bool operator !=(
		Expression::ElementRange const &,
		Expression::ElementRange const &
	);

}

namespace boost {

	// MARK: - boost::

	template <>
	void swap(
		Om::Expression &,
		Om::Expression &
	);

}

	#include "om/expression.cpp"

#endif
