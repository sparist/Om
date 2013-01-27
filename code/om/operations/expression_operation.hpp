/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_ExpressionOperation_ )

	#define Om_Operations_ExpressionOperation_ \
	Om::Operations::ExpressionOperation

	#include "om/definition.hpp"
	#include "om/expression.hpp"
	#include "om/operations/program_operation.hpp"

namespace Om
{
	namespace Operations
	{
		//! The \ref expression_operation Operation implementation.
		typedef ProgramOperation< Expression > ExpressionOperation;

		namespace
		{
			static Definition< ExpressionOperation > const theExpressionDefinition;
		}
	}
}

#endif
