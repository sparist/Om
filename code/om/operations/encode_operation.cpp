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

#if !defined( Om_Operations_EncodeOperation_ )

	#include "om/operations/encode_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE( EncodeOperationTest )

			BOOST_AUTO_TEST_CASE( DefinitionTest ) {
				BOOST_CHECK_EQUAL(
					"{encode}",
					System::Get().Evaluate( "drop find {encode} system" )
				);
			}

			BOOST_AUTO_TEST_CASE( SimpleTest ) {
				BOOST_CHECK_EQUAL(
					"{```{```}``` `{`{`}`}` }",
					System::Get().Evaluate( "encode {`{`}` {{}} }" )
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/literal.hpp"

// MARK: - Om::Operations::EncodeOperation

	#define Type_ \
	Om::Operations::EncodeOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return(
		Om_Operations_EncodeOperation_GetName_()
	);
}

template< typename TheEncodeOperation >
inline void Type_::GiveElements(
	TheEncodeOperation &,
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
	Operator theOperator;
	theOperator.Encode( theQueue );
	theEvaluation.TakeQuotedQueue( theOperator );
	return( true );
}

	#undef Type_

#endif
