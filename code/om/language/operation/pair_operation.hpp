/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb

\defgroup om__operation__pair_operation__ pair
	\ingroup om__operation__
	\brief
		Normalizes the first \ref om__operand__ as containing an \ref om__expression__, then appends the second \ref om__operand__ to the \ref om__expression__.
	\par Input
		<tt>{A} {B}</tt>
	\par Output
		<tt>{A{B}}</tt>
	\par Implementation
		Om::Language::Operation::PairOperation
*/

#ifndef Om_Language_Operation_PairOperation_

	#define Om_Language_Operation_PairOperation_ \
	Om::Language::Operation::PairOperation

	#include "om/language/operation/default_incomplete_operation.hpp"
	#include "om/language/system.hpp"

	#define Om_Language_Operation_PairOperation_GetName_() \
	"pair"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::PairOperation

			/*!
			\brief
				The \ref om__operation__pair_operation__ operation implementation.
			*/
			class PairOperation:
			public DefaultIncompleteOperation<PairOperation> {

			public: // MARK: public (static)

				static char const * GetName();

				template <typename ThePairOperation>
				static void GiveElements(
					ThePairOperation &,
					Consumer &
				);

			public: // MARK: public (non-static)

				PairOperation();

				template <typename TheOperand>
				bool TakeOperand(
					Evaluation &,
					TheOperand &
				);

				template <typename TheProducer>
				bool TakeQuotedProducer(
					Evaluation &,
					TheProducer &
				);

			private: // MARK: private (non-static)

				Expression thisExpression;

			};

			namespace {

				static System::Definition<PairOperation> const thePairDefinition;

			}

		}

	}

}

	#include "om/language/operation/pair_operation.cpp"

#endif
