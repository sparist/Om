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

#ifndef Om_Operation_BackPullFormOperation_

	#include "om/operation/back_pull_form_operation.hpp"

	#ifdef Om_Macros_Test_

		#include "om/system.hpp"

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(BackPullFormOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{forms->}",
					System::Get().Evaluate("drop find {forms->} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{4{5}{6}}{1{2}{3}}",
					System::Get().Evaluate("forms-> {1{2}{3}4{5}{6}}")
				);

				BOOST_CHECK_EQUAL(
					"{2}{1}",
					System::Get().Evaluate("forms-> {1 2}")
				);

				BOOST_CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate("forms-> {}")
				);

				BOOST_CHECK_EQUAL(
					"{only}{}",
					System::Get().Evaluate("forms-> {only}")
				);

				BOOST_CHECK_EQUAL(
					"forms->",
					System::Get().Evaluate("forms->")
				);

				BOOST_CHECK_EQUAL(
					"{a{b}{c}}{}",
					System::Get().Evaluate("forms->{a{b}{c}}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/expression.hpp"
	#include "om/operation/pull_operation.hpp"

// MARK: - Om::Operation::BackPullFormOperation

	#define Type_ \
	Om::Operation::BackPullFormOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operation_BackPullFormOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<IncompleteOperation>(
			new PullOperation<
				Expression,
				BackPullFormOperation
			>
		)
	);
}

template <typename TheConsumer>
inline void Type_::Pull(
	Expression & theExpression,
	TheConsumer & theConsumer
) {
	theExpression.BackGiveForm(theConsumer);
}

	#undef Type_

#endif
