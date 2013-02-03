/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
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

	#define Om_Operations_FrontPullCodePointOperation_ \
	Om::Operations::FrontPullCodePointOperation

	#include "om/definition.hpp"

	#define Om_Operations_FrontPullCodePointOperation_GetName_() \
	"<-code points"

namespace Om {
	namespace Operations {

		// MARK: - Om::Operations::FrontPullCodePointOperation
		/*!
		\brief
			The \ref front_pull_code_point_operation Operation implementation.
		*/
		struct FrontPullCodePointOperation {
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );

			/*!
			\brief
				The callback for PullOperation.
			*/
			template< typename TheQueue >
			static void Pull(
				Operator &,
				TheQueue &
			);
		};

		namespace {
			static Definition< FrontPullCodePointOperation > const theFrontPullCodePointDefinition;
		}
	}
}

	#include "om/operations/front_pull_code_point_operation.cpp"

#endif
