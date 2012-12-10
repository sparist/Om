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
#if defined( Om_Operations_DecodeOperation_ )

	#include "om/literal.hpp"

// MARK: Om::Operations::DecodeOperation

	#define Type_ Om::Operations::DecodeOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_DecodeOperation_GetName_() );
}

template< typename TheDecodeOperation >
inline void Type_::GiveElements( TheDecodeOperation &, Queue & theQueue )
{
	theQueue.TakeElement( GetOperator() );
}

// MARK: public (non-static)

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Expansion & theExpansion,
	TheOperand & theOperand
)
{
	return( this->TakeQuotedQueue( theExpansion, theOperand.GetProgram() ) );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Expansion & theExpansion,
	TheQueue & theQueue
)
{
	Literal theLiteral;
	{
		Operator theOperator;
		theOperator.TakeElements( theQueue );
		theOperator.Decode( theLiteral );
	}
	theExpansion.TakeQuotedQueue( theLiteral );
	return( true );
}

	#undef Type_

#else
	#include "om/operations/decode_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( DecodeOperation )
		{
			TEST( Simple )
			{
				CHECK_EQUAL(
					"{`{`}` {{}} {quote{s}} }",
					Environment().Evaluate(
						"decode {```{```}``` `{`{`}`}` {quote{s}} }"
					)
				);

				CHECK_EQUAL(
					"{{} {{}} {quote{s}} }",
					Environment().Evaluate( "decode {`{`}` {{}} {quote{s}} }" )
				);

				CHECK_EQUAL(
					"{ the {end: `} really: } ! }",
					Environment().Evaluate(
						"decode {` the` `{end:` ```}` really:` `}` !` }"
					)
				);

				// Test that each remaining encoded Operand Symbol is decoded.
				CHECK_EQUAL(
					"{ the {end: } really: }",
					Environment().Evaluate(
						"decode { the {end: `} really: } ! }"
					)
				);

				CHECK_EQUAL(
					"{ the {end: } really: }",
					Environment().Evaluate( "decode { the {end: } really: }" )
				);
			}
		}
	}
}

	#endif

#endif
