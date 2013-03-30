/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operations_EvaluateOperation_

	#include "om/operations/evaluate_operation.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE(EvaluateOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{evaluate}",
					System::Get().Evaluate("drop find {evaluate} system")
				);
			}

			BOOST_AUTO_TEST_CASE(BasicTest) {
				BOOST_CHECK_EQUAL(
					"{{A}{A}}",
					System::Get().Evaluate("evaluate {copy {A}}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/environment.hpp"

// MARK: - Om::Operations::EvaluateOperation

	#define Type_ \
	Om::Operations::EvaluateOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operations_EvaluateOperation_GetName_();
}

template <typename TheEvaluateOperation>
inline void Type_::GiveElements(
	TheEvaluateOperation &,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
}

// MARK: public (non-static)

inline Type_::EvaluateOperation() {}

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

template <typename TheProducer>
inline bool Type_::TakeQuotedProducer(
	Evaluation & theEvaluation,
	TheProducer & theProducer
) {
	Expression theExpression;
	{
		Evaluator theScope(
			theExpression,
			theEvaluation.GetTranslator()
		);
		theProducer.GiveElements(theScope);
	}
	theEvaluation.TakeQuotedProducer(theExpression);
	return true;
}

	#undef Type_

#endif
