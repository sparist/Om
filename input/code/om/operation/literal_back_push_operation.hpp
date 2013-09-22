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

#ifndef Om_Operation_LiteralBackPushOperation_

	#define Om_Operation_LiteralBackPushOperation_ \
	Om::Operation::LiteralBackPushOperation

	#include "om/system.hpp"

	#define Om_Operation_LiteralBackPushOperation_GetName_() \
	"literal<-"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::LiteralBackPushOperation

		/*!
		\brief
			The \ref om__operations__literal_back_push_operation__ operation implementation.
		*/
		class LiteralBackPushOperation {

		public: // MARK: public (static)

			static char const * GetName();

			static void Give(Evaluation &);

		};

		namespace {

			static System::Definition<LiteralBackPushOperation> const theLiteralBackPushDefinition;

		}

	}

}

	#include "om/operation/literal_back_push_operation.cpp"

#endif
