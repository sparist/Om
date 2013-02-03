/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_SwapOperation_ )

	#define Om_Operations_SwapOperation_ \
	Om::Operations::SwapOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_SwapOperation_GetName_() \
	"swap"

namespace Om {
	namespace Operations {
		// MARK: - Om::Operations::SwapOperation
		/*!
		\brief
			The \ref swap_operation Operation implementation.
		*/
		class SwapOperation:
		public DefaultOperation< SwapOperation > {
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheSwapOperation >
			static void GiveElements(
				TheSwapOperation &,
				Queue &
			);

		public: // MARK: public (non-static)

			SwapOperation();

			template< typename TheOperand >
			bool TakeOperand(
				Evaluation &,
				TheOperand &
			);

			template< typename TheQueue >
			bool TakeQuotedQueue(
				Evaluation &,
				TheQueue &
			);

		private: // MARK: private (non-static)

			/*!
			\brief
				The Operand to swap with.
			*/
			Operand thisOperand;
		};

		namespace {
			static Definition< SwapOperation > const theSwapDefinition;
		}
	}
}

	#include "om/operations/swap_operation.cpp"

#endif
