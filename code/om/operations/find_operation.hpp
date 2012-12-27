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
		Finds the \ref operator, and its \ref operand mapping (if any), in a
		\ref lexicon.
	\par Input
		<tt>{operator} {lexicon}</tt>
	\par Output
		-	If the \ref operator is found:
			-	If an \ref operand is mapped to the \ref operator "operator":
					<blockquote><tt>{{operand}} {operator}
						{lexicon}</tt></blockquote>
			-	Else:
					<blockquote><tt>{} {operator} {lexicon}</tt></blockquote>
		-	Else:
				<blockquote><tt>{} {} {lexicon}</tt></blockquote>
	\par Implementation
		Om#Operations#FindOperation
*/
#if !defined( Om_Operations_FindOperation_ )
	#define Om_Operations_FindOperation_ Om::Operations::FindOperation

	#include "om/default_operation.hpp"
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
		DefaultOperation< FindOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheFindOperation >
			static void GiveElements( TheFindOperation &, Queue & );

		public: // MARK: public (non-static)

			FindOperation();

			template< typename TheOperand >
			bool TakeOperand( Evaluation &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluation &, TheQueue & );

		private: // MARK: private (non-static)

			void TakeLexicon( Evaluation &, Lexicon & );

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
