/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup operator_front_push_operation ->operator
	\ingroup operations
	\brief
		Pushes the contents of an \ref operand onto the front of an
		\ref operator (quoted).
	\par Input
		<tt>{A} {B}</tt>
	\par Output
		<tt>{AB}</tt>
	\par Implementation
		Om#Operations#OperatorFrontPushOperation
*/
#if !defined( Om_Operations_OperatorFrontPushOperation_ )
	#define Om_Operations_OperatorFrontPushOperation_ \
	Om::Operations::OperatorFrontPushOperation

	#include "om/definition.hpp"

	#define Om_Operations_OperatorFrontPushOperation_GetName_() "->operator"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::OperatorFrontPushOperation
		/*!
		\brief
			The \ref operator_front_push_operation Operation implementation.
		*/
		struct OperatorFrontPushOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheEvaluationTaker >
			static void Give( TheEvaluationTaker & );
		};

		namespace
		{
			static Definition<
				OperatorFrontPushOperation
			> const theOperatorFrontPushDefinition;
		}
	}
}

	#include "om/operations/operator_front_push_operation.cpp"
#endif
