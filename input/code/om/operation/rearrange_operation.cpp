/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operation_RearrangeOperation_

	#include "om/operation/rearrange_operation.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(RearrangeOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{rearrange}",
					System::Get().Evaluate("drop find {rearrange} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{2}{1}",
					System::Get().Evaluate("rearrange{b a}{a b}{1}{2}")
				);

				BOOST_CHECK_EQUAL(
					"{2}{1}",
					System::Get().Evaluate(
						"rearrange"
						"{the` flaven the` glaven}"
						"{the` glaven the` flaven}"
						"{1}{2}"
					)
				);

				BOOST_CHECK_EQUAL(
					"{2}{1}",
					System::Get().Evaluate(
						"rearrange"
						"{do{the glaven} do{the flaven}}"
						"{the` flaven the` glaven}"
						"{1}{2}"
					)
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/operation/define_operation.hpp"
	#include "om/operation/dequote_operation.hpp"
	#include "om/operation/fill_operation.hpp"
	#include "om/operation/inject_operation.hpp"
	#include "om/operation/pair_operation.hpp"
	#include "om/operation/quote_operation.hpp"
	#include "om/operation/skip_operation.hpp"
	#include "om/operation/swap_operation.hpp"

// MARK: - Om::Operation::RearrangeOperation

	#define Type_ \
	Om::Operation::RearrangeOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_RearrangeOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	// define swap skip {dequote inject {quote} pair {fill}}
	DefineOperation::Give(theEvaluation);
	SwapOperation::Give(theEvaluation);
	SkipOperation::Give(theEvaluation);
	Expression theExpression;
	theExpression.TakeOperator(
		DequoteOperation::GetOperator()
	);
	theExpression.TakeOperator(
		InjectOperation::GetOperator()
	);
	theExpression.TakeQuotedProducer(
		QuoteOperation::GetOperator()
	);
	theExpression.TakeOperator(
		PairOperation::GetOperator()
	);
	theExpression.TakeQuotedProducer(
		FillOperation::GetOperator()
	);
	theEvaluation.TakeQuotedProducer(theExpression);
}

	#undef Type_

#endif
