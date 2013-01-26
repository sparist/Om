/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#include "om/symbols.hpp"

#if defined( Om_Macros_Test_ )

	#include "external.hpp"
	#include "om/symbols/operand_symbol.hpp"
	#include "om/symbols/operator_symbol.hpp"
	#include "om/symbols/separator_symbol.hpp"
	#include "UnitTest++.h"

namespace Om
{
	SUITE( Symbols )
	{
		TEST( Stringization )
		{
			CHECK_EQUAL(
				"{test}` \t\n",
				(
					Om_Symbols_OperandSymbol_GetStartString_()
					"test"
					Om_Symbols_OperandSymbol_GetEndString_()
					Om_Symbols_OperatorSymbol_GetEncodeString_()
					Om_Symbols_SeparatorSymbol_GetSpaceString_()
					Om_Symbols_SeparatorSymbol_GetTabString_()
					Om_Symbols_SeparatorSymbol_GetLineString_()
				)
			);
		}
	}
}

#endif
