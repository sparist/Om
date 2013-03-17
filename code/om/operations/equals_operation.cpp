/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operations_EqualsOperation_

	#include "om/operations/equals_operation.hpp"

	#ifdef Om_Macros_Test_

		#include "om/system.hpp"

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE(EqualsOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{=}",
					System::Get().Evaluate("drop find {=} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{{A}}",
					System::Get().Evaluate("= {A} {A}")
				);

				BOOST_CHECK_EQUAL(
					"{}",
					System::Get().Evaluate("= {A} {Not A}")
				);

				BOOST_CHECK_EQUAL(
					"{{}}",
					System::Get().Evaluate("= {} {}")
				);

				BOOST_CHECK_EQUAL(
					"{}",
					System::Get().Evaluate("= {} {Not empty}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/expression.hpp"

// MARK: - Om::Operations::EqualsOperation

	#define Type_ \
	Om::Operations::EqualsOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operations_EqualsOperation_GetName_();
}

template <typename TheEqualsOperation>
inline void Type_::GiveElements(
	TheEqualsOperation & theEqualsOperation,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
	if (
		!theEqualsOperation.thisOperand.IsEmpty()
	) {
		theConsumer.TakeElement(theEqualsOperation.thisOperand);
	}
}

// MARK: public (non-static)

inline Type_::EqualsOperation():
thisOperand() {}

template <typename TheOperand>
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
) {
	assert(
		!theOperand.IsEmpty()
	);
	if (
		this->thisOperand.IsEmpty()
	) {
		this->thisOperand.Take(theOperand);
		return false;
	}
	Expression theExpression;
	if (this->thisOperand == theOperand) {
		theExpression.TakeOperand(this->thisOperand);
	}
	theEvaluation.TakeQuotedProducer(theExpression);
	return true;
}

template <typename TheProducer>
inline bool Type_::TakeQuotedProducer(
	Evaluation & theEvaluation,
	TheProducer & theProducer
) {
	if (
		this->thisOperand.IsEmpty()
	) {
		this->thisOperand.SetProgram(
			theProducer.GiveProgram()
		);
		return false;
	}
	Expression theExpression;
	if (
		this->IsMatch(theProducer)
	) {
		theExpression.TakeOperand(this->thisOperand);
	}
	theEvaluation.TakeQuotedProducer(theExpression);
	return true;
}

// MARK: private (non-static)

template <typename TheProducer>
inline bool Type_::IsMatch(TheProducer & theProducer) const {
	assert(
		this->thisOperand.GetProgram()
	);
	Program const & theProgram = *this->thisOperand.GetProgram();
	Program const * const theProducerProgram = dynamic_cast<Program const *>(&theProducer);
	if (theProducerProgram) {
		return (*theProducerProgram == theProgram);
	}
	Literal theProducerLiteral;
	theProducerLiteral.TakeElements(theProducer);
	return theProducerLiteral.Equals(theProgram);
}

	#undef Type_

#endif
