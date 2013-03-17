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

#ifndef Om_Operations_EqualsOperation_

	#define Om_Operations_EqualsOperation_ \
	Om::Operations::EqualsOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_EqualsOperation_GetName_() \
	"="

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::EqualsOperation

		/*!
		\brief
			The \ref om__operations__equals_operation__ operation implementation.
		*/
		class EqualsOperation:
		public DefaultOperation<EqualsOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheEqualsOperation>
			static void GiveElements(
				TheEqualsOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

			EqualsOperation();

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

			template <typename TheProducer>
			bool IsMatch(TheProducer &) const;

			/*!
			\brief
				The Operand to compare with.
			*/
			Operand thisOperand;

		};

		namespace {

			static Definition<EqualsOperation> const theEqualsDefinition;

		}

	}

}

	#include "om/operations/equals_operation.cpp"

#endif
