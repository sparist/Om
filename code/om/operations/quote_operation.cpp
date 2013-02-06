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

#if !defined( Om_Operations_QuoteOperation_ )

	#include "om/operations/quote_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om {

	namespace Operations {

		SUITE( QuoteOperation ) {

			TEST( Definition ) {
				CHECK_EQUAL(
					"{quote}",
					System::Get().Evaluate( "drop find {quote} system" )
				);
			}

			TEST( Simple ) {
				CHECK_EQUAL(
					"{{1{2}3}}",
					System::Get().Evaluate( "quote {1{2}3}" )
				);
			}

		}

	}

}

	#endif

#else

	#include "om/literal.hpp"

// MARK: - Om::Operations::QuoteOperation

	#define Type_ \
	Om::Operations::QuoteOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return( Om_Operations_QuoteOperation_GetName_() );
}

template< typename TheQuoteOperation >
inline void Type_::GiveElements(
	TheQuoteOperation &,
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
	theEvaluation.TakeQuotedQueue( theOperand );
	return( true );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
) {
	Operand theOperand( theQueue.GiveProgram() );
	theEvaluation.TakeQuotedQueue( theOperand );
	return( true );
}

	#undef Type_

#endif
