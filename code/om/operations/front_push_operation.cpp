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
#if defined( Om_Operations_FrontPushOperation_ )

	#include "om/operations/program_operation.hpp"

// MARK: Om::Operations::FrontPushOperation

	#define Template_ template< \
		typename ThisProgram, \
		typename ThisImplementation \
	>

	#define Type_ Om::Operations::FrontPushOperation< \
		ThisProgram, \
		ThisImplementation \
	>

// MARK: public (static)

Template_
template< typename TheFrontPushOperation >
inline void Type_::GiveElements(
	TheFrontPushOperation & theFrontPushOperation,
	Queue & theQueue
)
{
	theQueue.TakeElement( GetOperator() );
	if( !theFrontPushOperation.thisProgram.IsEmpty() ){
		theQueue.TakeQuotedElements( theFrontPushOperation.thisProgram );
	}
}

// MARK: public (non-static)

Template_
inline Type_::FrontPushOperation()
:
thisProgram()
{
}

Template_
template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluator & theEvaluator,
	TheQueue & theQueue
)
{
	if( this->thisProgram.IsEmpty() ){
		this->thisProgram.TakeElements( theQueue );
		if( this->thisProgram.IsEmpty() ){
			ProgramOperation< ThisProgram >::Give( theEvaluator );
			return( true );
		}
		return( false );
	}
	this->thisProgram.TakeElements( theQueue );
	theEvaluator.TakeQuotedQueue( this->thisProgram );
	return( true );
}

Template_
template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluator & theEvaluator,
	TheOperand & theOperand
)
{
	return(
		this->TakeQuotedQueue( theEvaluator, theOperand.GetChildProgram() )
	);
}

// MARK: private (static)

Template_
inline Om::Operator const & Type_::GetOperator()
{
	static Operator const theOperator( ThisImplementation::GetName() );
	return( theOperator );
}

	#undef Type_
	#undef Template_

#else
	#include "om/operations/front_push_operation.hpp"
#endif
