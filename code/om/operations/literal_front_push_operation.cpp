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
#if defined( Om_Operations_LiteralFrontPushOperation_ )

	#include "om/literal.hpp"
	#include "om/operations/front_push_operation.hpp"

// MARK: Om::Operations::LiteralFrontPushOperation

	#define Type_ Om::Operations::LiteralFrontPushOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_LiteralFrontPushOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation )
{
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new FrontPushOperation< Literal, LiteralFrontPushOperation >
		)
	);
}

	#undef Type_

#else
	#include "om/operations/literal_front_push_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( LiteralFrontPushOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					"{1{2}34{5}6}",
					Environment().Evaluate( "->literal {1{2}3}{4{5}6}" )
				);

				CHECK_EQUAL(
					"{1{2}{5}6}",
					Environment().Evaluate( "->literal {1{2}}{{5}6}" )
				);

				CHECK_EQUAL(
					"{{5}6}",
					Environment().Evaluate( "->literal {}{{5}6}" )
				);

				CHECK_EQUAL(
					"{{5}6}",
					Environment().Evaluate( "->literal {{5}6}{}" )
				);

				CHECK_EQUAL(
					"{{2}3}",
					Environment().Evaluate( "->literal quote{2}{3}" )
				);

				CHECK_EQUAL(
					"{2{3}}",
					Environment().Evaluate( "->literal{2}quote{3}" )
				);
			}
		}
	}
}

	#endif

#endif
