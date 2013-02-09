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

#if !defined( Om_Operations_FrontPullOperatorOperation_ )

	#include "om/operations/front_pull_operator_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

namespace Om {

	namespace Operations {

		SUITE( FrontPullOperatorOperation ) {

			TEST( Definition ) {
				CHECK_EQUAL(
					"{operator<-elements}",
					System::Get().Evaluate( "drop find {operator<-elements} system" )
				);
			}

			TEST( General ) {
				CHECK_EQUAL(
					"{1}{{2}3}",
					System::Get().Evaluate( "operator<-elements {1{2}3}" )
				);

				CHECK_EQUAL(
					"{}{{2}3}",
					System::Get().Evaluate( "operator<-elements {{2}3}" )
				);

				CHECK_EQUAL(
					"{1}{ 2}",
					System::Get().Evaluate( "operator<-elements {1 2}" )
				);

				CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate( "operator<-elements {}" )
				);

				CHECK_EQUAL(
					"{only}{}",
					System::Get().Evaluate( "operator<-elements {only}" )
				);

				CHECK_EQUAL(
					"operator<-elements",
					System::Get().Evaluate( "operator<-elements" )
				);
			}

		}

	}

}

	#endif

#else

	#include "om/literal.hpp"
	#include "om/operations/pull_operation.hpp"

// MARK: - Om::Operations::FrontPullOperatorOperation

	#define Type_ \
	Om::Operations::FrontPullOperatorOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return(
		Om_Operations_FrontPullOperatorOperation_GetName_()
	);
}

inline void Type_::Give( Evaluation & theEvaluation ) {
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation<
				Literal,
				FrontPullOperatorOperation
			>
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull(
	Literal & theLiteral,
	TheQueue & theQueue
) {
	theLiteral.FrontGive< Operator >( theQueue );
}

	#undef Type_

#endif
