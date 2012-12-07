/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
	\date
		2012
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
	struct Evaluand;

	struct Expansion;

	struct Translator;
	//! \endcond

	// MARK: - Om::Evaluator
	/*!
	\brief
		A Queue that evaluates Program instances.

	The Evaluator interprets each Element as follows:
	-	When an Operator is taken, the Translator is queried for the
		corresponding Operation.  If found, it gives its
		\ref Evaluand "Evaluand(s)" to the Evaluand vector; otherwise, the
		Evaluand vector is flushed and the Operator is given to the output
		Queue.
	-	When a Operand is taken, it is given to the most current Evaluand in
		the Evaluand vector.  If none, it is given to the output Queue.
	-	When a Separator is taken, it is disregarded.

	The program output by the Evaluator is an Expression.  Note that if each
	line in the Expression was terminated by Symbols#theLineSeparatorSymbol,
	more than one Evaluator could not be connected in sequence without each
	contributing Symbols#theLineSeparatorSymbol to the final output.
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
			The Translator; must remain in scope for the life of the Evaluator,
			and is expected to not change.
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

		template< typename TheEvaluand >
		void TakeEvaluand( std::auto_ptr< TheEvaluand > );

		template< typename TheOperand >
		void TakeOperand( TheOperand & );

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

		template< typename TheQueue >
		void TakeQuotedQueue( TheQueue & );

		template< typename TheSeparator >
		void TakeSeparator( TheSeparator & );

	private: // MARK: private (static)

		//! An Evaluand vector.
		typedef boost::ptr_vector< Evaluand > EvaluandVector;

		template< typename TheIterator >
		static void GiveElements( TheIterator, TheIterator const, Queue & );

		template< typename TheEvaluator >
		static std::auto_ptr< Program > GiveProgram( TheEvaluator & );

	private: // MARK: private (non-static)

		Evaluator( Evaluator const & );

		Evaluator const & operator =( Evaluator const & );

		/*!
		If there is a translation for this Operator, the Expansion is updated
		and each leading Operand in the resulting Expansion is sent. Otherwise
		(if there is no translation for this Operator), the Expansion is
		flushed.
		*/
		template< typename TheOperator >
		void EvaluateOperator( Expansion &, TheOperator & );

		//! The output Queue.
		Queue & thisOutput;

		//! The Translator used for resolving Operator to Operation.
		Translator const & thisTranslator;

		//! A vector of Evaluand with the most current Evaluand at the back.
		EvaluandVector thisEvaluandVector;

		//! True if an Element has been given to the output Queue.
		bool thisGaveElementToOutput;
	};
}

	#include "om/evaluator.cpp"
#endif
