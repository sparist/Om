/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Operations_BackPullOperandOperation_ )

	#include "om/literal.hpp"
	#include "om/operations/pull_operation.hpp"

// MARK: Om::Operations::BackPullOperandOperation

	#define Type_ \
	Om::Operations::BackPullOperandOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_BackPullOperandOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation )
{
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation<
				Literal,
				BackPullOperandOperation
			>
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull(
	Literal & theLiteral,
	TheQueue & theQueue
)
{
	theLiteral.BackGive< Operand >( theQueue );
}

	#undef Type_

#else

	#include "om/operations/back_pull_operand_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( BackPullOperandOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{elements->operand}",
					System::Get().Evaluate( "drop find {elements->operand} system" )
				);
			}

			TEST( General )
			{
				CHECK_EQUAL(
					"{}{1{2}3}",
					System::Get().Evaluate( "elements->operand {1{2}3}" )
				);

				CHECK_EQUAL(
					"{{2}}{1}",
					System::Get().Evaluate( "elements->operand {1{2}}" )
				);

				CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate( "elements->operand {}" )
				);

				CHECK_EQUAL(
					"{{only}}{}",
					System::Get().Evaluate( "elements->operand {{only}}" )
				);

				CHECK_EQUAL(
					"elements->operand",
					System::Get().Evaluate( "elements->operand" )
				);
			}
		}
	}
}

	#endif

#endif
