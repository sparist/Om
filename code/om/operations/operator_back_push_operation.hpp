/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_OperatorBackPushOperation_ )

	#define Om_Operations_OperatorBackPushOperation_ \
	Om::Operations::OperatorBackPushOperation

	#include "om/definition.hpp"

	#define Om_Operations_OperatorBackPushOperation_GetName_() \
	"operator<-"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::OperatorBackPushOperation
		/*!
		\brief
			The \ref om__operations__operator_back_push_operation__ operation implementation.
		*/
		class OperatorBackPushOperation {
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );

		};

		namespace {

			static Definition< OperatorBackPushOperation > const theOperatorBackPushDefinition;

		}

	}

}

	#include "om/operations/operator_back_push_operation.cpp"

#endif
