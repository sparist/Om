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

\defgroup swap_operation swap
	\ingroup operations
	\brief
		Swaps two \ref operand "Operands".
	\par Input
		<tt>{A}{B}</tt>
	\par Output
		<tt>{B}{A}</tt>
	\par Implementation
		Om#Operations#SwapOperation
*/
#if !defined( Om_Operations_SwapOperation_ )
	#define Om_Operations_SwapOperation_ Om::Operations::SwapOperation

	#include "om/default_evaluation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_SwapOperation_GetName_() "swap"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::SwapOperation
		/*!
		\brief
			The \ref swap_operation Operation implementation.
		*/
		struct SwapOperation
		:
		DefaultEvaluation< SwapOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheSwapOperation >
			static void GiveElements( TheSwapOperation &, Queue & );

		public: // MARK: public (non-static)

			SwapOperation();

			template< typename TheOperand >
			bool TakeOperand( Expansion &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Expansion &, TheQueue & );

		private: // MARK: private (non-static)

			//! The Operand to swap with.
			boost::optional< Operand > thisOperand;
		};

		namespace
		{
			static Definition< SwapOperation > const theSwapDefinition;
		}
	}
}

	#include "om/operations/swap_operation.cpp"
#endif
