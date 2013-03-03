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

#if !defined( Om_Operations_DefineOperation_ )

	#include "om/operations/define_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE( DefineOperationTest )

			BOOST_AUTO_TEST_CASE( DefinitionTest ) {
				BOOST_CHECK_EQUAL(
					"{define}",
					System::Get().Evaluate( "drop find {define} system" )
				);
			}

			BOOST_AUTO_TEST_CASE( BasicSubstitutionTest ) {
				BOOST_CHECK_EQUAL(
					"B",
					System::Get().Evaluate( "define {A {B}} {A}" )
				);
			}

			BOOST_AUTO_TEST_CASE( IdentityDefinitionTest ) {
				BOOST_CHECK_EQUAL(
					"",
					System::Get().Evaluate( "define {A {}} {A}" )
				);
			}

			BOOST_AUTO_TEST_CASE( EmptyDefinitionTest ) {
				BOOST_CHECK_EQUAL(
					"A",
					System::Get().Evaluate( "define {A} {A}" )
				);
			}

			BOOST_AUTO_TEST_CASE( EmptyLexiconTest ) {
				BOOST_CHECK_EQUAL(
					"",
					System::Get().Evaluate( "define {} {}" )
				);
			}

			BOOST_AUTO_TEST_CASE( EmptyKeyFallThroughTest ) {
				BOOST_CHECK_EQUAL(
					"{A}",
					System::Get().Evaluate( "define {{{A}}} {B}" )
				);
			}

			// Confirms that the last definition wins.
			BOOST_AUTO_TEST_CASE( MultipleDefinitionTest ) {
				BOOST_CHECK_EQUAL(
					"{C}",
					System::Get().Evaluate( "define { A {{B}} A {{C}} } {A}" )
				);
			}

			// Confirms that the last definition wins.
			BOOST_AUTO_TEST_CASE( MultipleEmptyKeyTest ) {
				BOOST_CHECK_EQUAL(
					"{C}",
					System::Get().Evaluate( "define { {{B}} {{C}} } {A}" )
				);
			}

			// Confirms that underlying non-constant definitions are used.
			BOOST_AUTO_TEST_CASE( ChainedLookupTest ) {
				BOOST_CHECK_EQUAL(
					(
						"B\n"
						"B"
					),
					System::Get().Evaluate( "define {A {B}} {dequote {A} A}" )
				);

				BOOST_CHECK_EQUAL(
					"{1}",
					System::Get().Evaluate(
						"define{\n"
						"a` b\n"
						"{{1}}\n"
						"}{do{a b}}\n"
					)
				);
				BOOST_CHECK_EQUAL(
					"1",
					System::Get().Evaluate( "define fill {a` b} {1} {do{a b}}" )
				);
				BOOST_CHECK_EQUAL(
					"{1}",
					System::Get().Evaluate( "define {a` b{{1}}} {do{a b}}" )
				);
				BOOST_CHECK_EQUAL(
					"{2}{1}",
					System::Get().Evaluate(
						"define"
						"{"
						"the` flaven{{1}}"
						"the` glaven{{2}}"
						"}"
						"{do{the` glaven} do{the` flaven}}"
					)
				);
			}

			// Confirms evaluation order in nested scopes.
			BOOST_AUTO_TEST_CASE( NestedEvaluationOrderTest ) {
				BOOST_CHECK_EQUAL(
					"{a-default}",
					System::Get().Evaluate(
						"define { b {B} {{b-default}} }{"
						"define { a {A} {{a-default}} } { b }"
						"}"
					)
				);
				BOOST_CHECK_EQUAL(
					"{b-default}",
					System::Get().Evaluate(
						"define { b {B} {{b-default}} }{"
						"define { a {A} } { b }"
						"}"
					)
				);
			}

			BOOST_AUTO_TEST_CASE( SimpleNestedTest ) {
				BOOST_CHECK_EQUAL(
					"c",
					System::Get().Evaluate( "define{a{define{b{c}}{b}}}{a}" )
				);
			}

			BOOST_AUTO_TEST_CASE( DeletedOperatorTest ) {
				BOOST_CHECK_EQUAL(
					"A",
	 				System::Get().Evaluate( "define {define} {define {a{A}} {a}}" )
				);
 			}

			BOOST_AUTO_TEST_CASE( EvaluationTest ) {
				BOOST_CHECK_EQUAL(
					"{1}{3}{2}",
					System::Get().Evaluate( "define {a{{1}c{2}} c{{3}}} {a}" )
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/environment.hpp"

// MARK: - Om::Operations::DefineOperation

	#define Type_ \
	Om::Operations::DefineOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return(
		Om_Operations_DefineOperation_GetName_()
	);
}

template< typename TheDefineOperation >
inline void Type_::GiveElements(
	TheDefineOperation & theDefineOperation,
	Queue & theQueue
) {
	theQueue.TakeElement(
		GetOperator()
	);
	if( theDefineOperation.thisLexicon ) {
		theQueue.TakeQuotedElements( *theDefineOperation.thisLexicon );
	}
}

// MARK: public (non-static)

inline Type_::DefineOperation():
thisLexicon() {}

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
) {
	assert(
		!theOperand.IsEmpty()
	);
	return(
		this->TakeQuotedQueue(
			theEvaluation,
			*theOperand.GetProgram()
		)
	);
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
) {
	if( this->thisLexicon ) {
		Expression theExpression;
		{
			Environment theEnvironment;
			theEnvironment.Push(
				System::Get()
			);
			theEnvironment.Push(
				theEvaluation.GetTranslator()
			);
			theEnvironment.Push( *this->thisLexicon );
			Evaluator theScope(
				theExpression,
				theEnvironment
			);
			theQueue.GiveElements( theScope );
		}
		theEvaluation.TakeQueue( theExpression );
		return( true );
	}
	this->thisLexicon = boost::in_place();
	assert( this->thisLexicon );
	this->thisLexicon->TakeElements( theQueue );
	return( false );
}

	#undef Type_

#endif
