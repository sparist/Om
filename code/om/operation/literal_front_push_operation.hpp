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

\defgroup om__operation__literal_front_push_operation__ ->[literal]
	\ingroup om__operation__
	\brief
		Pushes the contents of an \ref om__operand__ onto the front of a \ref om__literal__ (quoted).
	\par Input
		<tt>{A} {B}</tt>
	\par Output
		<tt>{AB}</tt>
	\par Implementation
		Om::Operation::LiteralFrontPushOperation

	Normalization to a \ref om__literal__ only happens if an append occurs (i.e. the first \ref om__operand__ is non-empty); otherwise, it is left unchanged. However, since everything represents as a \ref om__literal__, this doesn't make an observable difference.
*/

#ifndef Om_Operation_LiteralFrontPushOperation_

	#define Om_Operation_LiteralFrontPushOperation_ \
	Om::Operation::LiteralFrontPushOperation

	#include "om/system.hpp"

	#define Om_Operation_LiteralFrontPushOperation_GetName_() \
	"->[literal]"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::LiteralFrontPushOperation

		/*!
		\brief
			The \ref om__operation__literal_front_push_operation__ operation implementation.
		*/
		class LiteralFrontPushOperation {

		public: // MARK: public (static)

			static char const * GetName();

			static void Give(Evaluation &);

		};

		namespace {

			static System::Definition<LiteralFrontPushOperation> const theLiteralFrontPushDefinition;

		}

	}

}

	#include "om/operation/literal_front_push_operation.cpp"

#endif
