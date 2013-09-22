/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operation_BackPullCodePointOperation_

	#include "om/operation/back_pull_code_point_operation.hpp"

	#ifdef Om_Macros_Test_

		#include "om/system.hpp"

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(BackPullCodePointOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{code` points->}",
					System::Get().Evaluate("drop find {code` points->} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{e}{1`{2`}thre}",
					System::Get().Evaluate("code` points-> {1{2}three}")
				);

				BOOST_CHECK_EQUAL(
					"{` }{}",
					System::Get().Evaluate("code` points-> {` }")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"\xCC\x81"
						"}{a"
						"\xC3\x98"
						"}"
					),
					System::Get().Evaluate(
						"code` points-> {a"
						"\xC7\xBE"
						"}"
					)
				);

				BOOST_CHECK_EQUAL(
					"{` }{}",
					System::Get().Evaluate("code` points-> { }")
				);

				BOOST_CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate("code` points-> {}")
				);

				BOOST_CHECK_EQUAL(
					"code` points->",
					System::Get().Evaluate("code` points->")
				);
			}

			BOOST_AUTO_TEST_CASE(MultiCodePointCharacterTest) {
				BOOST_CHECK_EQUAL(
					(
						"{"
						"\xE1\x85\xA1"
						"}{"
						"\xE1\x86\xAB"
						"\xE1\x84\x80"
						"}"
					),
					System::Get().Evaluate(
						"code` points->"
						"{"
						"\xE1\x86\xAB"
						"\xE1\x84\x80"
						"\xE1\x85\xA1"
						"}"
					)
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/operation/pull_operation.hpp"

// MARK: - Om::Operation::BackPullCodePointOperation

	#define Type_ \
	Om::Operation::BackPullCodePointOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_BackPullCodePointOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<IncompleteOperation>(
			new PullOperation<
				Operator,
				BackPullCodePointOperation
			>
		)
	);
}

template <typename TheConsumer>
inline void Type_::Pull(
	Operator & theOperator,
	TheConsumer & theConsumer
) {
	theOperator.BackGiveCodePoint(theConsumer);
}

	#undef Type_

#endif
