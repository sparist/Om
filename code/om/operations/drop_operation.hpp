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

#if !defined( Om_Operations_DropOperation_ )

	#define Om_Operations_DropOperation_ \
	Om::Operations::DropOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_DropOperation_GetName_() \
	"drop"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::DropOperation
		/*!
		\brief
			The \ref drop_operation Operation implementation.
		*/
		struct DropOperation:
		DefaultOperation< DropOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheDropOperation >
			static void GiveElements(
				TheDropOperation &,
				Queue &
			);

		public: // MARK: public (non-static)

			virtual bool ReadQuotedElements(
				Evaluation &,
				Parser &
			);

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
			static Definition< DropOperation > const theDropDefinition;
		}
	}
}

	#include "om/operations/drop_operation.cpp"

#endif
