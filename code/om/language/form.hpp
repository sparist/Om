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

#ifndef Om_Language_Form_

	#define Om_Language_Form_ \
	Om::Language::Form

	#include "om/language/operator.hpp"
	#include "om/source/collection_front_source.hpp"

namespace Om {

	namespace Language {

		// MARK: - Om::Language::Form

		/*!
		\brief
			An Operator (which may be empty), followed by zero or more Operand instances.
		*/
		class Form {

		public: // MARK: public (static)

			class ElementRange;

			/*!
			\brief
				A Form Operand range.
			*/
			template <typename ThisOperand>
			class OperandRange;

		public: // MARK: public (non-static)

			Form();

			/*!
			\return
				True if the call results in an empty Form.
			*/
			bool BackGiveTerm(Consumer &);

			/*!
			\return
				True if the call results in an empty Form.
			*/
			bool BackPopTerm();

			template <typename TheOperand>
			void BackTakeOperand(TheOperand &);

			template <typename TheProducer>
			void BackTakeQuotedProducer(TheProducer &);

			/*!
			\return
				True if the call results in an empty Form.
			*/
			bool FrontGiveTerm(Consumer &);

			/*!
			\return
				True if the call results in an empty Form.
			*/
			bool FrontPopTerm();

			template <typename TheOperand>
			void FrontTakeOperand(TheOperand &);

			template <typename TheProducer>
			void FrontTakeQuotedProducer(TheProducer &);

			Operator const & GetOperator() const;

			void GiveElements(Consumer &);

			void GiveElements(Consumer &) const;

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
				Consumer &
			);

		private: // MARK: private (non-static)

			Operator thisOperator;

			OperandDeque thisOperandDeque;

		};

		// MARK: - Om::Language::Form::ElementRange

		/*!
		\brief
			A Form Element range.
		*/
		class Form::ElementRange:
		public Om::Source::DefaultSource<
			Element const,
			ElementRange
		> {

		public: // MARK: public (non-static)

			explicit ElementRange(Form const &);

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

			OperandDeque::const_iterator thisOperandIterator;

			OperandDeque::const_iterator thisOperandEnd;

			Element const * thisElement;

		};

		// MARK: - Om::Language::

		bool operator ==(
			Form::ElementRange const &,
			Form::ElementRange const &
		);

		bool operator !=(
			Form::ElementRange const &,
			Form::ElementRange const &
		);

		// MARK: - Om::Language::Form::OperandRange<Operand>

		/*!
		\brief
			A mutable Form Operand range.
		*/
		template <>
		class Form::OperandRange<Operand>:
		public Om::Source::CollectionFrontSource<
			Operand,
			OperandDeque::iterator
		> {

		public: // MARK: public (non-static)

			explicit OperandRange(Form &);

		};

		// MARK: - Om::Language::Form::OperandRange<Operand const>

		/*!
		\brief
			An immutable Form Operand range.
		*/
		template <>
		class Form::OperandRange<Operand const>:
		public Om::Source::CollectionFrontSource<
			Operand const,
			OperandDeque::const_iterator
		> {

		public: // MARK: public (non-static)

			explicit OperandRange(Form const &);

		};

	}

}

namespace boost {

	// MARK: - boost::

	template <>
	void swap(
		Om::Language::Form &,
		Om::Language::Form &
	);

}

	#include "om/language/form.cpp"

#endif
