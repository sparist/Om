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

\defgroup skip_operation skip
	\ingroup operation
	\brief
		Skips over an \ref operand and \ref dequote_operation "dequotes".
	\par Input
		<tt>{expression} {A}</tt>
	\par Output
		<tt>{A} expression</tt>
	\par Implementation
		SkipOperation
*/
#if !defined( Om_Operations_SkipOperation_ )
	#define Om_Operations_SkipOperation_ Om::Operations::SkipOperation

	#include "om/default_evaluand.hpp"
	#include "om/definition.hpp"
	#include "om/expression.hpp"

	#define Om_Operations_SkipOperation_GetName_() "skip"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::SkipOperation
		/*!
		\brief
			The \ref skip_operation Operation implementation.
		*/
		struct SkipOperation
		:
		DefaultEvaluand< SkipOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheSkipOperation >
			static void GiveElements( TheSkipOperation &, Queue & );

		public: // MARK: public (non-static)

			SkipOperation();

			template< typename TheOperand >
			bool TakeOperand( Evaluator &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluator &, TheQueue & );

		private: // MARK: private (non-static)

			/*!
			If an empty Expression is taken as the first Operand, the Evaluand
			is complete.  Therefore, the empty Expression can be used to
			indicate that the first Operand has not yet been received.
			*/
			Expression thisExpression;
		};

		namespace
		{
			static Definition< SkipOperation > const theSkipDefinition;
		}
	}
}

	#include "om/operations/skip_operation.cpp"
#endif
