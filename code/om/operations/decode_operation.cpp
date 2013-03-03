/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_DecodeOperation_ )

	#include "om/operations/decode_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE( DecodeOperationTest )

			BOOST_AUTO_TEST_CASE( DefinitionTest ) {
				BOOST_CHECK_EQUAL(
					"{decode}",
					System::Get().Evaluate( "drop find {decode} system" )
				);
			}

			BOOST_AUTO_TEST_CASE( SimpleTest ) {
				BOOST_CHECK_EQUAL(
					"{`{`}` {{}} {quote{s}} }",
					System::Get().Evaluate( "decode {```{```}``` `{`{`}`}` {quote{s}} }" )
				);

				BOOST_CHECK_EQUAL(
					"{{} {{}} {quote{s}} }",
					System::Get().Evaluate( "decode {`{`}` {{}} {quote{s}} }" )
				);

				BOOST_CHECK_EQUAL(
					"{ the {end: `} really: } ! }",
					System::Get().Evaluate( "decode {` the` `{end:` ```}` really:` `}` !` }" )
				);

				// Test that each remaining encoded Operand Symbol is decoded.
				BOOST_CHECK_EQUAL(
					"{ the {end: } really: }",
					System::Get().Evaluate( "decode { the {end: `} really: } ! }" )
				);

				BOOST_CHECK_EQUAL(
					"{ the {end: } really: }",
					System::Get().Evaluate( "decode { the {end: } really: }" )
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/literal.hpp"

// MARK: - Om::Operations::DecodeOperation

	#define Type_ \
	Om::Operations::DecodeOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return(
		Om_Operations_DecodeOperation_GetName_()
	);
}

template< typename TheDecodeOperation >
inline void Type_::GiveElements(
	TheDecodeOperation &,
	Queue & theQueue
) {
	theQueue.TakeElement(
		GetOperator()
	);
}

// MARK: public (non-static)

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
) {
	assert(
		!theOperand.IsEmpty()
	);
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
	Literal theLiteral;
	{
		Operator theOperator;
		theOperator.TakeElements( theQueue );
		theOperator.Decode( theLiteral );
	}
	theEvaluation.TakeQuotedQueue( theLiteral );
	return( true );
}

	#undef Type_

#endif
