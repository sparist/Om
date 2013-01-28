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

#if !defined( Om_Operations_EvaluateOperation_ )

	#define Om_Operations_EvaluateOperation_ \
	Om::Operations::EvaluateOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_EvaluateOperation_GetName_() \
	"evaluate"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::EvaluateOperation
		/*!
		\brief
			The \ref define_operation Operation implementation.
		*/
		struct EvaluateOperation:
		DefaultOperation< EvaluateOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheEvaluateOperation >
			static void GiveElements(
				TheEvaluateOperation &,
				Queue &
			);

		public: // MARK: public (non-static)

			EvaluateOperation();

			template< typename TheOperand >
			bool TakeOperand(
				Evaluation &,
				TheOperand &
			);

			template< typename TheQueue >
			bool TakeQuotedQueue(
				Evaluation &,
				TheQueue &
			);
		};

		namespace
		{
			static Definition< EvaluateOperation > const theEvaluateDefinition;
		}
	}
}

	#include "om/operations/evaluate_operation.cpp"

#endif
