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

#ifndef Om_Form_

	#define Om_Form_ \
	Om::Form

	#include "om/operator.hpp"
	#include "om/sources/collection_front_source.hpp"

namespace Om {

	// MARK: - Om::Form

	/*!
	\brief
		An Operator (which may be empty), followed by zero or more Operand instances.
	*/
	class Form {

	public: // MARK: public (static)

		//! \cond
		class ElementRange;

		template <typename ThisOperand>
		class OperandRange;
		//! \endcond

	public: // MARK: public (non-static)

		Form();

		/*!
		\return
			True if the call results in an empty Form.
		*/
		bool BackGiveTerm(Queue &);

		/*!
		\return
			True if the call results in an empty Form.
		*/
		bool BackPopTerm();

		template <typename TheOperand>
		void BackTakeOperand(TheOperand &);

		template <typename TheQueue>
		void BackTakeQuotedQueue(TheQueue &);

		/*!
		\return
			True if the call results in an empty Form.
		*/
		bool FrontGiveTerm(Queue &);

		/*!
		\return
			True if the call results in an empty Form.
		*/
		bool FrontPopTerm();

		template <typename TheOperand>
		void FrontTakeOperand(TheOperand &);

		template <typename TheQueue>
		void FrontTakeQuotedQueue(TheQueue &);

		Operator const & GetOperator() const;

		void GiveElements(Queue &);

		void GiveElements(Queue &) const;

		bool IsEmpty() const;

		void Swap(Form &);

		/*!
		\brief
			Replaces the Form Operator.
		*/
		template <typename TheOperator>
		void TakeOperator(TheOperator &);

	private: // MARK: private (static)

		typedef std::deque<Operand> OperandDeque;

		template <
			typename TheOperandIterator,
			typename TheForm
		>
		static void GiveElements(
			TheForm &,
			Queue &
		);

	private: // MARK: private (non-static)

		Operator thisOperator;

		OperandDeque thisOperandDeque;

	};

	// MARK: - Om::Form::ElementRange

	/*!
	\brief
		A Form Element range.
	*/
	class Form::ElementRange:
	public Sources::DefaultSource<
		Element const,
		ElementRange
	> {

	public: // MARK: public (non-static)

		explicit ElementRange(Form const &);

		bool operator ==(ElementRange const &) const;

		virtual bool operator !() const;

		virtual Element const & operator *() const;

		void End();

		virtual void Pop();

	private: // MARK: private (non-static)

		OperandDeque::const_iterator thisOperandIterator;

		OperandDeque::const_iterator thisOperandEnd;

		Element const * thisElement;

	};

	// MARK: - Om::Form::OperandRange<Operand>

	/*!
	\brief
		Specialization on a mutable Operand.
	*/
	template <>
	class Form::OperandRange<Operand>:
	public Sources::CollectionFrontSource<
		Operand,
		OperandDeque::iterator
	> {

	public: // MARK: public (non-static)

		explicit OperandRange(Form &);

	};

	// MARK: - Om::Form::OperandRange<Operand const>

	/*!
	\brief
		Specialization on an immutable Operand.
	*/
	template <>
	class Form::OperandRange<Operand const>:
	public Sources::CollectionFrontSource<
		Operand const,
		OperandDeque::const_iterator
	> {

	public: // MARK: public (non-static)

		explicit OperandRange(Form const &);

	};

}

namespace boost {

	// MARK: - boost::

	template <>
	void swap(
		Om::Form &,
		Om::Form &
	);

}

	#include "om/form.cpp"

#endif
