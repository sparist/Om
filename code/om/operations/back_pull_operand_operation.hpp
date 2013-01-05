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

\defgroup back_pull_operand_operation elements->operand
	\ingroup operations
	\brief
		Casts to \ref literal and pops the last \ref operand (if any), quoted.
	\par Input
		<tt>{A {B}}</tt>
	\par Output
		<tt>{{B}} {A }</tt>
	\par Implementation
		Om#Operations#BackPullOperandOperation
*/
#if !defined( Om_Operations_BackPullOperandOperation_ )
	#define Om_Operations_BackPullOperandOperation_ \
	Om::Operations::BackPullOperandOperation

	#include "om/definition.hpp"

	#define Om_Operations_BackPullOperandOperation_GetName_() \
	"elements->operand"

namespace Om
{
	//! \cond
	struct Literal;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::BackPullOperandOperation
		/*!
		\brief
			The \ref back_pull_operand_operation Operation implementation.
		*/
		struct BackPullOperandOperation
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
				BackPullOperandOperation
			> const theBackPullOperandDefinition;
		}
	}
}

	#include "om/operations/back_pull_operand_operation.cpp"
#endif
