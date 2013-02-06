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

#if !defined( Om_Operations_FrontPullOperandOperation_ )

	#include "om/operations/front_pull_operand_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

namespace Om {

	namespace Operations {

		SUITE( FrontPullOperandOperation ) {

			TEST( Definition ) {
				CHECK_EQUAL(
					"{operand<-elements}",
					System::Get().Evaluate( "drop find {operand<-elements} system" )
				);
			}

			TEST( General ) {
				CHECK_EQUAL(
					"{}{1{2}3}",
					System::Get().Evaluate( "operand<-elements {1{2}3}" )
				);

				CHECK_EQUAL(
					"{{1}}{2}",
					System::Get().Evaluate( "operand<-elements {{1}2}" )
				);

				CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate( "operand<-elements {}" )
				);

				CHECK_EQUAL(
					"{{only}}{}",
					System::Get().Evaluate( "operand<-elements {{only}}" )
				);

				CHECK_EQUAL(
					"operand<-elements",
					System::Get().Evaluate( "operand<-elements" )
				);
			}

		}

	}

}

	#endif

#else

	#include "om/literal.hpp"
	#include "om/operations/pull_operation.hpp"

// MARK: - Om::Operations::FrontPullOperandOperation

	#define Type_ \
	Om::Operations::FrontPullOperandOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return( Om_Operations_FrontPullOperandOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation ) {
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation<
				Literal,
				FrontPullOperandOperation
			>
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull(
	Literal & theLiteral,
	TheQueue & theQueue
) {
	theLiteral.FrontGive< Operand >( theQueue );
}

	#undef Type_

#endif
