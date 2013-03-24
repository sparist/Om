/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operations_OperatorFrontPushOperation_

	#include "om/operations/operator_front_push_operation.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE(OperatorFrontPushOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{->operator}",
					System::Get().Evaluate("drop find {->operator} system")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/operations/front_push_operation.hpp"

// MARK: - Om::Operations::OperatorFrontPushOperation

	#define Type_ \
	Om::Operations::OperatorFrontPushOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operations_OperatorFrontPushOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<Operation>(
			new FrontPushOperation<
				Operator,
				OperatorFrontPushOperation
			>
		)
	);
}

	#undef Type_

#endif
