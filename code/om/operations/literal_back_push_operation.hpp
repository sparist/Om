/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
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

\defgroup literal_back_push_operation literal<-
	\ingroup operations
	\brief
		Pushes the contents of an \ref operand onto the back of a \ref literal
		(quoted).
	\par Input
		<tt>{A} {B}</tt>
	\par Output
		<tt>{BA}</tt>
	\par Implementation
		Om#Operations#LiteralBackPushOperation
*/
#if !defined( Om_Operations_LiteralBackPushOperation_ )
	#define Om_Operations_LiteralBackPushOperation_ \
	Om::Operations::LiteralBackPushOperation

	#include "om/definition.hpp"

	#define Om_Operations_LiteralBackPushOperation_GetName_() "literal<-"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::LiteralBackPushOperation
		/*!
		\brief
			The \ref literal_back_push_operation Operation implementation.
		*/
		struct LiteralBackPushOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );
		};

		namespace
		{
			static Definition<
				LiteralBackPushOperation
			> const theLiteralBackPushDefinition;
		}
	}
}

	#include "om/operations/literal_back_push_operation.cpp"
#endif
