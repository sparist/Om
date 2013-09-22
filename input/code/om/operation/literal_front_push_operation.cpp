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

#ifndef Om_Operation_LiteralFrontPushOperation_

	#include "om/operation/literal_front_push_operation.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(LiteralFrontPushOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{->literal}",
					System::Get().Evaluate("drop find {->literal} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{1{2}34{5}6}",
					System::Get().Evaluate("->literal {1{2}3}{4{5}6}")
				);

				BOOST_CHECK_EQUAL(
					"{1{2}{5}6}",
					System::Get().Evaluate("->literal {1{2}}{{5}6}")
				);

				BOOST_CHECK_EQUAL(
					"{{5}6}",
					System::Get().Evaluate("->literal {}{{5}6}")
				);

				BOOST_CHECK_EQUAL(
					"{{5}6}",
					System::Get().Evaluate("->literal {{5}6}{}")
				);

				BOOST_CHECK_EQUAL(
					"{{2}3}",
					System::Get().Evaluate("->literal quote{2}{3}")
				);

				BOOST_CHECK_EQUAL(
					"{2{3}}",
					System::Get().Evaluate("->literal{2}quote{3}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/literal.hpp"
	#include "om/operation/front_push_operation.hpp"

// MARK: - Om::Operation::LiteralFrontPushOperation

	#define Type_ \
	Om::Operation::LiteralFrontPushOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_LiteralFrontPushOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<IncompleteOperation>(
			new FrontPushOperation<
				Literal,
				LiteralFrontPushOperation
			>
		)
	);
}

	#undef Type_

#endif
