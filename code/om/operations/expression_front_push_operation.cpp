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

#if !defined( Om_Operations_ExpressionFrontPushOperation_ )

	#include "om/operations/expression_front_push_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om {

	namespace Operations {

		SUITE( ExpressionFrontPushOperation ) {

			TEST( Definition ) {
				CHECK_EQUAL(
					"{->expression}",
					System::Get().Evaluate( "drop find {->expression} system" )
				);
			}

			TEST( General ) {
				CHECK_EQUAL(
					(
						"{"
						"1{2}\n"
						"3\n"
						"4{5}\n"
						"6"
						"}"
					),
					System::Get().Evaluate( "->expression {1{2}3}{4{5}6}" )
				);

				CHECK_EQUAL(
					(
						"{"
						"1{2}{5}\n"
						"6"
						"}"
					),
					System::Get().Evaluate( "->expression {1{2}}{{5}6}" )
				);

				CHECK_EQUAL(
					(
						"{"
						"{5}\n"
						"6"
						"}"
					),
					System::Get().Evaluate( "->expression {}{{5}6}" )
				);

				CHECK_EQUAL(
					(
						"{"
						"{5}\n"
						"6"
						"}"
					),
					System::Get().Evaluate( "->expression {{5}6}{}" )
				);

				CHECK_EQUAL(
					(
						"{"
						"{2}\n"
						"3"
						"}"
					),
					System::Get().Evaluate( "->expression quote{2}{3}" )
				);

				CHECK_EQUAL(
					"{2{3}}",
					System::Get().Evaluate( "->expression{2}quote{3}" )
				);
			}

		}

	}

}

	#endif

#else

	#include "om/expression.hpp"
	#include "om/operations/front_push_operation.hpp"

// MARK: - Om::Operations::ExpressionFrontPushOperation

	#define Type_ \
	Om::Operations::ExpressionFrontPushOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return(
		Om_Operations_ExpressionFrontPushOperation_GetName_()
	);
}

inline void Type_::Give( Evaluation & theEvaluation ) {
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new FrontPushOperation<
				Expression,
				ExpressionFrontPushOperation
			>
		)
	);
}

	#undef Type_

#endif
