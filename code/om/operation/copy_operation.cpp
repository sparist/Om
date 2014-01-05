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

#ifndef Om_Operation_CopyOperation_

	#include "om/operation/copy_operation.hpp"

	#ifdef Om_Macro_Test_

		#include "om/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(CopyOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{copy}",
					System::Get().Evaluate("drop find {copy} system")
				);
			}

			BOOST_AUTO_TEST_CASE(SimpleTest) {
				BOOST_CHECK_EQUAL(
					"{1{2}3}{1{2}3}",
					System::Get().Evaluate("copy {1{2}3}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/literal.hpp"

// MARK: - Om::Operation::CopyOperation

	#define Type_ \
	Om::Operation::CopyOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_CopyOperation_GetName_();
}

template <typename TheCopyOperation>
inline void Type_::GiveElements(
	TheCopyOperation &,
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
	{
		Operand const & theConstOperand(theOperand);
		theEvaluation.TakeOperand(theConstOperand);
	}
	theEvaluation.TakeOperand(theOperand);
	return true;
}

template <typename TheProducer>
inline bool Type_::TakeQuotedProducer(
	Evaluation & theEvaluation,
	TheProducer & theProducer
) {
	{
		TheProducer const & theConstProducer(theProducer);
		theEvaluation.TakeQuotedProducer(theConstProducer);
	}
	theEvaluation.TakeQuotedProducer(theProducer);
	return true;
}

	#undef Type_

#endif
