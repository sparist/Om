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

\defgroup back_pull_term_operation terms->
	\ingroup operations
	\brief
		Pops the last term (\ref operator or \ref operand), quoted.
	\par Input
		<tt>{A B}</tt>
	\par Output
		<tt>{B} {A }</tt>
	\par Implementation
		Om#Operations#BackPullTermOperation
*/
#if !defined( Om_Operations_BackPullTermOperation_ )
	#define Om_Operations_BackPullTermOperation_ \
	Om::Operations::BackPullTermOperation

	#include "om/definition.hpp"

	#define Om_Operations_BackPullTermOperation_GetName_() "terms->"

namespace Om
{
	//! \cond
	struct Expression;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::BackPullTermOperation
		/*!
		\brief
			The \ref back_pull_term_operation Operation implementation.
		*/
		struct BackPullTermOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheEvaluator >
			static void Give( TheEvaluator & );

			//! The callback for PullOperation.
			template< typename TheQueue >
			static void Pull( Expression &, TheQueue & );
		};

		namespace
		{
			static Definition<
				BackPullTermOperation
			> const theBackPullTermDefinition;
		}
	}
}

	#include "om/operations/back_pull_term_operation.cpp"
#endif
