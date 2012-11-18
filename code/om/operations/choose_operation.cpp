/*!
\file
	\brief
		Om cpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if defined( Om_Operations_ChooseOperation_ )

	#include "om/literal.hpp"

// MARK: Om::Operations::ChooseOperation

	#define Type_ Om::Operations::ChooseOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_ChooseOperation_GetName_() );
}

template< typename TheChooseOperation >
inline void Type_::GiveElements(
	TheChooseOperation & theChooseOperation,
	Queue & theQueue
)
{
	theQueue.TakeElement( GetOperator() );
	if( 0 < theChooseOperation.thisOperandCount ){
		theQueue.TakeElement( theChooseOperation.thisEmptyCase );
		if( 1 < theChooseOperation.thisOperandCount ){
			theQueue.TakeElement( theChooseOperation.thisNonEmptyCase );
		}
	}
}

// MARK: public (non-static)

inline Type_::ChooseOperation()
:
thisEmptyCase(),
thisNonEmptyCase(),
thisOperandCount()
{
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluator & theEvaluator,
	TheQueue & theQueue
)
{
	Operand theOperand( theQueue.GiveProgram() );
	return( this->TakeOperand( theEvaluator, theOperand ) );
}

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluator & theEvaluator,
	TheOperand & theOperand
)
{
	assert( this->thisOperandCount < 3 );
	switch( this->thisOperandCount++ ){
	case 0:
		this->thisEmptyCase.Take( theOperand );
		return( false );
	case 1:
		this->thisNonEmptyCase.Take( theOperand );
		return( false );
	default:
		{
			TheOperand const & theConstOperand = theOperand;
			theEvaluator.TakeOperand(
				theConstOperand.GetChildProgram().IsEmpty() ?
				this->thisEmptyCase :
				this->thisNonEmptyCase
			);
		}
		return( true );
	}
}

	#undef Type_

#else
	#include "om/operations/choose_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( ChooseOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					"{empty}",
					Environment().Evaluate( "choose{empty}{non-empty}{}" )
				);

				CHECK_EQUAL(
					"{non-empty}",
					Environment().Evaluate(
						"choose{empty}{non-empty}{some operators}"
					)
				);
			}
		}
	}
}

	#endif

#endif
