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
#if !defined( Om_DefaultEvaluation_ )
	#define Om_DefaultEvaluation_ Om::DefaultEvaluation

	#include "om/evaluation.hpp"

namespace Om
{
	//! \cond
	struct Operator;
	//! \endcond

	// MARK: - Om::Operations::DefaultEvaluation
	/*!
	\brief
		A partial implementation of Evaluation.
	*/
	template< typename ThisImplementation >
	struct DefaultEvaluation
	:
	Evaluation
	{
	public: // MARK: public (static)

		static Operator const & GetOperator();

		template< typename TheEvaluationTaker >
		static void Give( TheEvaluationTaker & );

	public: // MARK: public (non-static)

		virtual ~DefaultEvaluation() = 0;

		virtual void GiveElements( Queue & );

		virtual void GiveElements( Queue & ) const;

		virtual bool ReadQuotedElements( Expansion &, Parser & );

		/*!
		\brief
			Takes the Operand and gives the result to the Expansion.
		\return
			True if this call completes the Evaluation, in which case any
			further calls on the Evaluation are undefined.
		*/
		virtual bool TakeElement( Expansion &, Operand & );

		//! \overload
		virtual bool TakeElement( Expansion &, Operand const & );

		virtual bool TakeQuotedElements( Expansion &, Queue & );

		virtual bool TakeQuotedElements( Expansion &, Queue const & );
	};
}

	#include "om/default_evaluation.cpp"
#endif
