/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operations_PairOperation_

	#define Om_Operations_PairOperation_ \
	Om::Operations::PairOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_PairOperation_GetName_() \
	"pair"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::PairOperation
		/*!
		\brief
			The \ref om__operations__pair_operation__ operation implementation.
		*/
		class PairOperation:
		public DefaultOperation<PairOperation> {
		public: // MARK: public (static)

			static char const * GetName();

			template <typename ThePairOperation>
			static void GiveElements(
				ThePairOperation &,
				Queue &
			);

		public: // MARK: public (non-static)

			PairOperation();

			template <typename TheOperand>
			bool TakeOperand(
				Evaluation &,
				TheOperand &
			);

			template <typename TheQueue>
			bool TakeQuotedQueue(
				Evaluation &,
				TheQueue &
			);

		private: // MARK: private (non-static)

			Expression thisExpression;

		};

		namespace {

			static Definition<PairOperation> const thePairDefinition;

		}

	}

}

	#include "om/operations/pair_operation.cpp"

#endif
