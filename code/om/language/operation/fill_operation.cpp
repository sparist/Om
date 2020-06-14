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

#ifndef Om_Language_Operation_FillOperation_

	#include "om/language/operation/fill_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

			BOOST_AUTO_TEST_SUITE(FillOperationTest)

				BOOST_AUTO_TEST_CASE(DefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{fill}",
						System::Get().Evaluate("drop find {fill} system")
					);
				}

				BOOST_AUTO_TEST_CASE(GeneralTest) {
					BOOST_CHECK_EQUAL(
						(
							"{"
							"a{A}\n"
							"b{B}\n"
							"c{C}"
							"}{Unused}"
						),
						System::Get().Evaluate("fill{a b{B} c}{A}{C}{Unused}")
					);

					BOOST_CHECK_EQUAL(
						"{}{A}{B}",
						System::Get().Evaluate("fill{}{A}{B}")
					);

					BOOST_CHECK_EQUAL(
						"{{Used}}{A}{B}",
						System::Get().Evaluate("fill{{Used}}{A}{B}")
					);
				}
				
				BOOST_AUTO_TEST_CASE(EarlyTerminationTest) {
					BOOST_CHECK_EQUAL(
						(
							"fill{"
							"a{A}\n"
							"b{B}\n"
							"c"
							"}"
						),
						System::Get().Evaluate("fill{a b{B} c}{A}}{C}{Unused}")
					);

					BOOST_CHECK_EQUAL(
						"fill",
						System::Get().Evaluate("fill}")
					);
				}

			BOOST_AUTO_TEST_SUITE_END()

		}

	}

}

	#endif

#else

	#ifndef Om_Macro_Precompilation_

		#include "boost/utility/in_place_factory.hpp"

	#endif

// MARK: - Om::Language::Operation::FillOperation

	#define Type_ \
	Om::Language::Operation::FillOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operation_FillOperation_GetName_();
}

template <typename TheFillOperation>
inline void Type_::GiveElements(
	TheFillOperation & theFillOperation,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
	if (theFillOperation.thisFormRange) {
		theConsumer.TakeQuotedElements(theFillOperation.thisExpression);
	}
}

// MARK: public (non-static)

inline Type_::FillOperation():
thisExpression(),
thisFormRange() {}

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
	if (this->thisFormRange) {
		FormRange & theFormRange = *this->thisFormRange;
		assert(
			theFormRange &&
			!this->thisExpression.IsEmpty()
		);
		assert(
			!Form::OperandRange<Operand const>(*theFormRange) &&
			"The Form should have no Operands."
		);
		theFormRange->BackTakeQuotedProducer(theProducer);
		theFormRange.Pop();
	} else {
		this->thisExpression.TakeElements(theProducer);
		this->thisFormRange = boost::in_place(
			boost::ref(this->thisExpression)
		);
	}
	assert(this->thisFormRange);

	// Find the next Form with no Operands and return false, or return true if none.
	for (
		FormRange & theFormRange = *this->thisFormRange;
		theFormRange;
		theFormRange.Pop()
	) {
		if (
			!Form::OperandRange<Operand const>(*theFormRange)
		) {
			return false;
		}
	}
	theEvaluation.TakeQuotedProducer(this->thisExpression);
	return true;
}

	#undef Type_

#endif
