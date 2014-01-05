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

#ifndef Om_Evaluation_

	#define Om_Evaluation_ \
	Om::Evaluation

	#include "om/expression.hpp"

namespace Om {

	//! \cond
	class Evaluator;

	class Translator;
	//! \endcond

	// MARK: - Om::Evaluation

	/*!
	\brief
		The current evaluation.

	An Evaluation contains an Expression and a reference to an Evaluator, and prevents a more recursive evaluation algorithm that would overflow the stack in the event of a recursive Om program.

	Each Element that it takes is pushed onto a stack, resulting in a LIFO-ordered application of each Element to the Evaluator.
	*/
	class Evaluation {

	public: // MARK: public (non-static)

		virtual ~Evaluation();

		/*!
		\brief
			Constructs an Evaluation on the given Evaluator.
		*/
		explicit Evaluation(Evaluator &);

		Translator const & GetTranslator() const;

		bool GiveTerm(Evaluator &);

		/*!
		\brief
			Pushes the Operand onto the front of the Expression.
		*/
		template <typename TheOperand>
		void TakeOperand(TheOperand &);

		/*!
		\brief
			Takes the Operation, and gives it to the Evaluator.
		*/
		template <typename TheOperation>
		void TakeOperation(
			std::auto_ptr<TheOperation>
		);

		/*!
		\brief
			Pushes the Operator onto the front of the Expression.
		*/
		template <typename TheOperator>
		void TakeOperator(TheOperator &);

		/*!
		\brief
			Pushes the produced \ref Element "Elements" onto the front of the Expression, last first.
		*/
		template <typename TheProducer>
		void TakeProducer(TheProducer &);

		/*!
		\brief
			Pushes the quoted Producer onto the front of the Expression.
		*/
		template <typename TheProducer>
		void TakeQuotedProducer(TheProducer &);

	private: // MARK: private (non-static)

		Evaluation(Evaluation const &);

		Evaluation const & operator =(Evaluation const &);

		/*!
		\brief
			The Expression.
		*/
		Expression thisExpression;

		/*!
		\brief
			The Evaluator.
		*/
		Evaluator & thisEvaluator;

	};

}

	#include "om/evaluation.cpp"

#endif
