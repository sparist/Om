/*!
\file
	\brief
		Om cpp file.
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
#if defined( Om_Operations_RearrangeOperation_ )

	#include "om/operations/dequote_operation.hpp"
	#include "om/operations/evaluate_operation.hpp"
	#include "om/operations/expression_back_push_operation.hpp"
	#include "om/operations/fill_operation.hpp"
	#include "om/operations/inject_operation.hpp"
	#include "om/operations/quote_operation.hpp"
	#include "om/operations/skip_operation.hpp"

// MARK: Om::Operations::RearrangeOperation

	#define Type_ Om::Operations::RearrangeOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_RearrangeOperation_GetName_() );
}

template< typename TheEvaluandTaker>
inline void Type_::Give( TheEvaluandTaker & theEvaluandTaker )
{
	// evaluate swap skip {dequote inject {quote} ->expression {fill} quote}
	EvaluateOperation::Give( theEvaluandTaker );
	SwapOperation::Give( theEvaluandTaker );
	SkipOperation::Give( theEvaluandTaker );
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
	theEvaluandTaker.TakeQuotedQueue( theExpression );
}

	#undef Type_

#else
	#include "om/operations/rearrange_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( RearrangeOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					"{2}{1}",
					Environment().Evaluate( "rearrange{b a}{a b}{1}{2}" )
				);

				CHECK_EQUAL(
					"{2}{1}",
					Environment().Evaluate(
						"rearrange"
						"{the` flaven the` glaven}"
						"{the` glaven the` flaven}"
						"{1}{2}"
					)
				);

				CHECK_EQUAL(
					"{2}{1}",
					Environment().Evaluate(
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
