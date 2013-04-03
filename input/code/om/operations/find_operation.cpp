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

#ifndef Om_Operations_FindOperation_

	#include "om/operations/find_operation.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE(FindOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{find}",
					System::Get().Evaluate("drop find {find} system")
				);
			}

			BOOST_AUTO_TEST_CASE(SimpleTest) {
				BOOST_CHECK_EQUAL(
					(
						"{"
						"b{B}\n"
						"a{A}"
						"}{a{A}}"
					),
					System::Get().Evaluate("find {a}{b{B} a{A}}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"b{B}\n"
						"a{A}"
						"}{a{A}}"
					),
					System::Get().Evaluate("find {a}lexicon{b{B} a{A}}")
				);

				BOOST_CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate("find {a}lexicon{}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"b{B}\n"
						"a{A}"
						"}{}"
					),
					System::Get().Evaluate("find {c}{b{B} a{A}}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"b{B}\n"
						"a{A}\n"
						"{C}"
						"}{}"
					),
					System::Get().Evaluate("find {c}{b{B} a{A} {C}}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"b{B}\n"
						"a{A}\n"
						"{C}"
						"}{{C}}"
					),
					System::Get().Evaluate("find {}{b{B} a{A} {C}}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"b{B}\n"
						"a{A}\n"
						"c"
						"}{c}"
					),
					System::Get().Evaluate("find {c}{b{B} a{A} c}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"b{B}\n"
						"a{A}\n"
						"c{}"
						"}{c{}}"
					),
					System::Get().Evaluate("find {c}{b{B} a{A} c{}}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/lexicon.hpp"

// MARK: - Om::Operations::FindOperation

	#define Type_ \
	Om::Operations::FindOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operations_FindOperation_GetName_();
}

template <typename TheFindOperation>
inline void Type_::GiveElements(
	TheFindOperation & theFindOperation,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
	if (theFindOperation.thisOperator) {
		theConsumer.TakeQuotedElements(*theFindOperation.thisOperator);
	}
}

// MARK: public (non-static)

inline Type_::FindOperation():
thisOperator() {}

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
	if (this->thisOperator) {
		Lexicon theLexicon;
		theLexicon.TakeElements(theProducer);

		Expression theExpression;
		theLexicon.Find(*this->thisOperator).GiveElements(theExpression);

		theEvaluation.TakeQuotedProducer(theExpression);
		theEvaluation.TakeQuotedProducer(theLexicon);
		return true;
	}
	this->thisOperator = boost::in_place();
	assert(this->thisOperator);
	this->thisOperator->TakeElements(theProducer);
	return false;
}

	#undef Type_

#endif
