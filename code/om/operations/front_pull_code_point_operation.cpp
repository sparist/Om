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
#if defined( Om_Operations_FrontPullCodePointOperation_ )

	#include "om/operations/pull_operation.hpp"

// MARK: Om::Operations::FrontPullCodePointOperation

	#define Type_ Om::Operations::FrontPullCodePointOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_FrontPullCodePointOperation_GetName_() );
}

template< typename TheEvaluator>
inline void Type_::Give( TheEvaluator & theEvaluator )
{
	theEvaluator.TakeEvaluand(
		std::auto_ptr< Evaluand >(
			new PullOperation< Operator, FrontPullCodePointOperation >
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull( Operator & theOperator, TheQueue & theQueue )
{
	theOperator.FrontGiveCodePoint( theQueue );
}

	#undef Type_

#else
	#include "om/operations/front_pull_code_point_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( FrontPullCodePointOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					"{1}{`{2`}three}",
					Environment().Evaluate( "<-codepoints {1{2}three}" )
				);

				CHECK_EQUAL(
					"{` }{}",
					Environment().Evaluate( "<-codepoints {` }" )
				);

				CHECK_EQUAL(
					"{" "\xC3\x98" "}{" "\xCC\x81" "a}",
					Environment().Evaluate( "<-codepoints {" "\xC7\xBE" "a}" )
				);

				CHECK_EQUAL(
					"{` }{}",
					Environment().Evaluate( "<-codepoints { }" )
				);

				CHECK_EQUAL(
					"{}{}",
					Environment().Evaluate( "<-codepoints {}" )
				);

				CHECK_EQUAL(
					"<-codepoints",
					Environment().Evaluate( "<-codepoints" )
				);
			}
			
			TEST( MultiCodePointCharacter )
			{
				CHECK_EQUAL(
					(
						"{" "\xE1\x84\x80" "}{"
							"\xE1\x85\xA1" "\xE1\x84\x82"
						"}"
					),
					Environment().Evaluate(
						"<-codepoints"
						"{" "\xE1\x84\x80" "\xE1\x85\xA1" "\xE1\x84\x82" "}"
					)
				);
			}
		}
	}
}

	#endif

#endif
