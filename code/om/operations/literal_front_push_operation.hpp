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

#if !defined( Om_Operations_LiteralFrontPushOperation_ )

	#define Om_Operations_LiteralFrontPushOperation_ \
	Om::Operations::LiteralFrontPushOperation

	#include "om/definition.hpp"

	#define Om_Operations_LiteralFrontPushOperation_GetName_() \
	"->literal"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::LiteralFrontPushOperation
		/*!
		\brief
			The \ref om__operations__literal_front_push_operation__ operation implementation.
		*/
		class LiteralFrontPushOperation {
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );

		};

		namespace {

			static Definition< LiteralFrontPushOperation > const theLiteralFrontPushDefinition;

		}

	}

}

	#include "om/operations/literal_front_push_operation.cpp"

#endif
