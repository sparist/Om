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

#ifndef Om_Operation_QuoteOperation_

	#include "om/operation/quote_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(QuoteOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{quote}",
					System::Get().Evaluate("drop find {quote} system")
				);
			}

			BOOST_AUTO_TEST_CASE(SimpleTest) {
				BOOST_CHECK_EQUAL(
					"{{1{2}3}}",
					System::Get().Evaluate("quote {1{2}3}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/literal.hpp"

// MARK: - Om::Operation::QuoteOperation

	#define Type_ \
	Om::Operation::QuoteOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_QuoteOperation_GetName_();
}

template <typename TheQuoteOperation>
inline void Type_::GiveElements(
	TheQuoteOperation &,
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
	theEvaluation.TakeQuotedProducer(theOperand);
	return true;
}

template <typename TheProducer>
inline bool Type_::TakeQuotedProducer(
	Evaluation & theEvaluation,
	TheProducer & theProducer
) {
	Operand theOperand(
		theProducer.GiveProgram()
	);
	theEvaluation.TakeQuotedProducer(theOperand);
	return true;
}

	#undef Type_

#endif
