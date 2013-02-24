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

#if !defined( Om_Operations_BackPullOperandOperation_ )

	#include "om/operations/back_pull_operand_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE( BackPullOperandOperationTest )

			BOOST_AUTO_TEST_CASE( DefinitionTest ) {
				BOOST_CHECK_EQUAL(
					"{elements->operand}",
					System::Get().Evaluate( "drop find {elements->operand} system" )
				);
			}

			BOOST_AUTO_TEST_CASE( GeneralTest ) {
				BOOST_CHECK_EQUAL(
					"{}{1{2}3}",
					System::Get().Evaluate( "elements->operand {1{2}3}" )
				);

				BOOST_CHECK_EQUAL(
					"{{2}}{1}",
					System::Get().Evaluate( "elements->operand {1{2}}" )
				);

				BOOST_CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate( "elements->operand {}" )
				);

				BOOST_CHECK_EQUAL(
					"{{only}}{}",
					System::Get().Evaluate( "elements->operand {{only}}" )
				);

				BOOST_CHECK_EQUAL(
					"elements->operand",
					System::Get().Evaluate( "elements->operand" )
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/literal.hpp"
	#include "om/operations/pull_operation.hpp"

// MARK: - Om::Operations::BackPullOperandOperation

	#define Type_ \
	Om::Operations::BackPullOperandOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return(
		Om_Operations_BackPullOperandOperation_GetName_()
	);
}

inline void Type_::Give( Evaluation & theEvaluation ) {
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
) {
	theLiteral.BackGive< Operand >( theQueue );
}

	#undef Type_

#endif
