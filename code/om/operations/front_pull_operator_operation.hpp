/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup front_pull_operator_operation operator<-elements
	\ingroup operations
	\brief
		Casts to \ref literal and pops the first \ref operator (if any), quoted.
	\par Input
		<tt>{A B}</tt>
	\par Output
		<tt>{A} { B}</tt>
	\par Implementation
		Om::Operations::FrontPullOperatorOperation
*/
#if !defined( Om_Operations_FrontPullOperatorOperation_ )
	#define Om_Operations_FrontPullOperatorOperation_ \
	Om::Operations::FrontPullOperatorOperation

	#include "om/definition.hpp"

	#define Om_Operations_FrontPullOperatorOperation_GetName_() \
	"operator<-elements"

namespace Om
{
	//! \cond
	struct Literal;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::FrontPullOperatorOperation
		/*!
		\brief
			The \ref front_pull_operator_operation Operation implementation.
		*/
		struct FrontPullOperatorOperation
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
				FrontPullOperatorOperation
			> const theFrontPullOperatorDefinition;
		}
	}
}

	#include "om/operations/front_pull_operator_operation.cpp"
#endif
