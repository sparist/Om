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

#ifndef Om_Language_Operation_InjectOperation_

	#include "om/language/operation/inject_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

			BOOST_AUTO_TEST_SUITE(InjectOperationTest)

				BOOST_AUTO_TEST_CASE(DefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{inject}",
						System::Get().Evaluate("drop find {inject} system")
					);
				}

				BOOST_AUTO_TEST_CASE(GeneralTest) {
					BOOST_CHECK_EQUAL(
						(
							"{"
							"{"
							"a{{A}}\n"
							"b{{B}}\n"
							"c{{C}}"
							"}"
							"}{D}{E}"
						),
						System::Get().Evaluate("inject {quote} {fill {a b{{B}} c}} {A} {C} {D} {E}")
					);

					BOOST_CHECK_EQUAL(
						(
							"{"
							"{"
							"a{A}\n"
							"b{B}\n"
							"c{A}\n"
							"d{C}"
							"}{C}"
							"}{D}{E}"
						),
						System::Get().Evaluate("inject {copy} {fill {a b{B} c d}} {A} {C} {D} {E}")
					);

					BOOST_CHECK_EQUAL(
						(
							"inject{drop}{"
							"fill{"
							"a\n"
							"b{B}\n"
							"c\n"
							"d"
							"}"
							"}"
						),
						System::Get().Evaluate("inject {drop} {fill {a b{B} c d}} {A} {C} {D} {E}")
					);
				}

				BOOST_AUTO_TEST_CASE(EmptyInjectorTest) {
					BOOST_CHECK_EQUAL(
						(
							"{"
							"{"
							"a{A}\n"
							"b{B}\n"
							"c{C}"
							"}"
							"}{D}{E}"
						),
						System::Get().Evaluate("inject {} {fill {a b{B} c}} {A} {C} {D} {E}")
					);
				}

				BOOST_AUTO_TEST_CASE(EmptyOperationTest) {
					BOOST_CHECK_EQUAL(
						"{}{A}{C}{D}{E}",
						System::Get().Evaluate("inject {quote} {} {A} {C} {D} {E}")
					);
				}

				BOOST_AUTO_TEST_CASE(FlushWithNoOperandsTest) {
					BOOST_CHECK_EQUAL(
						"inject",
						System::Get().Evaluate("inject }")
					);
				}

				BOOST_AUTO_TEST_CASE(FlushWithOneOperandTest) {
					BOOST_CHECK_EQUAL(
						"inject{quote}",
						System::Get().Evaluate("inject {quote} }")
					);
				}

				BOOST_AUTO_TEST_CASE(FlushWithTwoOperandsTest) {
					BOOST_CHECK_EQUAL(
						"inject{quote}{copy}",
						System::Get().Evaluate("inject {quote} {copy} }")
					);
				}

				BOOST_AUTO_TEST_CASE(FlushWithMoreThanTwoOperandsTest) {
					BOOST_CHECK_EQUAL(
						(
							"inject{quote}{"
							"fill{"
							"a{A}\n"
							"b{B}\n"
							"c"
							"}"
							"}"
						),
						System::Get().Evaluate("inject {quote} {fill {a b c} {A} {B} }")
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

// MARK: - Om::Language::Operation::InjectOperation

	#define Type_ \
	Om::Language::Operation::InjectOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operation_InjectOperation_GetName_();
}

template <typename TheInjectOperation>
inline void Type_::GiveElements(
	TheInjectOperation & theInjectOperation,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
	if (theInjectOperation.thisScope) {
		theConsumer.TakeQuotedElements(theInjectOperation.thisInjector);
		if (
			!theInjectOperation.thisScope->IsEmpty()
		) {
			Expression theExpression;
			theExpression.Take(theInjectOperation.thisOutput);
			theInjectOperation.thisScope->GiveElements(theExpression);
			theConsumer.TakeQuotedElements(theExpression);
		}
	}
}

// MARK: public (non-static)

inline Type_::InjectOperation():
thisInjector(),
thisOutput(),
thisScope() {}

template <typename TheProducer>
inline bool Type_::TakeQuotedProducer(
	Evaluation & theEvaluation,
	TheProducer & theProducer
) {
	if (this->thisScope) {
		if (
			this->thisScope->IsEmpty()
		) {
			theProducer.GiveElements(*this->thisScope);
		} else {
			{
				Expression const & theInjector = this->thisInjector;
				theInjector.GiveElements(*this->thisScope);
			}
			this->thisScope->TakeQuotedProducer(theProducer);
		}

		if (
			this->thisScope->IsEmpty()
		) {
			theEvaluation.TakeQuotedProducer(this->thisOutput);
			return true;
		}
	} else {
		this->thisScope = boost::in_place(
			boost::ref(this->thisOutput),
			boost::ref(
				theEvaluation.GetTranslator()
			)
		);
		this->thisInjector.TakeElements(theProducer);
	}
	return false;
}

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

	#undef Type_

#endif
