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

#ifndef Om_Operation_DequoteOperation_

	#define Om_Operation_DequoteOperation_ \
	Om::Operation::DequoteOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_DequoteOperation_GetName_() \
	"dequote"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::DequoteOperation

		/*!
		\brief
			The \ref om__operation__dequote_operation__ operation implementation.
		*/
		class DequoteOperation:
		public DefaultIncompleteOperation<DequoteOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheDequoteOperation>
			static void GiveElements(
				TheDequoteOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

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

			static System::Definition<DequoteOperation> const theDequoteDefinition;

		}

	}

}

	#include "om/operation/dequote_operation.cpp"

#endif
