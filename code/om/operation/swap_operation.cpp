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

#ifndef Om_Operation_SwapOperation_

	#include "om/operation/swap_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(SwapOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{swap}",
					System::Get().Evaluate("drop find {swap} system")
				);
			}

			BOOST_AUTO_TEST_CASE(SimpleTest) {
				BOOST_CHECK_EQUAL(
					"{4{5}6}{1{2}3}",
					System::Get().Evaluate("swap {1{2}3}{4{5}6}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/literal.hpp"

// MARK: - Om::Operation::SwapOperation

	#define Type_ \
	Om::Operation::SwapOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_SwapOperation_GetName_();
}

template <typename TheSwapOperation>
inline void Type_::GiveElements(
	TheSwapOperation & theSwapOperation,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
	if (
		!theSwapOperation.thisOperand.IsEmpty()
	) {
		theConsumer.TakeElement(theSwapOperation.thisOperand);
	}
}

// MARK: public (non-static)

inline Type_::SwapOperation():
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
	theEvaluation.TakeOperand(this->thisOperand);
	theEvaluation.TakeOperand(theOperand);
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
	theEvaluation.TakeOperand(this->thisOperand);
	theEvaluation.TakeQuotedProducer(theProducer);
	return true;
}

	#undef Type_

#endif
