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

#ifndef Om_Symbol_

	#include "om/symbol/symbol.hpp"

	#ifdef Om_Macros_Test_

		#include "om/symbol/operand_symbol.hpp"
		#include "om/symbol/operator_symbol.hpp"
		#include "om/symbol/separator_symbol.hpp"

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(SymbolTest)

		BOOST_AUTO_TEST_CASE(StringizationTest) {
			BOOST_CHECK_EQUAL(
				"{test}` \t\n",
				(
					Om_Symbol_OperandSymbol_GetStartString_()
					"test"
					Om_Symbol_OperandSymbol_GetEndString_()
					Om_Symbol_OperatorSymbol_GetEncodeString_()
					Om_Symbol_SeparatorSymbol_GetSpaceString_()
					Om_Symbol_SeparatorSymbol_GetTabString_()
					Om_Symbol_SeparatorSymbol_GetLineString_()
				)
			);
		}

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#endif
