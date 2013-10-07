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

#ifndef Om_Operation_NormalizeOperation_

	#include "om/operation/normalize_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(NormalizeOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{normalize}",
					System::Get().Evaluate("drop find {normalize} system")
				);
			}

			BOOST_AUTO_TEST_CASE(SimpleTest) {
				BOOST_CHECK_EQUAL(
					(
						"{"
						"\xE1\x84\x80"
						"\xE1\x85\xA1"
						"\xE1\x86\xA8"
						"}"
					),
					System::Get().Evaluate(
						"normalize {"
						"\xEA\xB0\x81"
						"}"
					)
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

// MARK: - Om::Operation::NormalizeOperation

	#define Type_ \
	Om::Operation::NormalizeOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_NormalizeOperation_GetName_();
}

template <typename TheNormalizeOperation>
inline void Type_::GiveElements(
	TheNormalizeOperation &,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
}

// MARK: public (non-static)

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
	Operator theOperator;
	theOperator.TakeElements(theProducer);
	theOperator.Normalize();
	theEvaluation.TakeQuotedProducer(theOperator);
	return true;
}

	#undef Type_

#endif
