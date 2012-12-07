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

\defgroup choose_operation choose
	\ingroup operations
	\brief
		If the conditional \ref operand is empty, it is replaced with the
		empty-case \ref operand; otherwise, it is replaced with the
		non-empty-case \ref operand.
	\par Input
		<tt>{empty case} {non-empty case} {conditional}</tt>
	\par Implementation
		Om#Operations#ChooseOperation
*/
#if !defined( Om_Operations_ChooseOperation_ )
	#define Om_Operations_ChooseOperation_ Om::Operations::ChooseOperation

	#include "om/default_evaluation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_ChooseOperation_GetName_() "choose"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::ChooseOperation
		/*!
		\brief
			The \ref choose_operation Operation implementation.
		*/
		struct ChooseOperation
		:
		DefaultEvaluation< ChooseOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheChooseOperation >
			static void GiveElements( TheChooseOperation &, Queue & );

		public: // MARK: public (non-static)

			ChooseOperation();

			template< typename TheOperand >
			bool TakeOperand( Evaluator &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluator &, TheQueue & );

		private: // MARK: private (non-static)

			//! The empty case handler.
			Operand thisEmptyCase;

			//! The non-empty case handler.
			Operand thisNonEmptyCase;

			//! The number of Operands received thus far.
			char unsigned thisOperandCount;
		};

		namespace
		{
			static Definition< ChooseOperation > const theChooseDefinition;
		}
	}
}

	#include "om/operations/choose_operation.cpp"
#endif
