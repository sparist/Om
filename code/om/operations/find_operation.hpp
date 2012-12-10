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

\defgroup find_operation find
	\ingroup operations
	\brief
		Finds the \ref operand mapped to an \ref operator, if any, in a
		\ref lexicon.
	\par Input
		<tt>{operator} {lexicon}</tt>
	\par Output
		-	If an \ref operand is mapped to the \ref operator (or there is a
			default \ref operand):
			<blockquote><tt>{{operand}} {operator} {lexicon}</tt></blockquote>
		-	Else:
			<blockquote><tt>{} {operator} {lexicon}</tt></blockquote>
	\par Implementation
		Om#Operations#FindOperation
*/
#if !defined( Om_Operations_FindOperation_ )
	#define Om_Operations_FindOperation_ Om::Operations::FindOperation

	#include "om/default_evaluation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_FindOperation_GetName_() "find"

namespace Om
{
	//! \cond
	struct Lexicon;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::FindOperation
		/*!
		\brief
			The \ref find_operation Operation implementation.
		*/
		struct FindOperation
		:
		DefaultEvaluation< FindOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheFindOperation >
			static void GiveElements( TheFindOperation &, Queue & );

		public: // MARK: public (non-static)

			FindOperation();

			template< typename TheOperand >
			bool TakeOperand( Expansion &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Expansion &, TheQueue & );

		private: // MARK: private (non-static)

			void TakeLexicon( Expansion &, Lexicon & );

			//! The Operator to find.
			boost::optional< Operator > thisOperator;
		};

		namespace
		{
			static Definition< FindOperation > const theFindDefinition;
		}
	}
}

	#include "om/operations/find_operation.cpp"
#endif
