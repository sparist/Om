/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.1
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
#if defined( Om_Operations_FrontPullElementOperation_ )

	#include "om/literal.hpp"
	#include "om/operations/pull_operation.hpp"

// MARK: Om::Operations::FrontPullElementOperation

	#define Type_ Om::Operations::FrontPullElementOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_FrontPullElementOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation )
{
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation< Literal, FrontPullElementOperation >
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull( Literal & theLiteral, TheQueue & theQueue )
{
	theLiteral.FrontGiveElement( theQueue );
}

	#undef Type_

#else
	#include "om/operations/front_pull_element_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( FrontPullElementOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{<-elements}",
					System::Get().Evaluate( "drop find {<-elements} system" )
				);
			}

			TEST( General )
			{
				CHECK_EQUAL(
					"{1}{{2}3}",
					System::Get().Evaluate( "<-elements {1{2}3}" )
				);

				CHECK_EQUAL(
					"{1}{ 2}",
					System::Get().Evaluate( "<-elements {1 2}" )
				);

				CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate( "<-elements {}" )
				);

				CHECK_EQUAL(
					"{only}{}",
					System::Get().Evaluate( "<-elements {only}" )
				);

				CHECK_EQUAL(
					"<-elements",
					System::Get().Evaluate( "<-elements" )
				);
			}
		}
	}
}

	#endif

#endif
