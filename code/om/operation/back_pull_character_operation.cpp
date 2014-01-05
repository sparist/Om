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

#ifndef Om_Operation_BackPullCharacterOperation_

	#include "om/operation/back_pull_character_operation.hpp"

	#ifdef Om_Macro_Test_

		#include "om/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(BackPullCharacterOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{[characters]->}",
					System::Get().Evaluate("drop find {[characters]->} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{e}{1`{2`}thre}",
					System::Get().Evaluate("[characters]-> {1{2}three}")
				);

				BOOST_CHECK_EQUAL(
					"{` }{}",
					System::Get().Evaluate("[characters]-> {` }")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"\xC3\x98"
						"\xCC\x81"
						"}{a}"
					),
					System::Get().Evaluate(
						"[characters]-> {a"
						"\xC7\xBE"
						"}"
					)
				);

				BOOST_CHECK_EQUAL(
					"{` }{}",
					System::Get().Evaluate("[characters]-> { }")
				);

				BOOST_CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate("[characters]-> {}")
				);

				BOOST_CHECK_EQUAL(
					"[characters]->",
					System::Get().Evaluate("[characters]->")
				);
			}

			BOOST_AUTO_TEST_CASE(MultiCodePointCharacterTest) {
				BOOST_CHECK_EQUAL(
					(
						"{"
						"\xE1\x84\x80"
						"\xE1\x85\xA1"
						"}{"
						"\xE1\x86\xAB"
						"}"
					),
					System::Get().Evaluate(
						"[characters]->"
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

// MARK: - Om::Operation::BackPullCharacterOperation

	#define Type_ \
	Om::Operation::BackPullCharacterOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_BackPullCharacterOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<IncompleteOperation>(
			new PullOperation<
				Operator,
				BackPullCharacterOperation
			>
		)
	);
}

template <typename TheConsumer>
inline void Type_::Pull(
	Operator & theOperator,
	TheConsumer & theConsumer
) {
	theOperator.BackGiveSegment<boost::locale::boundary::character>(theConsumer);
}

	#undef Type_

#endif
