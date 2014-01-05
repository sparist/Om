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
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Evaluator_

	#define Om_Evaluator_ \
	Om::Evaluator

	#include "om/default_consumer.hpp"
	#include "om/producer.hpp"

	#ifndef Om_Macro_Precompilation_

		#include "boost/ptr_container/ptr_vector.hpp"

	#endif

namespace Om {

	//! \cond
	class Evaluation;

	namespace Operation {

		class IncompleteOperation;

	}

	class Translator;
	//! \endcond

	// MARK: - Om::Evaluator

	/*!
	\brief
		A Consumer that evaluates Program instances.

	The Evaluator interprets each Element as follows:
	-	When an Operator is taken, the Translator is queried for the corresponding Operation. If found, its implementation is given to the Evaluator for further evaluation; otherwise, the IncompleteOperation vector is flushed and the Operator is given to the output Consumer.
	-	When a Operand is taken, it is given to the most current IncompleteOperation in the IncompleteOperation vector. If none, it is given to the output Consumer.
	-	When a Separator is taken, it is disregarded.

	The program output by the Evaluator is an Expression. Note that if each line in the Expression was terminated by Symbol::theLineSeparatorSymbol, more than one Evaluator could not be connected in sequence without each contributing Symbol::theLineSeparatorSymbol to the final output.
	*/
	class Evaluator:
	public DefaultConsumer<Evaluator>,
	public Producer {

	public: // MARK: public (non-static)

		/*!
		\brief
			Flushes the contents.

		If an exception is thrown, it will be caught and ignored, and each Element may not be flushed. This would only occur in an extreme situation such as insufficient memory.
		*/
		virtual ~Evaluator();

		/*!
		\param theOutput
			The output Consumer.
		\param theTranslator
			The Translator, which must remain in scope for the life of the Evaluator and is expected to not change.
		*/
		explicit Evaluator(
			Consumer & theOutput,
			Translator const & theTranslator
		);

		virtual void Clear();

		Translator const & GetTranslator() const;

		/*!
		\brief
			Gives to the argument each Element currently contained in the Evaluator.
		*/
		virtual void GiveElements(Consumer &);

		/*!
		\brief
			\overload
		*/
		virtual void GiveElements(Consumer &) const;

		virtual std::auto_ptr<Program> GiveProgram();

		virtual std::auto_ptr<Program> GiveProgram() const;

		virtual bool IsEmpty() const;

		virtual void ReadElements(Parser &);

		virtual void ReadQuotedElements(Parser &);

		void ReadQuotedElements(
			Evaluation &,
			Parser &
		);

		template <typename TheOperand>
		void TakeOperand(TheOperand &);

		template <typename TheOperand>
		void TakeOperand(
			Evaluation &,
			TheOperand &
		);

		template <typename TheOperation>
		void TakeOperation(
			std::auto_ptr<TheOperation>
		);

		/*!
		Evaluates the Operator in the following order:
		-	Attempts to evaluate the Operator in each Translator, in order.
		-	Attempts to evaluate the empty Operator (for the default definition) in each Translator, in order.
		If it was not done in this way, there would be no point in nesting if there was a default definition in the first Translator attempted.
		*/
		template <typename TheOperator>
		void TakeOperator(TheOperator &);

		template <typename TheOperator>
		void TakeOperator(
			Evaluation &,
			TheOperator &
		);

		template <typename TheProducer>
		void TakeQuotedProducer(TheProducer &);

		template <typename TheProducer>
		void TakeQuotedProducer(
			Evaluation &,
			TheProducer &
		);

		template <typename TheSeparator>
		void TakeSeparator(TheSeparator &);

	private: // MARK: private (static)

		/*!
		\brief
			An IncompleteOperation vector.
		*/
		typedef boost::ptr_vector<Operation::IncompleteOperation> IncompleteOperationVector;

		template <typename TheIterator>
		static void GiveElements(
			TheIterator,
			TheIterator const,
			Consumer &
		);

		template <typename TheEvaluator>
		static std::auto_ptr<Program> GiveProgram(TheEvaluator &);

	private: // MARK: private (non-static)

		Evaluator(Evaluator const &);

		Evaluator const & operator =(Evaluator const &);

		void Evaluate(Evaluation &);

		/*!
		\brief
			The output Consumer.
		*/
		Consumer & thisOutput;

		/*!
		\brief
			The Translator used for resolving Operator to Operation.
		*/
		Translator const & thisTranslator;

		/*!
		\brief
			A vector of IncompleteOperation with the most current at the back.
		*/
		IncompleteOperationVector thisIncompleteOperationVector;

		/*!
		\brief
			True if an Element has been given to the output Consumer.
		*/
		bool thisGaveElementToOutput;

	};

}

	#include "om/evaluator.cpp"

#endif
