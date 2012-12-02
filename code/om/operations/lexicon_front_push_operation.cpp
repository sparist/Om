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
#if defined( Om_Operations_LexiconFrontPushOperation_ )

	#include "om/lexicon.hpp"
	#include "om/operations/front_push_operation.hpp"

// MARK: Om::Operations::LexiconFrontPushOperation

	#define Type_ Om::Operations::LexiconFrontPushOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_LexiconFrontPushOperation_GetName_() );
}

template< typename TheEvaluandTaker>
inline void Type_::Give( TheEvaluandTaker & theEvaluandTaker )
{
	theEvaluandTaker.TakeEvaluand(
		std::auto_ptr< Evaluand >(
			new FrontPushOperation< Lexicon, LexiconFrontPushOperation >
		)
	);
}

	#undef Type_

#else
	#include "om/operations/lexicon_front_push_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( LexiconFrontPushOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					"{a{B}}",
					Environment().Evaluate( "->lexicon {a{A}} {a{B}}" )
				);

				CHECK_EQUAL(
					"{a{B}}",
					Environment().Evaluate( "->lexicon {a} {a{B}}" )
				);

				CHECK_EQUAL(
					"{a}",
					Environment().Evaluate( "->lexicon {a{A}} {a}" )
				);

				CHECK_EQUAL(
					(
						"{"
							"a\n"
							"b{C}"
						"}"
					),
					Environment().Evaluate( "->lexicon {a{A}} {a{B} a b{C}}" )
				);
			}
		}
	}
}

	#endif

#endif
