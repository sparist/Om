/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Language_Operation_ProgramOperation_

	#include "om/language/operation/program_operation.hpp"

#else

// MARK: - Om::Language::Operation::ProgramOperation

	#define Template_ \
	template <typename ThisProgram>

	#define Type_ \
	Om::Language::Operation::ProgramOperation<ThisProgram>

// MARK: public (static)

Template_
inline char const * Type_::GetName() {
	return ThisProgram::GetName();
}

Template_
template <typename TheProgramOperation>
inline void Type_::GiveElements(
	TheProgramOperation &,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		DefaultIncompleteOperation<
			ProgramOperation<ThisProgram>
		>::GetOperator()
	);
}

// MARK: public (non-static)

Template_
inline bool Type_::ParseQuotedElements(
	Evaluation & theEvaluation,
	Reader & theReader
) {
	ThisProgram theProgram;
	theProgram.ParseElements(theReader);
	theEvaluation.TakeQuotedProducer(theProgram);
	return true;
}

Template_
template <typename TheOperand>
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
) {
	assert(
		!theOperand.IsEmpty()
	);
	return this->TakeQuotedProducer(
		theEvaluation,
		*theOperand.GetProgram()
	);
}

Template_
template <typename TheProducer>
inline bool Type_::TakeQuotedProducer(
	Evaluation & theEvaluation,
	TheProducer & theProducer
) {
	ThisProgram theProgram;
	theProgram.TakeElements(theProducer);
	theEvaluation.TakeQuotedProducer(theProgram);
	return true;
}

	#undef Type_
	#undef Template_

#endif
