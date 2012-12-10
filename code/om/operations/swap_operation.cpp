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
	if( theSwapOperation.thisOperand ){
		theQueue.TakeElement( *theSwapOperation.thisOperand );
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
	Expansion & theExpansion,
	TheOperand & theOperand
)
{
	if( this->thisOperand ){
		theExpansion.TakeOperand( *this->thisOperand );
		theExpansion.TakeOperand( theOperand );
		return( true );
	}
	this->thisOperand = boost::in_place();
	assert( this->thisOperand );
	this->thisOperand->Take( theOperand );
	return( false );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Expansion & theExpansion,
	TheQueue & theQueue
)
{
	if( this->thisOperand ){
		theExpansion.TakeOperand( *this->thisOperand );
		theExpansion.TakeQuotedQueue( theQueue );
		return( true );
	}
	this->thisOperand = boost::in_place();
	assert( this->thisOperand );
	this->thisOperand->SetProgram( theQueue.GiveProgram() );
	return( false );
}

	#undef Type_

#else
	#include "om/operations/swap_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( SwapOperation )
		{
			TEST( Simple )
			{
				CHECK_EQUAL(
					"{4{5}6}{1{2}3}",
					Environment().Evaluate( "swap {1{2}3}{4{5}6}" )
				);
			}
		}
	}
}

	#endif

#endif
