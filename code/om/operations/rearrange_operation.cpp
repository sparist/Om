/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Operations_RearrangeOperation_ )

	#include "om/operations/define_operation.hpp"
	#include "om/operations/dequote_operation.hpp"
	#include "om/operations/expression_back_push_operation.hpp"
	#include "om/operations/fill_operation.hpp"
	#include "om/operations/inject_operation.hpp"
	#include "om/operations/quote_operation.hpp"
	#include "om/operations/skip_operation.hpp"

// MARK: Om::Operations::RearrangeOperation

	#define Type_ \
	Om::Operations::RearrangeOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_RearrangeOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation )
{
	// define swap skip {dequote inject {quote} ->expression {fill} quote}
	DefineOperation::Give( theEvaluation );
	SwapOperation::Give( theEvaluation );
	SkipOperation::Give( theEvaluation );
	Expression theExpression;
	theExpression.TakeOperator( DequoteOperation::GetOperator() );
	theExpression.TakeOperator( InjectOperation::GetOperator() );
	theExpression.TakeQuotedQueue( QuoteOperation::GetOperator() );
	{
		Operator theOperator( ExpressionFrontPushOperation::GetName() );
		theExpression.TakeOperator( theOperator );
	}
	theExpression.TakeQuotedQueue( FillOperation::GetOperator() );
	theExpression.TakeOperator( QuoteOperation::GetOperator() );
	theEvaluation.TakeQuotedQueue( theExpression );
}

	#undef Type_

#else

	#include "om/operations/rearrange_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( RearrangeOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{rearrange}",
					System::Get().Evaluate( "drop find {rearrange} system" )
				);
			}

			TEST( General )
			{
				CHECK_EQUAL(
					"{2}{1}",
					System::Get().Evaluate( "rearrange{b a}{a b}{1}{2}" )
				);

				CHECK_EQUAL(
					"{2}{1}",
					System::Get().Evaluate(
						"rearrange"
						"{the` flaven the` glaven}"
						"{the` glaven the` flaven}"
						"{1}{2}"
					)
				);

				CHECK_EQUAL(
					"{2}{1}",
					System::Get().Evaluate(
						"rearrange"
						"{do{the glaven} do{the flaven}}"
						"{the` flaven the` glaven}"
						"{1}{2}"
					)
				);
			}
		}
	}
}

	#endif

#endif
