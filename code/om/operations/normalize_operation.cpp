/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Operations_NormalizeOperation_ )

// MARK: Om::Operations::NormalizeOperation

	#define Type_ \
	Om::Operations::NormalizeOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return( Om_Operations_NormalizeOperation_GetName_() );
}

template< typename TheNormalizeOperation >
inline void Type_::GiveElements(
	TheNormalizeOperation &,
	Queue & theQueue
) {
	theQueue.TakeElement( GetOperator() );
}

// MARK: public (non-static)

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
) {
	assert( !theOperand.IsEmpty() );
	return(
		this->TakeQuotedQueue(
			theEvaluation,
			*theOperand.GetProgram()
		)
	);
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
) {
	Operator theOperator;
	theOperator.TakeElements( theQueue );
	theOperator.Normalize();
	theEvaluation.TakeQuotedQueue( theOperator );
	return( true );
}

	#undef Type_

#else

	#include "om/operations/normalize_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

// MARK: -
namespace Om {
	namespace Operations {
		SUITE( NormalizeOperation ) {
			TEST( Definition ) {
				CHECK_EQUAL(
					"{normalize}",
					System::Get().Evaluate( "drop find {normalize} system" )
				);
			}

			TEST( Simple ) {
				CHECK_EQUAL(
					(
						"{"
						"\xE1\x84\x80"
						"\xE1\x85\xA1"
						"\xE1\x86\xA8"
						"}"
					),
					System::Get().Evaluate(
						"normalize {"
						"\xEA\xB0\x81"
						"}"
					)
				);
			}
		}
	}
}

	#endif

#endif
