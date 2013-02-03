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

#include "om/operations/separator_operation.hpp"

#if defined( Om_Macros_Test_ )

	#include "UnitTest++.h"

namespace Om {
	namespace Operations {
		SUITE( SeparatorOperation ) {
			TEST( Definition ) {
				CHECK_EQUAL(
					"{separator}",
					System::Get().Evaluate( "drop find {separator} system" )
				);
			}

			TEST( General ) {
				CHECK_EQUAL(
					"{}",
					System::Get().Evaluate( "separator{}" )
				);

				CHECK_EQUAL(
					"{ \n\t }",
					System::Get().Evaluate( "separator{ \n\t }" )
				);

				CHECK_EQUAL(
					"{   \n\t   }",
					System::Get().Evaluate( "separator{ a {b} \n\t {c} d }" )
				);

				CHECK_EQUAL(
					"{   \n\t   }",
					System::Get().Evaluate( "drop swap separator copy{ a {b} \n\t {c} d }" )
				);
			}
		}
	}
}

#endif
