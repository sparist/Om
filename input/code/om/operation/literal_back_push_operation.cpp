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

#ifndef Om_Operation_LiteralBackPushOperation_

	#include "om/operation/literal_back_push_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(LiteralBackPushOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{literal<-}",
					System::Get().Evaluate("drop find {literal<-} system")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/operation/literal_front_push_operation.hpp"
	#include "om/operation/swap_operation.hpp"

// MARK: - Om::Operation::LiteralBackPushOperation

	#define Type_ \
	Om::Operation::LiteralBackPushOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_LiteralBackPushOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	LiteralFrontPushOperation::Give(theEvaluation);
	SwapOperation::Give(theEvaluation);
}

	#undef Type_

#endif
