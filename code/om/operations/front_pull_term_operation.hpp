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

\defgroup front_pull_term_operation <-term
	\ingroup operations
	\brief
		Pops the first term (\ref operator or \ref operand), quoted.
	\par Input
		<tt>{A B}</tt>
	\par Output
		<tt>{A} { B}</tt>
	\par Implementation
		Om#Operations#FrontPullTermOperation
*/
#if !defined( Om_Operations_FrontPullTermOperation_ )
	#define Om_Operations_FrontPullTermOperation_ \
	Om::Operations::FrontPullTermOperation

	#include "om/definition.hpp"

	#define Om_Operations_FrontPullTermOperation_GetName_() "<-term"

namespace Om
{
	//! \cond
	struct Expression;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::FrontPullTermOperation
		/*!
		\brief
			The \ref front_pull_term_operation Operation implementation.
		*/
		struct FrontPullTermOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );

			//! The callback for PullOperation.
			template< typename TheQueue >
			static void Pull( Expression &, TheQueue & );
		};

		namespace
		{
			static Definition<
				FrontPullTermOperation
			> const theFrontPullTermDefinition;
		}
	}
}

	#include "om/operations/front_pull_term_operation.cpp"
#endif
