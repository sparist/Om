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

\defgroup back_pull_code_point_operation codepoints->
	\ingroup operations
	\brief
		Pops the last code point, quoted.
	\par Implementation
		Om#Operations#BackPullCodePointOperation
*/
#if !defined( Om_Operations_BackPullCodePointOperation_ )
	#define Om_Operations_BackPullCodePointOperation_ \
	Om::Operations::BackPullCodePointOperation

	#include "om/definition.hpp"

	#define Om_Operations_BackPullCodePointOperation_GetName_() "codepoints->"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::BackPullCodePointOperation
		/*!
		\brief
			The \ref back_pull_code_point_operation Operation implementation.
		*/
		struct BackPullCodePointOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheEvaluandTaker >
			static void Give( TheEvaluandTaker & );

			//! The callback for PullOperation.
			template< typename TheQueue >
			static void Pull( Operator &, TheQueue & );
		};

		namespace
		{
			static Definition<
				BackPullCodePointOperation
			> const theBackPullCodePointDefinition;
		}
	}
}

	#include "om/operations/back_pull_code_point_operation.cpp"
#endif
