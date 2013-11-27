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

#ifndef Om_Operation_SkipOperation_

	#include "om/operation/skip_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(SkipOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{skip}",
					System::Get().Evaluate("drop find {skip} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{A}{B}{B}",
					System::Get().Evaluate("skip{copy}{A}{B}")
				);

				BOOST_CHECK_EQUAL(
					"{A}{}{}",
					System::Get().Evaluate("skip{copy}{A}{}")
				);

				BOOST_CHECK_EQUAL(
					"{A}{B}",
					System::Get().Evaluate("skip{}{A}{B}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

// MARK: - Om::Operation::SkipOperation

	#define Type_ \
	Om::Operation::SkipOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_SkipOperation_GetName_();
}

template <typename TheSkipOperation>
inline void Type_::GiveElements(
	TheSkipOperation & theSkipOperation,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
	if (
		!theSkipOperation.thisExpression.IsEmpty()
	) {
		theConsumer.TakeQuotedElements(theSkipOperation.thisExpression);
	}
}

// MARK: public (non-static)

inline Type_::SkipOperation() :
thisExpression() {}

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
	if (
		this->thisExpression.IsEmpty()
	) {
		this->thisExpression.TakeElements(theProducer);
		return this->thisExpression.IsEmpty();
	}
	theEvaluation.TakeProducer(this->thisExpression);
	theEvaluation.TakeQuotedProducer(theProducer);
	return true;
}

	#undef Type_

#endif
