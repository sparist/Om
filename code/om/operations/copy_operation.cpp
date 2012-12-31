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
#if defined( Om_Operations_CopyOperation_ )

	#include "om/literal.hpp"

// MARK: Om::Operations::CopyOperation

	#define Type_ Om::Operations::CopyOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_CopyOperation_GetName_() );
}

template< typename TheCopyOperation >
inline void Type_::GiveElements( TheCopyOperation &, Queue & theQueue )
{
	theQueue.TakeElement( GetOperator() );
}

// MARK: public (non-static)

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
)
{
	{
		Operand const & theConstOperand( theOperand );
		theEvaluation.TakeOperand( theConstOperand );
	}
	theEvaluation.TakeOperand( theOperand );
	return( true );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
)
{
	{
		TheQueue const & theConstQueue( theQueue );
		theEvaluation.TakeQuotedQueue( theConstQueue );
	}
	theEvaluation.TakeQuotedQueue( theQueue );
	return( true );
}

	#undef Type_

#else
	#include "om/operations/copy_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( CopyOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{copy}",
					System::Get().Evaluate( "drop find {copy} system" )
				);
			}

			TEST( Simple )
			{
				CHECK_EQUAL(
					"{1{2}3}{1{2}3}",
					System::Get().Evaluate( "copy {1{2}3}" )
				);
			}
		}
	}
}

	#endif

#endif
