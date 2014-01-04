/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operation_SkipOperation_

	#define Om_Operation_SkipOperation_ \
	Om::Operation::SkipOperation

	#include "om/expression.hpp"
	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_SkipOperation_GetName_() \
	"skip"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::SkipOperation

		/*!
		\brief
			The \ref om__operation__skip_operation__ operation implementation.
		*/
		class SkipOperation:
		public DefaultIncompleteOperation<SkipOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheSkipOperation>
			static void GiveElements(
				TheSkipOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

			SkipOperation();

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

			/*!
			If an empty Expression is taken as the first Operand, the Operation is complete. Therefore, the empty Expression can be used to indicate that the first Operand has not yet been received.
			*/
			Expression thisExpression;

		};

		namespace {

			static System::Definition<SkipOperation> const theSkipDefinition;

		}

	}

}

	#include "om/operation/skip_operation.cpp"

#endif
