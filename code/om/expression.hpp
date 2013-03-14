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

#ifndef Om_Expression_

	#define Om_Expression_ \
	Om::Expression

	#include "om/form.hpp"

	#ifndef Om_Macros_Precompilation_

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

		//! \cond
		class ElementRange;

		template <typename ThisForm>
		class FormRange;
		//! \endcond

		static char const * GetName();

	public: // MARK: public (non-static)

		Expression();

		Expression & operator =(Expression);

		void BackGiveForm(Queue &);

		void BackGiveTerm(Queue &);

		void BackPopTerm();

		template <typename TheOperand>
		void BackTakeOperand(TheOperand &);

		template <typename TheOperator>
		void BackTakeOperator(TheOperator &);

		template <typename TheQueue>
		void BackTakeQuotedQueue(TheQueue &);

		virtual void Clear();

		void FrontGiveForm(Queue &);

		void FrontGiveTerm(Queue &);

		void FrontPopTerm();

		template <typename TheOperand>
		void FrontTakeOperand(TheOperand &);
		
		template <typename TheOperator>
		void FrontTakeOperator(TheOperator &);

		template <typename TheQueue>
		void FrontTakeQuotedQueue(TheQueue &);

		virtual std::auto_ptr<
			Source<Element const>
		> GetElementRange() const;

		virtual void GiveElements(Queue &);

		virtual void GiveElements(Queue &) const;

		virtual bool IsEmpty() const;

		virtual void ReadElements(Parser &);

		virtual void ReadQuotedElements(Parser &);

		void Swap(Expression &);

		virtual void TakeElements(Expression &);

		virtual void TakeElements(Expression const &);

		virtual void TakeElements(Queue &);

		virtual void TakeElements(Queue const &);

		template <typename TheOperand>
		void TakeOperand(TheOperand &);

		template <typename TheOperator>
		void TakeOperator(TheOperator &);

		template <typename TheQueue>
		void TakeQuotedQueue(TheQueue &);

		template <typename TheSeparator>
		void TakeSeparator(TheSeparator &);

	private: // MARK: private (static)

		typedef std::deque<Form> FormDeque;

		/*!
		\param theQueue
			The taker.
		\param theCurrent
			The current Form iterator.
		\param theEnd
			The end Form iterator.
		*/
		template <typename TheFormIterator>
		static void GiveElements(
			Queue & theQueue,
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
		Specialization on a mutable Form.
	*/
	template <>
	class Expression::FormRange<Form>:
	public Sources::CollectionFrontSource<
		Form,
		FormDeque::iterator
	> {

	public: // MARK: public (non-static)

		explicit FormRange(Expression &);

	};

	// MARK: - Om::Expression::FormRange<Form const>

	/*!
	\brief
		Specialization on an immutable Form.
	*/
	template <>
	class Expression::FormRange<Form const>:
	public Sources::CollectionFrontSource<
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
	public Sources::DefaultSource<
		Element const,
		ElementRange
	> {

		friend bool operator ==(
			ElementRange const &,
			ElementRange const &
		);

	public: // MARK: public (non-static)

		explicit ElementRange(Expression const &);

		virtual bool operator !() const;

		virtual Element const & operator *() const;

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
