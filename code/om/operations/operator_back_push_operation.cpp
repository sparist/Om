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

#if defined( Om_Operations_OperatorBackPushOperation_ )

	#include "om/operations/operator_front_push_operation.hpp"
	#include "om/operations/swap_operation.hpp"

// MARK: Om::Operations::OperatorBackPushOperation

	#define Type_ \
	Om::Operations::OperatorBackPushOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return( Om_Operations_OperatorBackPushOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation ) {
	OperatorFrontPushOperation::Give( theEvaluation );
	SwapOperation::Give( theEvaluation );
}

	#undef Type_

#else

	#include "om/operations/operator_back_push_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

// MARK: -

namespace Om {

	namespace Operations {

		SUITE( OperatorBackPushOperation ) {

			TEST( Definition ) {
				CHECK_EQUAL(
					"{operator<-}",
					System::Get().Evaluate( "drop find {operator<-} system" )
				);
			}

		}

	}

}

	#endif

#endif
