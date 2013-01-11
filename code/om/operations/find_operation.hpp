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
