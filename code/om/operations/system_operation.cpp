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

#if !defined( Om_Operations_SystemOperation_ )

	#include "om/operations/system_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE( SystemOperationTest )

			BOOST_AUTO_TEST_CASE( DefinitionTest ) {
				BOOST_CHECK_EQUAL(
					"{system}",
					System::Get().Evaluate( "drop find {system} system" )
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

// MARK: - Om::Operations::SystemOperation

	#define Type_ \
	Om::Operations::SystemOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return(
		Om_Operations_SystemOperation_GetName_()
	);
}

inline void Type_::Give( Evaluation & theEvaluation ) {
	theEvaluation.TakeQuotedQueue(
		System::Get().GetLexicon()
	);
}

	#undef Type_

#endif
