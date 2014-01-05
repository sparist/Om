/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Operation_DefaultIncompleteOperation_

	#include "om/operation/default_incomplete_operation.hpp"

#else

	#include "om/evaluator.hpp"

// MARK: - Om::Operation::DefaultIncompleteOperation

	#define Template_ \
	template <typename ThisImplementation>

	#define Type_ \
	Om::Operation::DefaultIncompleteOperation<ThisImplementation>

// MARK: public (static)

Template_
inline Om::Operator const & Type_::GetOperator() {
	static Operator const theOperator(
		ThisImplementation::GetName()
	);
	return theOperator;
}

Template_
inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<ThisImplementation>(new ThisImplementation)
	);
}

// MARK: public (non-static)

Template_
inline Type_::~DefaultIncompleteOperation() {}

Template_
inline void Type_::GiveElements(Consumer & theConsumer) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	ThisImplementation::GiveElements(
		static_cast<ThisImplementation &>(*this),
		theConsumer
	);
}

Template_
inline void Type_::GiveElements(Consumer & theConsumer) const {
	assert(
		dynamic_cast<ThisImplementation const *>(this)
	);
	ThisImplementation::GiveElements(
		static_cast<ThisImplementation const &>(*this),
		theConsumer
	);
}

Template_
inline bool Type_::ReadQuotedElements(
	Evaluation & theEvaluation,
	Parser & theParser
) {
	Literal theLiteral;
	theLiteral.ReadElements(theParser);
	return this->TakeQuotedElements(
		theEvaluation,
		theLiteral
	);
}

Template_
inline bool Type_::TakeElement(
	Evaluation & theEvaluation,
	Operand & theOperand
) {
	assert(
		!theOperand.IsEmpty()
	);
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	return static_cast<ThisImplementation &>(*this).TakeOperand(
		theEvaluation,
		theOperand
	);
}

Template_
inline bool Type_::TakeElement(
	Evaluation & theEvaluation,
	Operand const & theOperand
) {
	assert(
		!theOperand.IsEmpty()
	);
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	return static_cast<ThisImplementation &>(*this).TakeOperand(
		theEvaluation,
		theOperand
	);
}

Template_
inline bool Type_::TakeQuotedElements(
	Evaluation & theEvaluation,
	Producer & theProducer
) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	return static_cast<ThisImplementation &>(*this).TakeQuotedProducer(
		theEvaluation,
		theProducer
	);
}

Template_
inline bool Type_::TakeQuotedElements(
	Evaluation & theEvaluation,
	Producer const & theProducer
) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	return static_cast<ThisImplementation &>(*this).TakeQuotedProducer(
		theEvaluation,
		theProducer
	);
}

	#undef Type_
	#undef Template_

#endif
