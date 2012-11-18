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

\defgroup evaluate_operation evaluate
	\ingroup operation
	\brief
		Evaluates the \ref operand, using the current environment, and
		\ref dequote_operation "dequotes".
	\par Input
		<tt>{lexicon} {expression}</tt>
	\par Output
		<tt>evaluation</tt>
	\par Implementation
		Om#Operations#EvaluateOperation
*/
#if !defined( Om_Operations_EvaluateOperation_ )
	#define Om_Operations_EvaluateOperation_ Om::Operations::EvaluateOperation

	#include "om/default_evaluand.hpp"
	#include "om/definition.hpp"
	#include "om/operations/translate_operation.hpp"

	#define Om_Operations_EvaluateOperation_GetName_() "evaluate"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::EvaluateOperation
		/*!
		\brief
			The \ref evaluate_operation Operation implementation.
		*/
		struct EvaluateOperation
		:
		DefaultEvaluand< EvaluateOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheEvaluateOperation >
			static void GiveElements( TheEvaluateOperation &, Queue & );

		public: // MARK: public (non-static)

			EvaluateOperation();

			template< typename TheOperand >
			bool TakeOperand( Evaluator &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluator &, TheQueue & );

		private: // MARK: private (non-static)

			boost::optional< Lexicon > thisLexicon;
		};

		namespace
		{
			static Definition< EvaluateOperation > const theEvaluateDefinition;
		}
	}
}

	#include "om/operations/evaluate_operation.cpp"
#endif
