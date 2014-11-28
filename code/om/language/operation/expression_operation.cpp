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

#ifndef Om_Language_Operation_ExpressionOperation_

	#include "om/language/operation/expression_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

			BOOST_AUTO_TEST_SUITE(ExpressionOperationTest)

				BOOST_AUTO_TEST_CASE(DefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{expression}",
						System::Get().Evaluate("drop find {expression} system")
					);
				}

				BOOST_AUTO_TEST_CASE(BasicTest) {
					BOOST_CHECK_EQUAL(
						(
							"{"
							"1{2}{5}\n"
							"6{7 {8}}"
							"}"
						),
						System::Get().Evaluate("expression {1{2}{5}6{7 {8}}   }")
					);
				}

			BOOST_AUTO_TEST_SUITE_END()

		}

	}

}

	#endif

#endif
