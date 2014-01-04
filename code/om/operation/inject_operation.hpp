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

#ifndef Om_Operation_InjectOperation_

	#define Om_Operation_InjectOperation_ \
	Om::Operation::InjectOperation

	#include "om/expression.hpp"
	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_InjectOperation_GetName_() \
	"inject"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::InjectOperation

		/*!
		\brief
			The \ref om__operation__inject_operation__ operation implementation.
		*/
		class InjectOperation:
		public DefaultIncompleteOperation<InjectOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheInjectOperation>
			static void GiveElements(
				TheInjectOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

			InjectOperation();

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

			Expression thisInjector;

			/*!
			\brief
				The argument to be used as Output.
			*/
			Expression thisOutput;

			/*!
			\brief
				The local Evaluator.
			\note
				This will hold a reference to the Evaluator's Translator, which must remain alive.
			*/
			boost::optional<Evaluator> thisScope;

		};

		namespace {

			static System::Definition<InjectOperation> const theInjectDefinition;

		}

	}

}

	#include "om/operation/inject_operation.cpp"

#endif
