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
#if defined( Om_Operations_PullOperation_ )

// MARK: Om::Operations::PullOperation

	#define Template_ template< \
		typename ThisProgram, \
		typename ThisImplementation \
	>

	#define Type_ Om::Operations::PullOperation< \
		ThisProgram, \
		ThisImplementation \
	>

// MARK: public (static)

Template_
template< typename ThePullOperation >
inline void Type_::GiveElements( ThePullOperation &, Queue & theQueue )
{
	theQueue.TakeElement( GetOperator() );
}

// MARK: public (non-static)

Template_
inline bool Type_::ReadQuotedElements(
	Evaluation & theEvaluation,
	Parser & theParser
)
{
	ThisProgram theProgram;
	theProgram.ReadElements( theParser );
	return( this->TakeQuotedElements( theEvaluation, theProgram ) );
}

Template_
template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
)
{
	return( this->TakeQuotedQueue( theEvaluation, theOperand.GetProgram() ) );
}

Template_
template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
)
{
	ThisProgram theProgramToPullFrom;
	theProgramToPullFrom.TakeElements( theQueue );

	ThisProgram thePulledProgram;
	ThisImplementation::Pull( theProgramToPullFrom, thePulledProgram );

	theEvaluation.TakeQuotedQueue( theProgramToPullFrom );
	theEvaluation.TakeQuotedQueue( thePulledProgram );
	return( true );
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
	#include "om/operations/pull_operation.hpp"
#endif
