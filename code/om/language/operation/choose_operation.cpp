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

#ifndef Om_Language_Operation_ChooseOperation_

	#include "om/language/operation/choose_operation.hpp"

	#ifdef Om_Macro_Test_

		#include "om/language/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

			BOOST_AUTO_TEST_SUITE(ChooseOperationTest)

				BOOST_AUTO_TEST_CASE(DefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{choose}",
						System::Get().Evaluate("drop find {choose} system")
					);
				}

				BOOST_AUTO_TEST_CASE(GeneralTest) {
					BOOST_CHECK_EQUAL(
						"{empty}",
						System::Get().Evaluate("choose{empty}{non-empty}{}")
					);

					BOOST_CHECK_EQUAL(
						"{non-empty}",
						System::Get().Evaluate("choose{empty}{non-empty}{some operators}")
					);
				}

			BOOST_AUTO_TEST_SUITE_END()

		}

	}

}

	#endif

#else

	#include "om/language/literal.hpp"

// MARK: - Om::Language::Operation::ChooseOperation

	#define Type_ \
	Om::Language::Operation::ChooseOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operation_ChooseOperation_GetName_();
}

template <typename TheChooseOperation>
inline void Type_::GiveElements(
	TheChooseOperation & theChooseOperation,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
	if (0 < theChooseOperation.thisOperandCount) {
		theConsumer.TakeElement(theChooseOperation.thisEmptyCase);
		if (1 < theChooseOperation.thisOperandCount) {
			theConsumer.TakeElement(theChooseOperation.thisNonEmptyCase);
		}
	}
}

// MARK: public (non-static)

inline Type_::ChooseOperation():
thisEmptyCase(),
thisNonEmptyCase(),
thisOperandCount() {}

template <typename TheProducer>
inline bool Type_::TakeQuotedProducer(
	Evaluation & theEvaluation,
	TheProducer & theProducer
) {
	Operand theOperand(
		theProducer.GiveProgram()
	);
	return this->TakeOperand(
		theEvaluation,
		theOperand
	);
}

template <typename TheOperand>
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
) {
	assert(
		!theOperand.IsEmpty()
	);
	assert(this->thisOperandCount < 3);
	switch (this->thisOperandCount++) {
	case 0:
		this->thisEmptyCase.Take(theOperand);
		return false;
	case 1:
		this->thisNonEmptyCase.Take(theOperand);
		return false;
	default:
		{
			TheOperand const & theConstOperand = theOperand;
			theEvaluation.TakeOperand(
				theConstOperand.GetProgram()->IsEmpty() ?
				this->thisEmptyCase :
				this->thisNonEmptyCase
			);
		}
		return true;
	}
}

	#undef Type_

#endif
