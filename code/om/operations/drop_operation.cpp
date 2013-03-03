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

#if !defined( Om_Operations_DropOperation_ )

	#include "om/operations/drop_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE( DropOperationTest )

			BOOST_AUTO_TEST_CASE( DefinitionTest ) {
				BOOST_CHECK_EQUAL(
					"{drop}",
					System::Get().Evaluate( "drop find {drop} system" )
				);
			}

			BOOST_AUTO_TEST_CASE( SimpleTest ) {
				BOOST_CHECK_EQUAL(
					"{4{5}6}",
					System::Get().Evaluate( "drop {1{2}3}{4{5}6}" )
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

// MARK: - Om::Operations::DropOperation

	#define Type_ \
	Om::Operations::DropOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return(
		Om_Operations_DropOperation_GetName_()
	);
}

template< typename TheDropOperation >
inline void Type_::GiveElements(
	TheDropOperation &,
	Queue & theQueue
) {
	theQueue.TakeElement(
		GetOperator()
	);
}

// MARK: public (non-static)

inline bool Type_::ReadQuotedElements(
	Evaluation &,
	Parser & theParser
) {
	while( theParser ) {
		theParser.Pop();
	}
	return( true );
}

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation &,
	TheOperand &
) {
	return( true );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation &,
	TheQueue &
) {
	return( true );
}

	#undef Type_

#endif
