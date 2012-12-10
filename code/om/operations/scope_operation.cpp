/*!
\file
	\brief
		Om cpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if defined( Om_Operations_ScopeOperation_ )

	#include "om/environment.hpp"

// MARK: Om::Operations::ScopeOperation

	#define Type_ Om::Operations::ScopeOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_ScopeOperation_GetName_() );
}

// MARK: public (non-static)

template< typename TheQueue >
inline void Type_::Translate(
	Translator const & theTranslator,
	TheQueue & theQueue,
	Expression & theExpression
) const
{
	Environment theEnvironment( theTranslator );
	theEnvironment.Push( *this->thisLexicon );
	Evaluator theScope( theExpression, theEnvironment );
	theQueue.GiveElements( theScope );
}

	#undef Type_

#else
	#include "om/operations/scope_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( ScopeOperation )
		{
			TEST( BasicSubstitution )
			{
				CHECK_EQUAL(
					"{A{B}}{B}",
					Environment().Evaluate( "scope {A {B}} {A}" )
				);
			}

			TEST( IdentityDefinition )
			{
				CHECK_EQUAL(
					"{A{}}{}",
					Environment().Evaluate( "scope {A {}} {A}" )
				);
			}

			TEST( EmptyDefinition )
			{
				CHECK_EQUAL(
					"{A}{A}",
					Environment().Evaluate( "scope {A} {A}" )
				);
			}

			TEST( EmptyLexicon )
			{
				CHECK_EQUAL( "{}{}", Environment().Evaluate( "scope {} {}" ) );
			}

			TEST( EmptyKeyFallThrough )
			{
				CHECK_EQUAL(
					"{{{A}}}{{A}}",
					Environment().Evaluate( "scope {{{A}}} {B}" )
				);
			}

			// Confirms that the last definition wins.
			TEST( MultipleDefinition )
			{
				CHECK_EQUAL(
					"{A{{C}}}{{C}}",
					Environment().Evaluate( "scope { A {{B}} A {{C}} } {A}" )
				);
			}

			// Confirms that the last definition wins.
			TEST( MultipleEmptyKey )
			{
				CHECK_EQUAL(
					"{{{C}}}{{C}}",
					Environment().Evaluate( "scope { {{B}} {{C}} } {A}" )
				);
			}

			// Confirms that underlying non-constant definitions are used.
			TEST( ChainedLookup )
			{
				CHECK_EQUAL(
					(
						"{A{B}}{"
							"B\n"
							"B"
						"}"
					),
					Environment().Evaluate( "scope {A {B}} {dequote {A} A}" )
				);

				CHECK_EQUAL(
					"{a` b{{1}}}{{1}}",
					Environment().Evaluate(
						"scope{\n"
							"a` b\n"
							"{"
								"{1}"
							"}\n"
						"}{do{a b}}\n"
					)
				);
				CHECK_EQUAL(
					"{a` b{1}}{1}",
					Environment().Evaluate( "scope fill {a` b} {1} {do{a b}}" )
				);
				CHECK_EQUAL(
					"{a` b{{1}}}{{1}}",
					Environment().Evaluate( "scope {a` b{{1}}} {do{a b}}" )
				);
				CHECK_EQUAL(
					"{{2}{1}}",
					Environment().Evaluate(
						"drop scope"
						"{"
							"the` blaven{{1}}"
							"the` glaven{{2}}"
						"}"
						"{do{the glaven} do{the blaven}}"
					)
				);
			}

			// Confirms evaluation order in nested scopes.
			TEST( NestedEvaluationOrder )
			{
				CHECK_EQUAL(
					"{{a-default}}",
					Environment().Evaluate(
						"dequote drop scope {"
							"b {B} {{b-default}}"
						"}{"
							"drop scope {"
								"a {A} {{a-default}}"
							"} { b }"
						"}"
					)
				);
				CHECK_EQUAL(
					"{{b-default}}",
					Environment().Evaluate(
						"dequote drop scope {"
							"b {B} {{b-default}}"
						"}{ drop scope { a {A} } { b } }"
					)
				);
			}

			TEST( OperatorWithNoOperand )
			{
				CHECK_EQUAL(
					"{scope{something}}{something{a{A}}{a}}",
	 				Environment().Evaluate(
						"scope {scope{something}} {scope {a{A}} {a}}"
					)
				);

				CHECK_EQUAL(
					"{scope}{{a{A}}{A}}",
	 				Environment().Evaluate(
						"scope {scope{something}scope} {scope {a{A}} {a}}"
					)
				);
 			}
		}
	}
}

	#endif

#endif
