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
#if defined( Om_Operations_FrontPullTermOperation_ )

	#include "om/expression.hpp"
	#include "om/operations/pull_operation.hpp"

// MARK: Om::Operations::FrontPullTermOperation

	#define Type_ Om::Operations::FrontPullTermOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_FrontPullTermOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation )
{
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation< Expression, FrontPullTermOperation >
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull( Expression & theExpression, TheQueue & theQueue )
{
	theExpression.FrontGiveTerm( theQueue );
}

	#undef Type_

#else
	#include "om/operations/front_pull_term_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( FrontPullTermOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					(
						"{1}{"
							"{2}\n"
							"3"
						"}"
					),
					System::Get().Evaluate( "<-term {1{2}3}" )
				);

				CHECK_EQUAL(
					"{1}{2}",
					System::Get().Evaluate( "<-term {1 2}" )
				);

				CHECK_EQUAL( "{}{}", System::Get().Evaluate( "<-term {}" ) );

				CHECK_EQUAL(
					"{only}{}",
					System::Get().Evaluate( "<-term {only}" )
				);

				CHECK_EQUAL( "<-term", System::Get().Evaluate( "<-term" ) );
			}
		}
	}
}

	#endif

#endif
