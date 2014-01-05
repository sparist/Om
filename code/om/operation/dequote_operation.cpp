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
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operation_DequoteOperation_

	#include "om/operation/dequote_operation.hpp"

	#ifdef Om_Macro_Test_

		#include "om/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(DequoteOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{dequote}",
					System::Get().Evaluate("drop find {dequote} system")
				);
			}

			BOOST_AUTO_TEST_CASE(SimpleTest) {
				BOOST_CHECK_EQUAL(
					(
						"1{2}\n"
						"3"
					),
					System::Get().Evaluate("dequote {1{2}3}")
				);
			}

			BOOST_AUTO_TEST_CASE(SimpleDequoteThenEvaluateTest) {
				BOOST_CHECK_EQUAL(
					(
						"A{b}\n"
						"c"
					),
					System::Get().Evaluate("define {a {A}} {dequote {a{b}c}}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

// MARK: - Om::Operation::DequoteOperation

	#define Type_ \
	Om::Operation::DequoteOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_DequoteOperation_GetName_();
}

template <typename TheDequoteOperation>
inline void Type_::GiveElements(
	TheDequoteOperation &,
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
	theEvaluation.TakeProducer(theProducer);
	return true;
}

	#undef Type_

#endif
