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
#if defined( Om_Operations_DoOperation_ )

	#include "om/operations/dequote_operation.hpp"
	#include "om/operations/operator_operation.hpp"

// MARK: Om::Operations::DoOperation

	#define Type_ Om::Operations::DoOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_DoOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation )
{
	DequoteOperation::Give( theEvaluation );
	OperatorOperation::Give( theEvaluation );
}

	#undef Type_

#else
	#include "om/operations/do_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( DoOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{do}",
					System::Get().Evaluate( "drop find {do} system" )
				);
			}

			TEST( Simple )
			{
				CHECK_EQUAL(
					"{a}{bc}",
					System::Get().Evaluate( "do {<-code points} {abc}" )
				);
			}
		}
	}
}

	#endif

#endif
