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

#ifndef Om_Language_Operation_LexiconFrontPushOperation_

	#include "om/language/operation/lexicon_front_push_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

			BOOST_AUTO_TEST_SUITE(LexiconFrontPushOperationTest)

				BOOST_AUTO_TEST_CASE(DefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{->[lexicon]}",
						System::Get().Evaluate("drop find {->[lexicon]} system")
					);
				}

				BOOST_AUTO_TEST_CASE(GeneralTest) {
					BOOST_CHECK_EQUAL(
						"{a{B}}",
						System::Get().Evaluate("->[lexicon] {a{A}} {a{B}}")
					);

					BOOST_CHECK_EQUAL(
						"{a{B}}",
						System::Get().Evaluate("->[lexicon] {a} {a{B}}")
					);

					BOOST_CHECK_EQUAL(
						"{a}",
						System::Get().Evaluate("->[lexicon] {a{A}} {a}")
					);

					BOOST_CHECK_EQUAL(
						(
							"{"
							"a\n"
							"b{C}"
							"}"
						),
						System::Get().Evaluate("->[lexicon] {a{A}} {a{B} a b{C}}")
					);
				}

			BOOST_AUTO_TEST_SUITE_END()

		}

	}

}

	#endif

#else

	#include "om/language/lexicon.hpp"
	#include "om/language/operation/front_push_operation.hpp"

// MARK: - Om::Language::Operation::LexiconFrontPushOperation

	#define Type_ \
	Om::Language::Operation::LexiconFrontPushOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operation_LexiconFrontPushOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<IncompleteOperation>(
			new FrontPushOperation<
				Lexicon,
				LexiconFrontPushOperation
			>
		)
	);
}

	#undef Type_

#endif
