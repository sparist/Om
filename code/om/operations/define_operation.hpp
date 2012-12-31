/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
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

\defgroup define_operation define
	\ingroup operations
	\brief
		\ref evaluate_operation "Evaluates" and
		\ref dequote_operation "dequotes" an \ref expression with an environment
		that contains additionally defined \ref operator "operators".
	\par Input
		A \ref lexicon, containing the additional operator definition(s), and an
		\ref expression to evaluate.
	\par Output
		The evaluation of the \ref expression under the temporarily extended
		environment, \ref dequote_operation "dequoted".
	\par Implementation
		Om#Operations#DefineOperation
*/
#if !defined( Om_Operations_DefineOperation_ )
	#define Om_Operations_DefineOperation_ Om::Operations::DefineOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_DefineOperation_GetName_() "define"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::DefineOperation
		/*!
		\brief
			The \ref define_operation Operation implementation.
		*/
		struct DefineOperation
		:
		DefaultOperation< DefineOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheDefineOperation >
			static void GiveElements( TheDefineOperation &, Queue & );

		public: // MARK: public (non-static)

			DefineOperation();

			template< typename TheOperand >
			bool TakeOperand( Evaluation &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluation &, TheQueue & );

		private: // MARK: private (non-static)

			boost::optional< Lexicon > thisLexicon;
		};

		namespace
		{
			static Definition< DefineOperation > const theDefineDefinition;
		}
	}
}

	#include "om/operations/define_operation.cpp"
#endif
