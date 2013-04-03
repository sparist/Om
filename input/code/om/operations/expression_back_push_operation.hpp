/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operations_ExpressionBackPushOperation_

	#define Om_Operations_ExpressionBackPushOperation_ \
	Om::Operations::ExpressionBackPushOperation

	#include "om/system.hpp"

	#define Om_Operations_ExpressionBackPushOperation_GetName_() \
	"expression<-"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::ExpressionBackPushOperation

		/*!
		\brief
			The \ref om__operations__expression_back_push_operation__ operation implementation.
		*/
		class ExpressionBackPushOperation {

		public: // MARK: public (static)

			static char const * GetName();

			static void Give(Evaluation &);

		};

		namespace {

			static System::Definition<ExpressionBackPushOperation> const theExpressionBackPushDefinition;

		}

	}

}

	#include "om/operations/expression_back_push_operation.cpp"

#endif
