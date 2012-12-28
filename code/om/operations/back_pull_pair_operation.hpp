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

\defgroup back_pull_pair_operation pair->
	\ingroup operations
	\brief
		Pops the last pair (a non-empty list of zero or one
		\ref operator "Operator(s)", followed by zero or one
		\ref operand "Operand(s)"), quoted.
	\par Implementation
		Om#Operations#BackPullPairOperation
*/
#if !defined( Om_Operations_BackPullPairOperation_ )
	#define Om_Operations_BackPullPairOperation_ \
	Om::Operations::BackPullPairOperation

	#include "om/definition.hpp"

	#define Om_Operations_BackPullPairOperation_GetName_() "pair->"

namespace Om
{
	//! \cond
	struct Lexicon;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::BackPullPairOperation
		/*!
		\brief
			The \ref back_pull_pair_operation Operation implementation.
		*/
		struct BackPullPairOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );

			//! The callback for PullOperation.
			template< typename TheQueue >
			static void Pull( Lexicon &, TheQueue & );
		};

		namespace
		{
			static Definition<
				BackPullPairOperation
			> const theBackPullPairDefinition;
		}
	}
}

	#include "om/operations/back_pull_pair_operation.cpp"
#endif
