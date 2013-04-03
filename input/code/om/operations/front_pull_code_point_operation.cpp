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

#ifndef Om_Operations_FrontPullCodePointOperation_

	#include "om/operations/front_pull_code_point_operation.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE(FrontPullCodePointOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{<-code` points}",
					System::Get().Evaluate("drop find {<-code` points} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{1}{`{2`}three}",
					System::Get().Evaluate("<-code` points {1{2}three}")
				);

				BOOST_CHECK_EQUAL(
					"{` }{}",
					System::Get().Evaluate("<-code` points {` }")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"\xC3\x98"
						"}{"
						"\xCC\x81"
						"a}"
					),
					System::Get().Evaluate(
						"<-code` points {"
						"\xC7\xBE"
						"a}"
					)
				);

				BOOST_CHECK_EQUAL(
					"{` }{}",
					System::Get().Evaluate("<-code` points { }")
				);

				BOOST_CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate("<-code` points {}")
				);

				BOOST_CHECK_EQUAL(
					"<-code` points",
					System::Get().Evaluate("<-code` points")
				);
			}
			
			BOOST_AUTO_TEST_CASE(MultiCodePointCharacterTest) {
				BOOST_CHECK_EQUAL(
					(
						"{"
						"\xE1\x84\x80"
						"}{"
						"\xE1\x85\xA1"
						"\xE1\x84\x82"
						"}"
					),
					System::Get().Evaluate(
						"<-code` points"
						"{"
						"\xE1\x84\x80"
						"\xE1\x85\xA1"
						"\xE1\x84\x82"
						"}"
					)
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/operations/pull_operation.hpp"

// MARK: - Om::Operations::FrontPullCodePointOperation

	#define Type_ \
	Om::Operations::FrontPullCodePointOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operations_FrontPullCodePointOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<Operation>(
			new PullOperation<
				Operator,
				FrontPullCodePointOperation
			>
		)
	);
}

template <typename TheConsumer>
inline void Type_::Pull(
	Operator & theOperator,
	TheConsumer & theConsumer
) {
	theOperator.FrontGiveCodePoint(theConsumer);
}

	#undef Type_

#endif
