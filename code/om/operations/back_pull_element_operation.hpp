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

\defgroup back_pull_element_operation element->
	\ingroup operations
	\brief
		Pops the last element, quoted.
	\par Input
		<tt>{A B}</tt>
	\par Output
		<tt>{B} {A }</tt>
	\par Implementation
		Om#Operations#BackPullElementOperation
*/
#if !defined( Om_Operations_BackPullElementOperation_ )
	#define Om_Operations_BackPullElementOperation_ \
	Om::Operations::BackPullElementOperation

	#include "om/definition.hpp"

	#define Om_Operations_BackPullElementOperation_GetName_() "element->"

namespace Om
{
	//! \cond
	struct Literal;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::BackPullElementOperation
		/*!
		\brief
			The \ref back_pull_element_operation Operation implementation.
		*/
		struct BackPullElementOperation
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
				BackPullElementOperation
			> const theBackPullElementDefinition;
		}
	}
}

	#include "om/operations/back_pull_element_operation.cpp"
#endif
