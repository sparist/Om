/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup expression_back_push_operation expression<-
	\ingroup operations
	\brief
		Pushes the contents of an \ref operand onto the back of an
		\ref expression (quoted).
	\par Input
		<tt>{A} {B}</tt>
	\par Output
		<tt>{B<br/>
		A}</tt>
	\par Implementation
		Om::Operations::ExpressionBackPushOperation
*/
#if !defined( Om_Operations_ExpressionBackPushOperation_ )
	#define Om_Operations_ExpressionBackPushOperation_ \
	Om::Operations::ExpressionBackPushOperation

	#include "om/definition.hpp"

	#define Om_Operations_ExpressionBackPushOperation_GetName_() "expression<-"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::ExpressionBackPushOperation
		/*!
		\brief
			The \ref expression_back_push_operation Operation implementation.
		*/
		struct ExpressionBackPushOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );
		};

		namespace
		{
			static Definition<
				ExpressionBackPushOperation
			> const theExpressionBackPushDefinition;
		}
	}
}

	#include "om/operations/expression_back_push_operation.cpp"
#endif
