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

#ifndef Om_Language_Operation_DropOperation_

	#include "om/language/operation/drop_operation.hpp"

	#ifdef Om_Macro_Test_

		#include "om/language/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

			BOOST_AUTO_TEST_SUITE(DropOperationTest)

				BOOST_AUTO_TEST_CASE(DefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{drop}",
						System::Get().Evaluate("drop find {drop} system")
					);
				}

				BOOST_AUTO_TEST_CASE(SimpleTest) {
					BOOST_CHECK_EQUAL(
						"{4{5}6}",
						System::Get().Evaluate("drop {1{2}3}{4{5}6}")
					);
				}

			BOOST_AUTO_TEST_SUITE_END()

		}

	}

}

	#endif

#else

// MARK: - Om::Language::Operation::DropOperation

	#define Type_ \
	Om::Language::Operation::DropOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operation_DropOperation_GetName_();
}

template <typename TheDropOperation>
inline void Type_::GiveElements(
	TheDropOperation &,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
}

// MARK: public (non-static)

inline bool Type_::ParseQuotedElements(
	Evaluation &,
	Reader & theReader
) {
	while (theReader) {
		theReader.Pop();
	}
	return true;
}

template <typename TheOperand>
inline bool Type_::TakeOperand(
	Evaluation &,
	TheOperand &
) {
	return true;
}

template <typename TheProducer>
inline bool Type_::TakeQuotedProducer(
	Evaluation &,
	TheProducer &
) {
	return true;
}

	#undef Type_

#endif
