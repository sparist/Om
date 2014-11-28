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

#ifndef Om_Language_Symbol_

	#include "om/language/symbol.hpp"

	#ifdef Om_Macro_Test_

		#include "om/language/symbol/operand_symbol.hpp"
		#include "om/language/symbol/operator_symbol.hpp"
		#include "om/language/symbol/separator_symbol.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		BOOST_AUTO_TEST_SUITE(SymbolTest)

			BOOST_AUTO_TEST_CASE(StringizationTest) {
				BOOST_CHECK_EQUAL(
					"{test}` \t\n",
					(
						Om_Language_Symbol_OperandSymbol_GetStartString_()
						"test"
						Om_Language_Symbol_OperandSymbol_GetEndString_()
						Om_Language_Symbol_OperatorSymbol_GetEncodeString_()
						Om_Language_Symbol_SeparatorSymbol_GetSpaceString_()
						Om_Language_Symbol_SeparatorSymbol_GetTabString_()
						Om_Language_Symbol_SeparatorSymbol_GetLineString_()
					)
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#endif
