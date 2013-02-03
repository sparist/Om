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

#if defined( Om_Operations_ProgramOperation_ )

// MARK: Om::Operations::ProgramOperation

	#define Template_ \
	template< typename ThisProgram >

	#define Type_ \
	Om::Operations::ProgramOperation< ThisProgram >

// MARK: public (static)

Template_
inline char const * Type_::GetName() {
	return( ThisProgram::GetName() );
}

Template_
template< typename TheProgramOperation >
inline void Type_::GiveElements(
	TheProgramOperation &,
	Queue & theQueue
) {
	theQueue.TakeElement(
		DefaultOperation<
			ProgramOperation< ThisProgram >
		>::GetOperator()
	);
}

// MARK: public (non-static)

Template_
inline bool Type_::ReadQuotedElements(
	Evaluation & theEvaluation,
	Parser & theParser
) {
	ThisProgram theProgram;
	theProgram.ReadElements( theParser );
	theEvaluation.TakeQuotedQueue( theProgram );
	return( true );
}

Template_
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

Template_
template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
) {
	ThisProgram theProgram;
	theProgram.TakeElements( theQueue );
	theEvaluation.TakeQuotedQueue( theProgram );
	return( true );
}

	#undef Type_
	#undef Template_

#else

	#include "om/operations/program_operation.hpp"

#endif
