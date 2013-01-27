/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Operations_SubstituteOperation_ )

// MARK: Om::Operations::SubstituteOperation

	#define Type_ \
	Om::Operations::SubstituteOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_SubstituteOperation_GetName_() );
}

// MARK: public (non-static)

template< typename TheQueue >
inline void Type_::Translate(
	Translator const &,
	TheQueue & theQueue,
	Expression & theExpression
) const
{
	Evaluator theScope(
		theExpression,
		*this->thisLexicon
	);
	theQueue.GiveElements( theScope );
}

	#undef Type_

#else

	#include "om/operations/substitute_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( SubstituteOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{substitute}",
					System::Get().Evaluate( "drop find {substitute} system" )
				);
			}

			TEST( BasicSubstitution )
			{
				CHECK_EQUAL(
					"{A{B}}{B}",
					System::Get().Evaluate( "substitute {A {B}} {A}" )
				);
			}

			TEST( IdentityDefinition )
			{
				CHECK_EQUAL(
					"{A{}}{}",
					System::Get().Evaluate( "substitute {A {}} {A}" )
				);
			}

			TEST( EmptyDefinition )
			{
				CHECK_EQUAL(
					"{A}{A}",
					System::Get().Evaluate( "substitute {A} {A}" )
				);
			}

			TEST( EmptyLexicon )
			{
				CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate( "substitute {} {}" )
				);
			}

			TEST( EmptyKeyFallThrough )
			{
				CHECK_EQUAL(
					"{{{A}}}{{A}}",
					System::Get().Evaluate( "substitute {{{A}}} {B}" )
				);
			}

			// Confirms that the last definition wins.
			TEST( MultipleDefinition )
			{
				CHECK_EQUAL(
					"{A{{C}}}{{C}}",
					System::Get().Evaluate( "substitute { A {{B}} A {{C}} } {A}" )
				);
			}

			// Confirms that the last definition wins.
			TEST( MultipleEmptyKey )
			{
				CHECK_EQUAL(
					"{{{C}}}{{C}}",
					System::Get().Evaluate( "substitute { {{B}} {{C}} } {A}" )
				);
			}

			// Confirms that underlying non-constant definitions are used.
			TEST( ChainedLookup )
			{
				CHECK_EQUAL(
					(
						"{A{B}}{"
						"unquote{A}\n"
						"B"
						"}"
					),
					System::Get().Evaluate( "substitute {A {B}} {unquote {A} A}" )
				);

				CHECK_EQUAL(
					"{blaven{42}}{do{blaven}}",
					System::Get().Evaluate( "substitute{blaven{42}}{do{blaven}}" )
				);
			}
		}
	}
}

	#endif

#endif
