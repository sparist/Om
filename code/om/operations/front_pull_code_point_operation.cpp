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

#if !defined( Om_Operations_FrontPullCodePointOperation_ )

	#include "om/operations/front_pull_code_point_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om {

	namespace Operations {

		SUITE( FrontPullCodePointOperation ) {

			TEST( Definition ) {
				CHECK_EQUAL(
					"{<-code` points}",
					System::Get().Evaluate( "drop find {<-code` points} system" )
				);
			}

			TEST( General ) {
				CHECK_EQUAL(
					"{1}{`{2`}three}",
					System::Get().Evaluate( "<-code` points {1{2}three}" )
				);

				CHECK_EQUAL(
					"{` }{}",
					System::Get().Evaluate( "<-code` points {` }" )
				);

				CHECK_EQUAL(
					(
						"{"
						"\xC3\x98"
						"}{"
						"\xCC\x81"
						"a}"
					),
					System::Get().Evaluate(
						"<-code` points {"
						"\xC7\xBE"
						"a}"
					)
				);

				CHECK_EQUAL(
					"{` }{}",
					System::Get().Evaluate( "<-code` points { }" )
				);

				CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate( "<-code` points {}" )
				);

				CHECK_EQUAL(
					"<-code` points",
					System::Get().Evaluate( "<-code` points" )
				);
			}
			
			TEST( MultiCodePointCharacter ) {
				CHECK_EQUAL(
					(
						"{"
						"\xE1\x84\x80"
						"}{"
						"\xE1\x85\xA1"
						"\xE1\x84\x82"
						"}"
					),
					System::Get().Evaluate(
						"<-code` points"
						"{"
						"\xE1\x84\x80"
						"\xE1\x85\xA1"
						"\xE1\x84\x82"
						"}"
					)
				);
			}

		}

	}

}

	#endif

#else

	#include "om/operations/pull_operation.hpp"

// MARK: - Om::Operations::FrontPullCodePointOperation

	#define Type_ \
	Om::Operations::FrontPullCodePointOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return( Om_Operations_FrontPullCodePointOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation ) {
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation<
				Operator,
				FrontPullCodePointOperation
			>
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull(
	Operator & theOperator,
	TheQueue & theQueue
) {
	theOperator.FrontGiveCodePoint( theQueue );
}

	#undef Type_

#endif
