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

#ifndef Om_Operation_BackPullSeparatorOperation_

	#include "om/operation/back_pull_separator_operation.hpp"

	#ifdef Om_Macro_Test_

		#include "om/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(BackPullSeparatorOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{[elements|separator]->}",
					System::Get().Evaluate("drop find {[elements|separator]->} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{ }{1{2}}",
					System::Get().Evaluate("[elements|separator]-> {1{2} }")
				);

				BOOST_CHECK_EQUAL(
					"{}{1{2}}",
					System::Get().Evaluate("[elements|separator]-> {1{2}}")
				);

				BOOST_CHECK_EQUAL(
					"{}{1 2}",
					System::Get().Evaluate("[elements|separator]-> {1 2}")
				);

				BOOST_CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate("[elements|separator]-> {}")
				);

				BOOST_CHECK_EQUAL(
					"{ }{}",
					System::Get().Evaluate("[elements|separator]-> { }")
				);

				BOOST_CHECK_EQUAL(
					"[elements|separator]->",
					System::Get().Evaluate("[elements|separator]->")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/literal.hpp"
	#include "om/operation/pull_operation.hpp"

// MARK: - Om::Operation::BackPullSeparatorOperation

	#define Type_ \
	Om::Operation::BackPullSeparatorOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_BackPullSeparatorOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<IncompleteOperation>(
			new PullOperation<
				Literal,
				BackPullSeparatorOperation
			>
		)
	);
}

template <typename TheConsumer>
inline void Type_::Pull(
	Literal & theLiteral,
	TheConsumer & theConsumer
) {
	theLiteral.BackGive<Separator>(theConsumer);
}

	#undef Type_

#endif
