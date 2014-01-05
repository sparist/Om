/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operation_ExpressionFrontPushOperation_

	#include "om/operation/expression_front_push_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(ExpressionFrontPushOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{->[expression]}",
					System::Get().Evaluate("drop find {->[expression]} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					(
						"{"
						"1{2}\n"
						"3\n"
						"4{5}\n"
						"6"
						"}"
					),
					System::Get().Evaluate("->[expression] {1{2}3}{4{5}6}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"1{2}{5}\n"
						"6"
						"}"
					),
					System::Get().Evaluate("->[expression] {1{2}}{{5}6}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"{5}\n"
						"6"
						"}"
					),
					System::Get().Evaluate("->[expression] {}{{5}6}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"{5}\n"
						"6"
						"}"
					),
					System::Get().Evaluate("->[expression] {{5}6}{}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"{2}\n"
						"3"
						"}"
					),
					System::Get().Evaluate("->[expression] quote{2}{3}")
				);

				BOOST_CHECK_EQUAL(
					"{2{3}}",
					System::Get().Evaluate("->[expression]{2}quote{3}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/expression.hpp"
	#include "om/operation/front_push_operation.hpp"

// MARK: - Om::Operation::ExpressionFrontPushOperation

	#define Type_ \
	Om::Operation::ExpressionFrontPushOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_ExpressionFrontPushOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<IncompleteOperation>(
			new FrontPushOperation<
				Expression,
				ExpressionFrontPushOperation
			>
		)
	);
}

	#undef Type_

#endif
