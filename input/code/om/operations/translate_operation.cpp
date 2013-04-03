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

#ifndef Om_Operations_TranslateOperation_

	#include "om/operations/translate_operation.hpp"

#else

	#include "om/expression.hpp"

// MARK: - Om::Operations::TranslateOperation

	#define Template_ \
	template <typename ThisImplementation>

	#define Type_ \
	Om::Operations::TranslateOperation<ThisImplementation>

// MARK: public (static)

Template_
template <typename TheTranslateOperation>
inline void Type_::GiveElements(
	TheTranslateOperation & theTranslateOperation,
	Consumer & theConsumer
) {
	assert(
		typeid(TheTranslateOperation) == typeid(ThisImplementation)
	);
	theConsumer.TakeElement(
		ThisImplementation::GetOperator()
	);
	if (theTranslateOperation.thisLexicon) {
		theConsumer.TakeQuotedElements(*theTranslateOperation.thisLexicon);
	}
}

// MARK: public (non-static)

Template_
inline Type_::~TranslateOperation() {}

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
	if (this->thisLexicon) {
		{
			// Perform the translation. Note that this uses this->thisLexicon and must be done before the lexicon is given to the Evaluation.
			Expression theExpression;
			assert(
				dynamic_cast<ThisImplementation *>(this)
			);
			static_cast<ThisImplementation &>(*this).Translate(
				theEvaluation.GetTranslator(),
				theProducer,
				theExpression
			);
			theEvaluation.TakeQuotedProducer(theExpression);
		}
		theEvaluation.TakeQuotedProducer(*this->thisLexicon);
		return true;
	}
	this->thisLexicon = boost::in_place();
	assert(this->thisLexicon);
	this->thisLexicon->TakeElements(theProducer);
	return false;
}

// MARK: protected (non-static)

Template_
inline Type_::TranslateOperation():
thisLexicon() {}

	#undef Type_
	#undef Template_

#endif
