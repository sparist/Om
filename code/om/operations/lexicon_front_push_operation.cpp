/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.1
	\date
		2012-2013
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

inline void Type_::Give( Evaluation & theEvaluation )
{
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new FrontPushOperation< Lexicon, LexiconFrontPushOperation >
		)
	);
}

	#undef Type_

#else
	#include "om/operations/lexicon_front_push_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( LexiconFrontPushOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{->lexicon}",
					System::Get().Evaluate( "drop find {->lexicon} system" )
				);
			}

			TEST( General )
			{
				CHECK_EQUAL(
					"{a{B}}",
					System::Get().Evaluate( "->lexicon {a{A}} {a{B}}" )
				);

				CHECK_EQUAL(
					"{a{B}}",
					System::Get().Evaluate( "->lexicon {a} {a{B}}" )
				);

				CHECK_EQUAL(
					"{a}",
					System::Get().Evaluate( "->lexicon {a{A}} {a}" )
				);

				CHECK_EQUAL(
					(
						"{"
							"a\n"
							"b{C}"
						"}"
					),
					System::Get().Evaluate( "->lexicon {a{A}} {a{B} a b{C}}" )
				);
			}
		}
	}
}

	#endif

#endif
