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

\defgroup om__expression__ Expression
	\ingroup om__program__
	\brief
		A \ref om__program__ optimized for evaluation.
	\par Interpretation
		A \ref om__program__ is interpreted as an \ref om__expression__ by treating it as a list of non-empty <em>forms</em>, each containing the following:
		-	An \ref om__operator__ (or none).
		-	An \ref om__operand__ list (which may be empty only if there is an \ref om__operator__).
	\par Normalization
		A \ref om__program__ is normalized as an \ref om__expression__ as follows:
		-	Each \ref om__separator__ is removed, and a line \ref om__separator__ is inserted between each non-empty form.
	\par Implementation
		Om::Expression
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
	\todo
		Restore default ThisInterface argument when <a href="https://bugzilla.gnome.org/show_bug.cgi?id=739863">Doxygen bug 739863</a> is fixed.
	*/
	class Expression:
	public DefaultProgram<
		Expression,
		Program
	> {

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

		virtual void ParseElements(Reader &);

		virtual void ParseQuotedElements(Reader &);

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
