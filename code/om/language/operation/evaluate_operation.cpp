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

#ifndef Om_Language_Operation_EvaluateOperation_

	#include "om/language/operation/evaluate_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

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

}

	#endif

#else

	#include "om/language/environment.hpp"

// MARK: - Om::Language::Operation::EvaluateOperation

	#define Type_ \
	Om::Language::Operation::EvaluateOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operation_EvaluateOperation_GetName_();
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
