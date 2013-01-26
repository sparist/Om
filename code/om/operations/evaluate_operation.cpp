/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Operations_EvaluateOperation_ )

	#include "om/environment.hpp"

// MARK: Om::Operations::EvaluateOperation

	#define Type_ \
	Om::Operations::EvaluateOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_EvaluateOperation_GetName_() );
}

template< typename TheEvaluateOperation >
inline void Type_::GiveElements(
	TheEvaluateOperation &,
	Queue & theQueue
)
{
	theQueue.TakeElement( GetOperator() );
}

// MARK: public (non-static)

inline Type_::EvaluateOperation()
{
}

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
)
{
	assert( !theOperand.IsEmpty() );
	return(
		this->TakeQuotedQueue(
			theEvaluation,
			*theOperand.GetProgram()
		)
	);
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
)
{
	Expression theExpression;
	{
		Evaluator theScope(
			theExpression,
			theEvaluation.GetTranslator()
		);
		theQueue.GiveElements( theScope );
	}
	theEvaluation.TakeQuotedQueue( theExpression );
	return( true );
}

	#undef Type_

#else

	#include "om/operations/evaluate_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( EvaluateOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{evaluate}",
					System::Get().Evaluate( "drop find {evaluate} system" )
				);
			}

			TEST( Basic )
			{
				CHECK_EQUAL(
					"{{A}{A}}",
					System::Get().Evaluate( "evaluate {copy {A}}" )
				);
			}
		}
	}
}

	#endif

#endif
