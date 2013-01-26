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

#include "om/operations/expression_operation.hpp"

#if defined( Om_Macros_Test_ )

	#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		SUITE( ExpressionOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{expression}",
					System::Get().Evaluate( "drop find {expression} system" )
				);
			}

			TEST( Basic )
			{
				CHECK_EQUAL(
					(
						"{"
						"1{2}{5}\n"
						"6{7 {8}}"
						"}"
					),
					System::Get().Evaluate( "expression {1{2}{5}6{7 {8}}   }" )
				);
			}
		}
	}
}

#endif
