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

#ifndef Om_Operation_BackPullElementOperation_

	#include "om/operation/back_pull_element_operation.hpp"

	#ifdef Om_Macro_Test_

		#include "om/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(BackPullElementOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{[elements]->}",
					System::Get().Evaluate("drop find {[elements]->} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{3}{1{2}}",
					System::Get().Evaluate("[elements]-> {1{2}3}")
				);

				BOOST_CHECK_EQUAL(
					"{2}{1 }",
					System::Get().Evaluate("[elements]-> {1 2}")
				);

				BOOST_CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate("[elements]-> {}")
				);

				BOOST_CHECK_EQUAL(
					"{only}{}",
					System::Get().Evaluate("[elements]-> {only}")
				);

				BOOST_CHECK_EQUAL(
					"[elements]->",
					System::Get().Evaluate("[elements]->")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/literal.hpp"
	#include "om/operation/pull_operation.hpp"

// MARK: - Om::Operation::BackPullElementOperation

	#define Type_ \
	Om::Operation::BackPullElementOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_BackPullElementOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<IncompleteOperation>(
			new PullOperation<
				Literal,
				BackPullElementOperation
			>
		)
	);
}

template <typename TheConsumer>
inline void Type_::Pull(
	Literal & theLiteral,
	TheConsumer & theConsumer
) {
	theLiteral.BackGiveElement(theConsumer);
}

	#undef Type_

#endif
