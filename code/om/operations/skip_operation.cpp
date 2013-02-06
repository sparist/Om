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

#if !defined( Om_Operations_SkipOperation_ )

	#include "om/operations/skip_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om {

	namespace Operations {

		SUITE( SkipOperation ) {

			TEST( Definition ) {
				CHECK_EQUAL(
					"{skip}",
					System::Get().Evaluate( "drop find {skip} system" )
				);
			}

			TEST( General ) {
				CHECK_EQUAL(
					"{A}{B}{B}",
					System::Get().Evaluate( "skip{copy}{A}{B}" )
				);

				CHECK_EQUAL(
					"{A}{}{}",
					System::Get().Evaluate( "skip{copy}{A}{}" )
				);

				CHECK_EQUAL(
					"{A}{B}",
					System::Get().Evaluate( "skip{}{A}{B}" )
				);
			}

		}

	}

}

	#endif

#else

// MARK: - Om::Operations::SkipOperation

	#define Type_ \
	Om::Operations::SkipOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return( Om_Operations_SkipOperation_GetName_() );
}

template< typename TheSkipOperation >
inline void Type_::GiveElements(
	TheSkipOperation & theSkipOperation,
	Queue & theQueue
) {
	theQueue.TakeElement( GetOperator() );
	if( !theSkipOperation.thisExpression.IsEmpty() ) {
		theQueue.TakeQuotedElements( theSkipOperation.thisExpression );
	}
}

// MARK: public (non-static)

inline Type_::SkipOperation():
thisExpression() {}

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
) {
	assert( !theOperand.IsEmpty() );
	return(
		this->TakeQuotedQueue(
			theEvaluation,
			*theOperand.GetProgram()
		)
	);
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
) {
	if( this->thisExpression.IsEmpty() ) {
		this->thisExpression.TakeElements( theQueue );
		return( this->thisExpression.IsEmpty() );
	}
	theEvaluation.TakeQueue( this->thisExpression );
	theEvaluation.TakeQuotedQueue( theQueue );
	return( true );
}

	#undef Type_

#endif
