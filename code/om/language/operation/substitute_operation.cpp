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

#ifndef Om_Language_Operation_SubstituteOperation_

	#include "om/language/operation/substitute_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

			BOOST_AUTO_TEST_SUITE(SubstituteOperationTest)

				BOOST_AUTO_TEST_CASE(DefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{substitute}",
						System::Get().Evaluate("drop find {substitute} system")
					);
				}

				BOOST_AUTO_TEST_CASE(BasicSubstitutionTest) {
					BOOST_CHECK_EQUAL(
						"{A{B}}{B}",
						System::Get().Evaluate("substitute {A {B}} {A}")
					);
				}

				BOOST_AUTO_TEST_CASE(IdentityDefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{A{}}{}",
						System::Get().Evaluate("substitute {A {}} {A}")
					);
				}

				BOOST_AUTO_TEST_CASE(EmptyDefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{A}{A}",
						System::Get().Evaluate("substitute {A} {A}")
					);
				}

				BOOST_AUTO_TEST_CASE(EmptyLexiconTest) {
					BOOST_CHECK_EQUAL(
						"{}{}",
						System::Get().Evaluate("substitute {} {}")
					);
				}

				BOOST_AUTO_TEST_CASE(EmptyKeyFallThroughTest) {
					BOOST_CHECK_EQUAL(
						"{{{A}}}{{A}}",
						System::Get().Evaluate("substitute {{{A}}} {B}")
					);
				}

				// Confirms that the last definition wins.
				BOOST_AUTO_TEST_CASE(MultipleDefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{A{{C}}}{{C}}",
						System::Get().Evaluate("substitute { A {{B}} A {{C}} } {A}")
					);
				}

				// Confirms that the last definition wins.
				BOOST_AUTO_TEST_CASE(MultipleEmptyKeyTest) {
					BOOST_CHECK_EQUAL(
						"{{{C}}}{{C}}",
						System::Get().Evaluate("substitute { {{B}} {{C}} } {A}")
					);
				}

				// Confirms that underlying non-constant definitions are used.
				BOOST_AUTO_TEST_CASE(ChainedLookupTest) {
					BOOST_CHECK_EQUAL(
						(
							"{A{B}}{"
							"unquote{A}\n"
							"B"
							"}"
						),
						System::Get().Evaluate("substitute {A {B}} {unquote {A} A}")
					);

					BOOST_CHECK_EQUAL(
						"{blaven{42}}{do{blaven}}",
						System::Get().Evaluate("substitute{blaven{42}}{do{blaven}}")
					);
				}

			BOOST_AUTO_TEST_SUITE_END()

		}

	}

}

	#endif

#else

// MARK: - Om::Language::Operation::SubstituteOperation

	#define Type_ \
	Om::Language::Operation::SubstituteOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operation_SubstituteOperation_GetName_();
}

// MARK: public (non-static)

template <typename TheProducer>
inline void Type_::Translate(
	Translator const &,
	TheProducer & theProducer,
	Expression & theExpression
) const {
	Evaluator theScope(
		theExpression,
		*this->thisLexicon
	);
	theProducer.GiveElements(theScope);
}

	#undef Type_

#endif
