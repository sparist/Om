/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_EqualsOperation_ )

	#include "om/operations/equals_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

namespace Om {

	namespace Operations {

		SUITE( EqualsOperation ) {

			TEST( Definition ) {
				CHECK_EQUAL(
					"{=}",
					System::Get().Evaluate( "drop find {=} system" )
				);
			}

			TEST( General ) {
				CHECK_EQUAL(
					"{{A}}",
					System::Get().Evaluate( "= {A} {A}" )
				);

				CHECK_EQUAL(
					"{}",
					System::Get().Evaluate( "= {A} {Not A}" )
				);

				CHECK_EQUAL(
					"{{}}",
					System::Get().Evaluate( "= {} {}" )
				);

				CHECK_EQUAL(
					"{}",
					System::Get().Evaluate( "= {} {Not empty}" )
				);
			}

		}

	}

}

	#endif

#else

	#include "om/expression.hpp"

// MARK: - Om::Operations::EqualsOperation

	#define Type_ \
	Om::Operations::EqualsOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return(
		Om_Operations_EqualsOperation_GetName_()
	);
}

template< typename TheEqualsOperation >
inline void Type_::GiveElements(
	TheEqualsOperation & theEqualsOperation,
	Queue & theQueue
) {
	theQueue.TakeElement(
		GetOperator()
	);
	if(
		!theEqualsOperation.thisOperand.IsEmpty()
	) {
		theQueue.TakeElement( theEqualsOperation.thisOperand );
	}
}

// MARK: public (non-static)

inline Type_::EqualsOperation():
thisOperand() {}

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
) {
	assert(
		!theOperand.IsEmpty()
	);
	if(
		this->thisOperand.IsEmpty()
	) {
		this->thisOperand.Take( theOperand );
		return( false );
	}
	Expression theExpression;
	if( this->thisOperand == theOperand ) {
		theExpression.TakeOperand( this->thisOperand );
	}
	theEvaluation.TakeQuotedQueue( theExpression );
	return( true );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
) {
	if(
		this->thisOperand.IsEmpty()
	) {
		this->thisOperand.SetProgram(
			theQueue.GiveProgram()
		);
		return( false );
	}
	Expression theExpression;
	if(
		theQueue == *this->thisOperand.GetProgram()
	) {
		theExpression.TakeOperand( this->thisOperand );
	}
	theEvaluation.TakeQuotedQueue( theExpression );
	return( true );
}

	#undef Type_

#endif
