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

#ifndef Om_Operation_EvaluateOperation_

	#define Om_Operation_EvaluateOperation_ \
	Om::Operation::EvaluateOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_EvaluateOperation_GetName_() \
	"evaluate"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::EvaluateOperation

		/*!
		\brief
			The \ref om__operation__define_operation__ operation implementation.
		*/
		class EvaluateOperation :
		public DefaultIncompleteOperation<EvaluateOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheEvaluateOperation>
			static void GiveElements(
				TheEvaluateOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

			EvaluateOperation();

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

		};

		namespace {

			static System::Definition<EvaluateOperation> const theEvaluateDefinition;

		}

	}

}

	#include "om/operation/evaluate_operation.cpp"

#endif
