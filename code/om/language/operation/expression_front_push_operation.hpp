/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb

\defgroup om__operation__expression_front_push_operation__ ->[expression]
	\ingroup om__operation__
	\brief
		Pushes the contents of an \ref om__operand__ onto the front of an \ref om__expression__ (quoted).
	\par Input
		<tt>{A} {B}</tt>
	\par Output
		<tt>{A<br/>
		B}</tt>
	\par Implementation
		Om::Language::Operation::ExpressionFrontPushOperation
*/

#ifndef Om_Language_Operation_ExpressionFrontPushOperation_

	#define Om_Language_Operation_ExpressionFrontPushOperation_ \
	Om::Language::Operation::ExpressionFrontPushOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_ExpressionFrontPushOperation_GetName_() \
	"->[expression]"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::ExpressionFrontPushOperation

			/*!
			\brief
				The \ref om__operation__expression_front_push_operation__ operation implementation.
			*/
			class ExpressionFrontPushOperation {

			public: // MARK: public (static)

				static char const * GetName();

				static void Give(Evaluation &);

			};

			namespace {

				static System::Definition<ExpressionFrontPushOperation> const theExpressionFrontPushDefinition;

			}

		}

	}

}

	#include "om/language/operation/expression_front_push_operation.cpp"

#endif
