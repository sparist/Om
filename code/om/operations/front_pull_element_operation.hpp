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

\defgroup front_pull_element_operation <-elements
	\ingroup operations
	\brief
		Pops the first element, quoted.
	\par Input
		<tt>{A B}</tt>
	\par Output
		<tt>{A} { B}</tt>
	\par Implementation
		Om#Operations#FrontPullElementOperation
*/
#if !defined( Om_Operations_FrontPullElementOperation_ )
	#define Om_Operations_FrontPullElementOperation_ \
	Om::Operations::FrontPullElementOperation

	#include "om/definition.hpp"

	#define Om_Operations_FrontPullElementOperation_GetName_() "<-elements"

namespace Om
{
	//! \cond
	struct Literal;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::FrontPullElementOperation
		/*!
		\brief
			The \ref front_pull_element_operation Operation implementation.
		*/
		struct FrontPullElementOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );

			//! The callback for PullOperation.
			template< typename TheQueue >
			static void Pull( Literal &, TheQueue & );
		};

		namespace
		{
			static Definition<
				FrontPullElementOperation
			> const theFrontPullElementDefinition;
		}
	}
}

	#include "om/operations/front_pull_element_operation.cpp"
#endif
