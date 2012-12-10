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
#if defined( Om_Operations_ProgramOperation_ )

// MARK: Om::Operations::ProgramOperation

	#define Template_ template< typename ThisProgram >

	#define Type_ Om::Operations::ProgramOperation< ThisProgram >

// MARK: public (static)

Template_
inline char const * Type_::GetName()
{
	return( ThisProgram::GetName() );
}

Template_
template< typename TheProgramOperation >
inline void Type_::GiveElements( TheProgramOperation &, Queue & theQueue )
{
	theQueue.TakeElement(
		DefaultEvaluation< ProgramOperation< ThisProgram > >::GetOperator()
	);
}

// MARK: public (non-static)

Template_
inline bool Type_::ReadQuotedElements(
	Expansion & theExpansion,
	Parser & theParser
)
{
	ThisProgram theProgram;
	theProgram.ReadElements( theParser );
	return( this->TakeQuotedQueue( theExpansion, theProgram ) );
}

Template_
template< typename TheOperand >
inline bool Type_::TakeOperand(
	Expansion & theExpansion,
	TheOperand & theOperand
)
{
	return( this->TakeQuotedQueue( theExpansion, *theOperand ) );
}

Template_
template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Expansion & theExpansion,
	TheQueue & theQueue
)
{
	ThisProgram theProgram;
	theProgram.TakeElements( theQueue );
	theExpansion.TakeQuotedQueue( theProgram );
	return( true );
}

	#undef Type_
	#undef Template_

#else
	#include "om/operations/program_operation.hpp"
#endif
