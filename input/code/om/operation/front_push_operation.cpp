/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operation_FrontPushOperation_

	#include "om/operation/front_push_operation.hpp"

#else

	#include "om/operation/program_operation.hpp"

// MARK: - Om::Operation::FrontPushOperation

	#define Template_ \
	template < \
		typename ThisProgram, \
		typename ThisImplementation \
	>

	#define Type_ \
	Om::Operation::FrontPushOperation< \
		ThisProgram, \
		ThisImplementation \
	>

// MARK: public (static)

Template_
template <typename TheFrontPushOperation>
inline void Type_::GiveElements(
	TheFrontPushOperation & theFrontPushOperation,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
	if (
		!theFrontPushOperation.thisProgram.IsEmpty()
	) {
		theConsumer.TakeQuotedElements(theFrontPushOperation.thisProgram);
	}
}

// MARK: public (non-static)

Template_
inline Type_::FrontPushOperation() :
thisProgram()
{}

Template_
template <typename TheProducer>
inline bool Type_::TakeQuotedProducer(
	Evaluation & theEvaluation,
	TheProducer & theProducer
) {
	if (
		this->thisProgram.IsEmpty()
	) {
		this->thisProgram.TakeElements(theProducer);
		if (
			this->thisProgram.IsEmpty()
		) {
			ProgramOperation<ThisProgram>::Give(theEvaluation);
			return true;
		}
		return false;
	}
	this->thisProgram.TakeElements(theProducer);
	theEvaluation.TakeQuotedProducer(this->thisProgram);
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

// MARK: private (static)

Template_
inline Om::Operator const & Type_::GetOperator() {
	static Operator const theOperator(
		ThisImplementation::GetName()
	);
	return theOperator;
}

	#undef Type_
	#undef Template_

#endif
