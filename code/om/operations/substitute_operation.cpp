/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operations_SubstituteOperation_

	#include "om/operations/substitute_operation.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

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

	#endif

#else

// MARK: - Om::Operations::SubstituteOperation

	#define Type_ \
	Om::Operations::SubstituteOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operations_SubstituteOperation_GetName_();
}

// MARK: public (non-static)

template <typename TheQueue>
inline void Type_::Translate(
	Translator const &,
	TheQueue & theQueue,
	Expression & theExpression
) const {
	Evaluator theScope(
		theExpression,
		*this->thisLexicon
	);
	theQueue.GiveElements(theScope);
}

	#undef Type_

#endif
