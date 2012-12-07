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

\defgroup literal_front_push_operation ->literal
	\ingroup operations
	\brief
		Pushes the contents of an \ref operand onto the front of a \ref literal
		(quoted).
	\par Input
		<tt>{A} {B}</tt>
	\par Output
		<tt>{AB}</tt>
	\par Implementation
		Om#Operations#LiteralFrontPushOperation

	Normalization to a \ref literal only happens if an append occurs (i.e. the
	first \ref operand is non-empty); otherwise, it is left unchanged.  However,
	since everything represents as a \ref literal, this doesn't make an
	observable difference.
*/
#if !defined( Om_Operations_LiteralFrontPushOperation_ )
	#define Om_Operations_LiteralFrontPushOperation_ \
	Om::Operations::LiteralFrontPushOperation

	#include "om/definition.hpp"

	#define Om_Operations_LiteralFrontPushOperation_GetName_() "->literal"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::LiteralFrontPushOperation
		/*!
		\brief
			The \ref literal_front_push_operation Operation implementation.
		*/
		struct LiteralFrontPushOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheEvaluationTaker >
			static void Give( TheEvaluationTaker & );
		};

		namespace
		{
			static Definition<
				LiteralFrontPushOperation
			> const theLiteralFrontPushDefinition;
		}
	}
}

	#include "om/operations/literal_front_push_operation.cpp"
#endif
