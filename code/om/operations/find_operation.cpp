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
#if defined( Om_Operations_FindOperation_ )

	#include "om/lexicon.hpp"

// MARK: Om::Operations::FindOperation

	#define Type_ Om::Operations::FindOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_FindOperation_GetName_() );
}

template< typename TheFindOperation >
inline void Type_::GiveElements(
	TheFindOperation & theFindOperation,
	Queue & theQueue
)
{
	theQueue.TakeElement( GetOperator() );
	if( theFindOperation.thisOperator ){
		theQueue.TakeQuotedElements( *theFindOperation.thisOperator );
	}
}

// MARK: public (non-static)

inline Type_::FindOperation()
:
thisOperator()
{
}

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
)
{
	return( this->TakeQuotedQueue( theEvaluation, theOperand.GetProgram() ) );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
)
{
	if( this->thisOperator ){
		Lexicon theLexicon;
		theLexicon.TakeElements( theQueue );
		this->TakeLexicon( theEvaluation, theLexicon );
		return( true );
	}
	this->thisOperator = boost::in_place();
	assert( this->thisOperator );
	this->thisOperator->TakeElements( theQueue );
	return( false );
}

// MARK: private (non-static)

inline void Type_::TakeLexicon(
	Evaluation & theEvaluation,
	Lexicon & theLexicon
)
{
	assert( this->thisOperator );
	Program const * theProgram;
	theLexicon.Find( *this->thisOperator, theProgram );
	theEvaluation.TakeQuotedQueue( theLexicon );
	theEvaluation.TakeQuotedQueue( *this->thisOperator );
	theEvaluation.TakeQuotedQueue( theProgram ? *theProgram : Null::Get() );
}

	#undef Type_

#else
	#include "om/operations/find_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( FindOperation )
		{
			TEST( Simple )
			{
				CHECK_EQUAL(
					(
						"{A}{a}{"
							"b{B}\n"
							"a{A}"
						"}"
					),
					Environment().Evaluate( "find {a}{b{B} a{A}}" )
				);

				CHECK_EQUAL(
					(
						"{A}{a}{"
							"b{B}\n"
							"a{A}"
						"}"
					),
					Environment().Evaluate( "find {a}lexicon{b{B} a{A}}" )
				);

				CHECK_EQUAL(
					"{}{a}{}",
					Environment().Evaluate( "find {a}lexicon{}" )
				);

				CHECK_EQUAL(
					(
						"{}{c}{"
							"b{B}\n"
							"a{A}"
						"}"
					),
					Environment().Evaluate( "find {c}{b{B} a{A}}" )
				);

				CHECK_EQUAL(
					(
						"{}{c}{"
							"b{B}\n"
							"a{A}\n"
							"{C}"
						"}"
					),
					Environment().Evaluate( "find {c}{b{B} a{A} {C}}" )
				);

				CHECK_EQUAL(
					(
						"{C}{}{"
							"b{B}\n"
							"a{A}\n"
							"{C}"
						"}"
					),
					Environment().Evaluate( "find {}{b{B} a{A} {C}}" )
				);
			}
		}
	}
}

	#endif

#endif
