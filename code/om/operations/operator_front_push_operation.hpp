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

			static void Give( Evaluation & );
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
