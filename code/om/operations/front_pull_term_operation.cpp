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

template< typename TheEvaluationTaker>
inline void Type_::Give( TheEvaluationTaker & theEvaluationTaker )
{
	theEvaluationTaker.TakeEvaluation(
		std::auto_ptr< Evaluation >(
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

		#include "om/environment.hpp"
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
					Environment().Evaluate( "<-terms {1{2}3}" )
				);

				CHECK_EQUAL(
					"{1}{2}",
					Environment().Evaluate( "<-terms {1 2}" )
				);

				CHECK_EQUAL( "{}{}", Environment().Evaluate( "<-terms {}" ) );

				CHECK_EQUAL(
					"{only}{}",
					Environment().Evaluate( "<-terms {only}" )
				);

				CHECK_EQUAL( "<-terms", Environment().Evaluate( "<-terms" ) );
			}
		}
	}
}

	#endif

#endif
