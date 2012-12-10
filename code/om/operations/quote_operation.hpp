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

\defgroup quote_operation quote
	\ingroup operations
	\brief
		Encloses an \ref operand in braces.
	\par Input
		<tt>{A}</tt>
	\par Output
		<tt>{{A}}</tt>
	\par Implementation
		Om#Operations#QuoteOperation
*/
#if !defined( Om_Operations_QuoteOperation_ )
	#define Om_Operations_QuoteOperation_ Om::Operations::QuoteOperation

	#include "om/default_evaluation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_QuoteOperation_GetName_() "quote"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::QuoteOperation
		/*!
		\brief
			The \ref quote_operation Operation implementation.
		*/
		struct QuoteOperation
		:
		DefaultEvaluation< QuoteOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheQuoteOperation >
			static void GiveElements( TheQuoteOperation &, Queue & );

		public: // MARK: public (non-static)

			template< typename TheOperand >
			bool TakeOperand( Expansion &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Expansion &, TheQueue & );
		};

		namespace
		{
			static Definition< QuoteOperation > const theQuoteDefinition;
		}
	}
}

	#include "om/operations/quote_operation.cpp"
#endif

