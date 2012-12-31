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
#if defined( Om_Operations_DropOperation_ )

// MARK: Om::Operations::DropOperation

	#define Type_ Om::Operations::DropOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_DropOperation_GetName_() );
}

template< typename TheDropOperation >
inline void Type_::GiveElements( TheDropOperation &, Queue & theQueue )
{
	theQueue.TakeElement( GetOperator() );
}

// MARK: public (non-static)

inline bool Type_::ReadQuotedElements( Evaluation &, Parser & theParser )
{
	while( theParser ){ theParser.Pop(); }
	return( true );
}

template< typename TheOperand >
inline bool Type_::TakeOperand( Evaluation &, TheOperand & )
{
	return( true );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue( Evaluation &, TheQueue & )
{
	return( true );
}

	#undef Type_

#else
	#include "om/operations/drop_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( DropOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{drop}",
					System::Get().Evaluate( "drop find {drop} system" )
				);
			}

			TEST( Simple )
			{
				CHECK_EQUAL(
					"{4{5}6}",
					System::Get().Evaluate( "drop {1{2}3}{4{5}6}" )
				);
			}
		}
	}
}

	#endif

#endif
