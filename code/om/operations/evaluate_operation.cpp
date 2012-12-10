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
#if defined( Om_Operations_EvaluateOperation_ )

	#include "om/environment.hpp"

// MARK: Om::Operations::EvaluateOperation

	#define Type_ Om::Operations::EvaluateOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_EvaluateOperation_GetName_() );
}

template< typename TheEvaluateOperation >
inline void Type_::GiveElements(
	TheEvaluateOperation & theEvaluateOperation,
	Queue & theQueue
)
{
	theQueue.TakeElement( GetOperator() );
	if( theEvaluateOperation.thisLexicon ){
		theQueue.TakeQuotedElements( *theEvaluateOperation.thisLexicon );
	}
}

// MARK: public (non-static)

inline Type_::EvaluateOperation()
:
thisLexicon()
{
}

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Expansion & theExpansion,
	TheOperand & theOperand
)
{
	return( this->TakeQuotedQueue( theExpansion, theOperand.GetProgram() ) );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Expansion & theExpansion,
	TheQueue & theQueue
)
{
	if( this->thisLexicon ){
		Expression theExpression;
		{
			Environment theEnvironment( theExpansion.GetTranslator() );
			theEnvironment.Push( *this->thisLexicon );
			Evaluator theScope( theExpression, theEnvironment );
			theQueue.GiveElements( theScope );
		}
		theExpansion.TakeQueue( theExpression );
		return( true );
	}
	this->thisLexicon = boost::in_place();
	assert( this->thisLexicon );
	this->thisLexicon->TakeElements( theQueue );
	return( false );
}

	#undef Type_

#else
	#include "om/operations/evaluate_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( EvaluateOperation )
		{
			TEST( BasicSubstitution )
			{
				CHECK_EQUAL(
					"B",
					Environment().Evaluate( "evaluate {A {B}} {A}" )
				);
			}

			TEST( IdentityDefinition )
			{
				CHECK_EQUAL(
					"",
					Environment().Evaluate( "evaluate {A {}} {A}" )
				);
			}

			TEST( EmptyDefinition )
			{
				CHECK_EQUAL(
					"A",
					Environment().Evaluate( "evaluate {A} {A}" )
				);
			}

			TEST( EmptyLexicon )
			{
				CHECK_EQUAL( "", Environment().Evaluate( "evaluate {} {}" ) );
			}

			TEST( EmptyKeyFallThrough )
			{
				CHECK_EQUAL(
					"{A}",
					Environment().Evaluate( "evaluate {{{A}}} {B}" )
				);
			}

			// Confirms that the last definition wins.
			TEST( MultipleDefinition )
			{
				CHECK_EQUAL(
					"{C}",
					Environment().Evaluate( "evaluate { A {{B}} A {{C}} } {A}" )
				);
			}

			// Confirms that the last definition wins.
			TEST( MultipleEmptyKey )
			{
				CHECK_EQUAL(
					"{C}",
					Environment().Evaluate( "evaluate { {{B}} {{C}} } {A}" )
				);
			}

			// Confirms that underlying non-constant definitions are used.
			TEST( ChainedLookup )
			{
				CHECK_EQUAL(
					(
						"B\n"
						"B"
					),
					Environment().Evaluate( "evaluate {A {B}} {dequote {A} A}" )
				);

				CHECK_EQUAL(
					"{1}",
					Environment().Evaluate(
						"evaluate{\n"
							"a` b\n"
							"{{1}}\n"
						"}{do{a b}}\n"
					)
				);
				CHECK_EQUAL(
					"1",
					Environment().Evaluate(
						"evaluate fill {a` b} {1} {do{a b}}"
					)
				);
				CHECK_EQUAL(
					"{1}",
					Environment().Evaluate( "evaluate {a` b{{1}}} {do{a b}}" )
				);
				CHECK_EQUAL(
					"{2}{1}",
					Environment().Evaluate(
						"evaluate"
						"{"
							"the` flaven{{1}}"
							"the` glaven{{2}}"
						"}"
						"{do{the` glaven} do{the` flaven}}"
					)
				);
			}

			// Confirms evaluation order in nested scopes.
			TEST( NestedEvaluationOrder )
			{
				CHECK_EQUAL(
					"{a-default}",
					Environment().Evaluate(
						"evaluate { b {B} {{b-default}} }{"
							"evaluate { a {A} {{a-default}} } { b }"
						"}"
					)
				);
				CHECK_EQUAL(
					"{b-default}",
					Environment().Evaluate(
						"evaluate { b {B} {{b-default}} }{"
							"evaluate { a {A} } { b }"
						"}"
					)
				);
			}

			TEST( SimpleNested )
			{
				CHECK_EQUAL(
					"c",
					Environment().Evaluate(
						"evaluate{a{evaluate{b{c}}{b}}}{a}"
					)
				);
			}

			TEST( DeletedOperator )
			{
				CHECK_EQUAL(
					"A",
	 				Environment().Evaluate(
						"evaluate {evaluate} {evaluate {a{A}} {a}}"
					)
				);
 			}

			TEST( Evaluation )
			{
				CHECK_EQUAL(
					"{1}{3}{2}",
					Environment().Evaluate( "evaluate {a{{1}c{2}} c{{3}}} {a}" )
				);
			}
		}
	}
}

	#endif

#endif
