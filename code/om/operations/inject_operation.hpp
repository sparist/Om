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

#if !defined( Om_Operations_InjectOperation_ )

	#define Om_Operations_InjectOperation_ \
	Om::Operations::InjectOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"
	#include "om/expression.hpp"

	#define Om_Operations_InjectOperation_GetName_() \
	"inject"

namespace Om {
	namespace Operations {

		// MARK: - Om::Operations::InjectOperation
		/*!
		\brief
			The \ref inject_operation Operation implementation.
		*/
		class InjectOperation:
		public DefaultOperation< InjectOperation > {
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheInjectOperation >
			static void GiveElements(
				TheInjectOperation &,
				Queue &
			);

		public: // MARK: public (non-static)

			InjectOperation();

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
			boost::optional< Evaluator > thisScope;
		};

		namespace {
			static Definition< InjectOperation > const theInjectDefinition;
		}
	}
}

	#include "om/operations/inject_operation.cpp"

#endif
