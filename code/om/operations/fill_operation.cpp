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
#if defined( Om_Operations_FillOperation_ )

// MARK: Om::Operations::FillOperation

	#define Type_ Om::Operations::FillOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_FillOperation_GetName_() );
}

template< typename TheFillOperation >
inline void Type_::GiveElements(
	TheFillOperation & theFillOperation,
	Queue & theQueue
)
{
	theQueue.TakeElement( GetOperator() );
	if( theFillOperation.thisFormRange ){
		theQueue.TakeQuotedElements( theFillOperation.thisExpression );
	}
}

// MARK: public (non-static)

inline Type_::FillOperation()
:
thisExpression(),
thisFormRange()
{
}

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
)
{
	return( this->TakeQuotedQueue( theEvaluation, theOperand.GetProgram() ) );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
)
{
	if( this->thisFormRange ){
		FormRange & theFormRange = *this->thisFormRange;
		assert( theFormRange && !this->thisExpression.IsEmpty() );
		assert(
			!Form::OperandRange< Operand const >( *theFormRange ) &&
			"The Form should have no Operands."
		);
		theFormRange->BackTakeQuotedQueue( theQueue );
		theFormRange.Pop();
	} else{
		this->thisExpression.TakeElements( theQueue );
		this->thisFormRange = boost::in_place(
			boost::ref( this->thisExpression )
		);
	}
	assert( this->thisFormRange );

	/*
	Find the next Form with no Operands and return false, or return true if
	none.
	*/
	for( 
		FormRange & theFormRange = *this->thisFormRange;
		theFormRange;
		theFormRange.Pop()
	){
		if( !Form::OperandRange< Operand const >( *theFormRange ) ){
			return( false );
		}
	}
	theEvaluation.TakeQuotedQueue( this->thisExpression );
	return( true );
}

	#undef Type_

#else
	#include "om/operations/fill_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( FillOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					(
						"{"
							"a{A}\n"
							"b{B}\n"
							"c{C}"
						"}{Unused}"
					),
					Environment().Evaluate( "fill{a b{B} c}{A}{C}{Unused}" )
				);

				CHECK_EQUAL(
					"{}{A}{B}",
					Environment().Evaluate( "fill{}{A}{B}" )
				);

				CHECK_EQUAL(
					"{{Used}}{A}{B}",
					Environment().Evaluate( "fill{{Used}}{A}{B}" )
				);
			}
			
			TEST( EarlyTermination )
			{
				CHECK_EQUAL(
					(
						"fill{"
							"a{A}\n"
							"b{B}\n"
							"c"
						"}"
					),
					Environment().Evaluate( "fill{a b{B} c}{A}}{C}{Unused}" )
				);

				CHECK_EQUAL(
					"fill",
					Environment().Evaluate( "fill}" )
				);
			}
		}
	}
}

	#endif

#endif
