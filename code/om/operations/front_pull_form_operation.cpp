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

#if !defined( Om_Operations_FrontPullFormOperation_ )

	#include "om/operations/front_pull_form_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE( FrontPullFormOperationTest )

			BOOST_AUTO_TEST_CASE( DefinitionTest ) {
				BOOST_CHECK_EQUAL(
					"{<-forms}",
					System::Get().Evaluate( "drop find {<-forms} system" )
				);
			}

			BOOST_AUTO_TEST_CASE( GeneralTest ) {
				BOOST_CHECK_EQUAL(
					"{1{2}{3}}{4{5}{6}}",
					System::Get().Evaluate( "<-forms {1{2}{3}4{5}{6}}" )
				);

				BOOST_CHECK_EQUAL(
					"{1}{2}",
					System::Get().Evaluate( "<-forms {1 2}" )
				);

				BOOST_CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate( "<-forms {}" )
				);

				BOOST_CHECK_EQUAL(
					"{only}{}",
					System::Get().Evaluate( "<-forms {only}" )
				);

				BOOST_CHECK_EQUAL(
					"<-forms",
					System::Get().Evaluate( "<-forms" )
				);

				BOOST_CHECK_EQUAL(
					"{a{b}{c}}{}",
					System::Get().Evaluate( "<-forms{a{b}{c}}" )
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/expression.hpp"
	#include "om/operations/pull_operation.hpp"

// MARK: - Om::Operations::FrontPullFormOperation

	#define Type_ \
	Om::Operations::FrontPullFormOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return(
		Om_Operations_FrontPullFormOperation_GetName_()
	);
}

inline void Type_::Give( Evaluation & theEvaluation ) {
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation<
				Expression,
				FrontPullFormOperation
			>
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull(
	Expression & theExpression,
	TheQueue & theQueue
) {
	theExpression.FrontGiveForm( theQueue );
}

	#undef Type_

#endif
