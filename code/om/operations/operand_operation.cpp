/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_OperandOperation_ )

	#include "om/operations/operand_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om {

	namespace Operations {

		SUITE( OperandOperation ) {

			TEST( Definition ) {
				CHECK_EQUAL(
					"{operand}",
					System::Get().Evaluate( "drop find {operand} system" )
				);
			}

			TEST( General ) {
				CHECK_EQUAL(
					"{}",
					System::Get().Evaluate( "operand{}" )
				);

				CHECK_EQUAL(
					"{{}}",
					System::Get().Evaluate( "operand{{}}" )
				);

				CHECK_EQUAL(
					"{{b}}",
					System::Get().Evaluate( "operand{ a {b} {c} d }" )
				);

				CHECK_EQUAL(
					"{{b}}",
					System::Get().Evaluate( "drop swap operand copy{ a {b} {c} d }" )
				);
			}

		}

	}

}

	#endif

#endif
