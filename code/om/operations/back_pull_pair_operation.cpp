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
#if defined( Om_Operations_BackPullPairOperation_ )

	#include "om/lexicon.hpp"
	#include "om/operations/pull_operation.hpp"

// MARK: Om::Operations::BackPullPairOperation

	#define Type_ Om::Operations::BackPullPairOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_BackPullPairOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation )
{
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation< Lexicon, BackPullPairOperation >
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull( Lexicon & theLexicon, TheQueue & theQueue )
{
	theLexicon.BackGivePair( theQueue );
}

	#undef Type_

#else
	#include "om/operations/back_pull_pair_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( BackPullPairOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					"{4{5}}{1{2}}",
					System::Get().Evaluate( "pair-> {1{2}4{5}}" )
				);

				CHECK_EQUAL(
					"{2}{1}",
					System::Get().Evaluate( "pair-> {1 2}" )
				);

				CHECK_EQUAL(
					"{{2}}{}",
					System::Get().Evaluate( "pair-> {{1}{2}}" )
				);

				CHECK_EQUAL( "{}{}", System::Get().Evaluate( "pair-> {}" ) );

				CHECK_EQUAL(
					"{only}{}",
					System::Get().Evaluate( "pair-> {only}" )
				);

				CHECK_EQUAL(
					"{{c}}{a{b}}",
					System::Get().Evaluate( "pair->{a{b}{c}}" )
				);

				CHECK_EQUAL(
					"{a{b}}{{c}}",
					System::Get().Evaluate( "pair->{{c}a{b}}" )
				);
			}

			TEST( Flush )
			{
				CHECK_EQUAL( "pair->", System::Get().Evaluate( "pair->" ) );
			}
		}
	}
}

	#endif

#endif
