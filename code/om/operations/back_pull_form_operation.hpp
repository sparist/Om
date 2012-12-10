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

\defgroup back_pull_form_operation forms->
	\ingroup operations
	\brief
		Pops the last form (a non-empty list of zero or one
		\ref operator "Operator(s)", followed by zero or more
		\ref operand "Operands"), quoted.
	\par Implementation
		Om#Operations#BackPullFormOperation
*/
#if !defined( Om_Operations_BackPullFormOperation_ )
	#define Om_Operations_BackPullFormOperation_ \
	Om::Operations::BackPullFormOperation

	#include "om/definition.hpp"

	#define Om_Operations_BackPullFormOperation_GetName_() "forms->"

namespace Om
{
	//! \cond
	struct Expression;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::BackPullFormOperation
		/*!
		\brief
			The \ref back_pull_form_operation Operation implementation.
		*/
		struct BackPullFormOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Expansion & );

			//! The callback for PullOperation.
			template< typename TheQueue >
			static void Pull( Expression &, TheQueue & );
		};

		namespace
		{
			static Definition<
				BackPullFormOperation
			> const theBackPullFormDefinition;
		}
	}
}

	#include "om/operations/back_pull_form_operation.cpp"
#endif
