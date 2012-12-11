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
#if defined( Om_Operations_EqualsOperation_ )

	#include "om/expression.hpp"

// MARK: Om::Operations::EqualsOperation

	#define Type_ Om::Operations::EqualsOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_EqualsOperation_GetName_() );
}

template< typename TheEqualsOperation >
inline void Type_::GiveElements(
	TheEqualsOperation & theEqualsOperation,
	Queue & theQueue
)
{
	theQueue.TakeElement( GetOperator() );
	if( theEqualsOperation.thisOperand ){
		theQueue.TakeElement( *theEqualsOperation.thisOperand );
	}
}

// MARK: public (non-static)

inline Type_::EqualsOperation()
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
	if( this->thisOperand ){
		Expression theExpression;
		if( *this->thisOperand == theOperand ){
			theExpression.TakeOperand( *this->thisOperand );
		}
		theEvaluation.TakeQuotedQueue( theExpression );
		return( true );
	}
	this->thisOperand = boost::in_place();
	this->thisOperand->Take( theOperand );
	return( false );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
)
{
	if( this->thisOperand ){
		Expression theExpression;
		if( theQueue == this->thisOperand->GetProgram() ){
			theExpression.TakeOperand( *this->thisOperand );
		}
		theEvaluation.TakeQuotedQueue( theExpression );
		return( true );
	}
	this->thisOperand = boost::in_place();
	this->thisOperand->SetProgram( theQueue.GiveProgram() );
	return( false );
}

	#undef Type_

#else
	#include "om/operations/equals_operation.hpp"
#endif
