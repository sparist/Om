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

#ifndef Om_Language_Operation_FrontPullOperandOperation_

	#include "om/language/operation/front_pull_operand_operation.hpp"

	#ifdef Om_Macro_Test_

		#include "om/language/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

			BOOST_AUTO_TEST_SUITE(FrontPullOperandOperationTest)

				BOOST_AUTO_TEST_CASE(DefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{<-[operand...]}",
						System::Get().Evaluate("drop find {<-[operand...]} system")
					);
				}

				BOOST_AUTO_TEST_CASE(GeneralTest) {
					BOOST_CHECK_EQUAL(
						"{}{1{2}3}",
						System::Get().Evaluate("<-[operand...] {1{2}3}")
					);

					BOOST_CHECK_EQUAL(
						"{{1}}{2}",
						System::Get().Evaluate("<-[operand...] {{1}2}")
					);

					BOOST_CHECK_EQUAL(
						"{}{}",
						System::Get().Evaluate("<-[operand...] {}")
					);

					BOOST_CHECK_EQUAL(
						"{{only}}{}",
						System::Get().Evaluate("<-[operand...] {{only}}")
					);

					BOOST_CHECK_EQUAL(
						"<-[operand...]",
						System::Get().Evaluate("<-[operand...]")
					);
				}

			BOOST_AUTO_TEST_SUITE_END()

		}

	}

}

	#endif

#else

	#include "om/language/literal.hpp"
	#include "om/language/operation/pull_operation.hpp"

// MARK: - Om::Language::Operation::FrontPullOperandOperation

	#define Type_ \
	Om::Language::Operation::FrontPullOperandOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operation_FrontPullOperandOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<IncompleteOperation>(
			new PullOperation<
				Literal,
				FrontPullOperandOperation
			>
		)
	);
}

template <typename TheConsumer>
inline void Type_::Pull(
	Literal & theLiteral,
	TheConsumer & theConsumer
) {
	theLiteral.FrontGive<Operand>(theConsumer);
}

	#undef Type_

#endif
