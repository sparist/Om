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
#if defined( Om_Operations_BackPullCharacterOperation_ )

	#include "om/operations/pull_operation.hpp"

// MARK: Om::Operations::BackPullCharacterOperation

	#define Type_ Om::Operations::BackPullCharacterOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_BackPullCharacterOperation_GetName_() );
}

template< typename TheEvaluationTaker >
inline void Type_::Give( TheEvaluationTaker & theEvaluationTaker )
{
	theEvaluationTaker.TakeEvaluation(
		std::auto_ptr< Evaluation >(
			new PullOperation< Operator, BackPullCharacterOperation >
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull( Operator & theOperator, TheQueue & theQueue )
{
	theOperator.BackGiveSegment< boost::locale::boundary::character >(
		theQueue
	);
}

	#undef Type_

#else
	#include "om/operations/back_pull_character_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( BackPullCharacterOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					"{e}{1`{2`}thre}",
					Environment().Evaluate( "characters-> {1{2}three}" )
				);

				CHECK_EQUAL(
					"{` }{}",
					Environment().Evaluate( "characters-> {` }" )
				);

				CHECK_EQUAL(
					"{" "\xC3\x98" "\xCC\x81" "}{a}",
					Environment().Evaluate( "characters-> {a" "\xC7\xBE" "}" )
				);

				CHECK_EQUAL(
					"{` }{}",
					Environment().Evaluate( "characters-> { }" )
				);

				CHECK_EQUAL(
					"{}{}",
					Environment().Evaluate( "characters-> {}" )
				);

				CHECK_EQUAL(
					"characters->",
					Environment().Evaluate( "characters->" )
				);
			}

			TEST( MultiCodePointCharacter )
			{
				CHECK_EQUAL(
					(
						"{"
							"\xE1\x84\x80" "\xE1\x85\xA1"
						"}{" "\xE1\x86\xAB" "}"
					),
					Environment().Evaluate(
						"characters->"
						"{" "\xE1\x86\xAB" "\xE1\x84\x80" "\xE1\x85\xA1" "}"
					)
				);
			}
		}
	}
}

	#endif

#endif
