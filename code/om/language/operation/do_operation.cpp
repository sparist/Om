/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Language_Operation_DoOperation_

	#include "om/language/operation/do_operation.hpp"

	#ifdef Om_Macro_Test_

		#include "om/language/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

			BOOST_AUTO_TEST_SUITE(DoOperationTest)

				BOOST_AUTO_TEST_CASE(DefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{do}",
						System::Get().Evaluate("drop find {do} system")
					);
				}

				BOOST_AUTO_TEST_CASE(SimpleTest) {
					BOOST_CHECK_EQUAL(
						"{a}{bc}",
						System::Get().Evaluate("do {<-[code points]} {abc}")
					);
				}

			BOOST_AUTO_TEST_SUITE_END()

		}

	}

}

	#endif

#else

	#include "om/language/operation/dequote_operation.hpp"
	#include "om/language/operation/operator_operation.hpp"

// MARK: - Om::Language::Operation::DoOperation

	#define Type_ \
	Om::Language::Operation::DoOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operation_DoOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	DequoteOperation::Give(theEvaluation);
	OperatorOperation::Give(theEvaluation);
}

	#undef Type_

#endif
