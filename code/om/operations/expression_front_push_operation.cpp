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
#if defined( Om_Operations_ExpressionFrontPushOperation_ )

	#include "om/expression.hpp"
	#include "om/operations/front_push_operation.hpp"

// MARK: Om::Operations::ExpressionFrontPushOperation

	#define Type_ Om::Operations::ExpressionFrontPushOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_ExpressionFrontPushOperation_GetName_() );
}

template< typename TheEvaluator>
inline void Type_::Give( TheEvaluator & theEvaluator )
{
	theEvaluator.TakeEvaluand(
		std::auto_ptr< Evaluand >(
			new FrontPushOperation< Expression, ExpressionFrontPushOperation >
		)
	);
}

	#undef Type_

#else
	#include "om/operations/expression_front_push_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( ExpressionFrontPushOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					(
						"{"
							"1{2}\n"
							"3\n"
							"4{5}\n"
							"6"
						"}"
					),
					Environment().Evaluate( "->expression {1{2}3}{4{5}6}" )
				);

				CHECK_EQUAL(
					(
						"{"
							"1{2}{5}\n"
							"6"
						"}"
					),
					Environment().Evaluate( "->expression {1{2}}{{5}6}" )
				);

				CHECK_EQUAL(
					(
						"{"
							"{5}\n"
							"6"
						"}"
					),
					Environment().Evaluate( "->expression {}{{5}6}" )
				);

				CHECK_EQUAL(
					(
						"{"
							"{5}\n"
							"6"
						"}"
					),
					Environment().Evaluate( "->expression {{5}6}{}" )
				);

				CHECK_EQUAL(
					(
						"{"
							"{2}\n"
							"3"
						"}"
					),
					Environment().Evaluate( "->expression quote{2}{3}" )
				);

				CHECK_EQUAL(
					"{2{3}}",
					Environment().Evaluate( "->expression{2}quote{3}" )
				);
			}
		}
	}
}

	#endif

#endif
