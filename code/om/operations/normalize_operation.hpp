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

\defgroup normalize_operation normalize
	\ingroup operations
	\brief
		Performs a Unicode compatibility normalization
		(<a href="http://unicode.org/reports/tr15/">NFKD</a>) on the contents
		of the operand.
	\par Implementation
		Om#Operations#NormalizeOperation
*/
#if !defined( Om_Operations_NormalizeOperation_ )
	#define Om_Operations_NormalizeOperation_ \
	Om::Operations::NormalizeOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_NormalizeOperation_GetName_() "normalize"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::NormalizeOperation
		/*!
		\brief
			The \ref normalize_operation Operation implementation.
		*/
		struct NormalizeOperation
		:
		DefaultOperation< NormalizeOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheNormalizeOperation >
			static void GiveElements( TheNormalizeOperation &, Queue & );

		public: // MARK: public (non-static)

			template< typename TheOperand >
			bool TakeOperand( Evaluation &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluation &, TheQueue & );
		};

		namespace
		{
			static Definition<
				NormalizeOperation
			> const theNormalizeDefinition;
		}
	}
}

	#include "om/operations/normalize_operation.cpp"
#endif
