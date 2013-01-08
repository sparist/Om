/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if !defined( Om_Evaluator_ )
	#define Om_Evaluator_ Om::Evaluator

	#include "om/default_queue.hpp"

namespace Om
{
	//! \cond
	struct Evaluation;

	struct Operation;

	struct Translator;
	//! \endcond

	// MARK: - Om::Evaluator
	/*!
	\brief
		A Queue that evaluates Program instances.

	The Evaluator interprets each Element as follows:
	-	When an Operator is taken, the Translator is queried for the
		corresponding Operation.  If found, its implementation is given to the
		Evaluator for further evaluation; otherwise, the Operation vector is
		flushed and the Operator is given to the output Queue.
	-	When a Operand is taken, it is given to the most current Operation in
		the Operation vector.  If none, it is given to the output Queue.
	-	When a Separator is taken, it is disregarded.

	The program output by the Evaluator is an Expression.  Note that if each
	line in the Expression was terminated by Symbols::theLineSeparatorSymbol,
	more than one Evaluator could not be connected in sequence without each
	contributing Symbols::theLineSeparatorSymbol to the final output.
	*/
	struct Evaluator
	:
	DefaultQueue< Evaluator >
	{
	public: // MARK: public (non-static)

		/*!
		\brief
			Flushes the contents.

		If an exception is thrown, it will be caught and ignored, and each
		Element may not be flushed.  This would only occur in an extreme
		situation such as insufficient memory.
		*/
		virtual ~Evaluator();

		/*!
		\param theOutput
			The output Queue.
		\param theTranslator
			The Translator, which must remain in scope for the life of the
			Evaluator and is expected to not change.
		*/
		explicit Evaluator(
			Queue & theOutput,
			Translator const & theTranslator
		);

		virtual bool operator ==( Program const & ) const;

		virtual void Clear();

		Translator const & GetTranslator() const;

		/*!
		\brief
			Gives to the argument each Element currently contained in the
			Evaluator.
		*/
		virtual void GiveElements( Queue & );

		//! \overload
		virtual void GiveElements( Queue & ) const;

		virtual std::auto_ptr< Program > GiveProgram();

		virtual std::auto_ptr< Program > GiveProgram() const;

		virtual bool IsEmpty() const;

		virtual void ReadElements( Parser & );

		virtual void ReadQuotedElements( Parser & );

		void ReadQuotedElements( Evaluation &, Parser & );

		template< typename TheOperand >
		void TakeOperand( TheOperand & );

		template< typename TheOperand >
		void TakeOperand( Evaluation &, TheOperand & );

		template< typename TheOperation >
		void TakeOperation( std::auto_ptr< TheOperation > );

		/*!
		Evaluates the Operator in the following order:
		-	Attempts to evaluate the Operator in each Translator, in order.
		-	Attempts to evaluate the empty Operator (for the default definition)
			in each Translator, in order.
		If it was not done in this way, there would be no point in nesting if
		there was a default definition in the first Translator attempted.
		*/
		template< typename TheOperator >
		void TakeOperator( TheOperator & );

		template< typename TheOperator >
		void TakeOperator( Evaluation &, TheOperator & );

		template< typename TheQueue >
		void TakeQuotedQueue( TheQueue & );

		template< typename TheQueue >
		void TakeQuotedQueue( Evaluation &, TheQueue & );

		template< typename TheSeparator >
		void TakeSeparator( TheSeparator & );

	private: // MARK: private (static)

		//! An Operation vector.
		typedef boost::ptr_vector< Operation > OperationVector;

		template< typename TheIterator >
		static void GiveElements( TheIterator, TheIterator const, Queue & );

		template< typename TheEvaluator >
		static std::auto_ptr< Program > GiveProgram( TheEvaluator & );

	private: // MARK: private (non-static)

		Evaluator( Evaluator const & );

		Evaluator const & operator =( Evaluator const & );

		void Evaluate( Evaluation & );

		//! The output Queue.
		Queue & thisOutput;

		//! The Translator used for resolving Operator to Operation.
		Translator const & thisTranslator;

		//! A vector of Operation with the most current at the back.
		OperationVector thisOperationVector;

		//! True if an Element has been given to the output Queue.
		bool thisGaveElementToOutput;
	};
}

	#include "om/evaluator.cpp"
#endif
