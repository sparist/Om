/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup om__operation__expression_operation__ expression
	\ingroup om__operation__
	\brief
		Normalizes the \ref om__operand__ as a quoted \ref om__expression__.
	\par Implementation
		Om::Operation::ExpressionOperation
*/

#ifndef Om_Operation_ExpressionOperation_

	#define Om_Operation_ExpressionOperation_ \
	Om::Operation::ExpressionOperation

	#include "om/expression.hpp"
	#include "om/operation/program_operation.hpp"
	#include "om/system.hpp"

namespace Om {

	namespace Operation {

		/*!
		\brief
			The \ref om__operation__expression_operation__ operation implementation.
		*/
		typedef ProgramOperation<Expression> ExpressionOperation;

		namespace {

			static System::Definition<ExpressionOperation> const theExpressionDefinition;

		}

	}

}

#endif
