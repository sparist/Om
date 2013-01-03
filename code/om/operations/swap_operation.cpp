/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.1
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
#if defined( Om_Operations_SwapOperation_ )

	#include "om/literal.hpp"

// MARK: Om::Operations::SwapOperation

	#define Type_ Om::Operations::SwapOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_SwapOperation_GetName_() );
}

template< typename TheSwapOperation >
inline void Type_::GiveElements(
	TheSwapOperation & theSwapOperation,
	Queue & theQueue
)
{
	theQueue.TakeElement( GetOperator() );
	if( !theSwapOperation.thisOperand.IsEmpty() ){
		theQueue.TakeElement( theSwapOperation.thisOperand );
	}
}

// MARK: public (non-static)

inline Type_::SwapOperation()
:
thisOperand()
{
}

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
)
{
	assert( !theOperand.IsEmpty() );
	if( this->thisOperand.IsEmpty() ){
		this->thisOperand.Take( theOperand );
		return( false );
	}
	theEvaluation.TakeOperand( this->thisOperand );
	theEvaluation.TakeOperand( theOperand );
	return( true );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
)
{
	if( this->thisOperand.IsEmpty() ){
		this->thisOperand.SetProgram( theQueue.GiveProgram() );
		return( false );
	}
	theEvaluation.TakeOperand( this->thisOperand );
	theEvaluation.TakeQuotedQueue( theQueue );
	return( true );
}

	#undef Type_

#else
	#include "om/operations/swap_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( SwapOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{swap}",
					System::Get().Evaluate( "drop find {swap} system" )
				);
			}

			TEST( Simple )
			{
				CHECK_EQUAL(
					"{4{5}6}{1{2}3}",
					System::Get().Evaluate( "swap {1{2}3}{4{5}6}" )
				);
			}
		}
	}
}

	#endif

#endif
