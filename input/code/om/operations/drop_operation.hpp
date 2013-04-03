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

#ifndef Om_Operations_DropOperation_

	#define Om_Operations_DropOperation_ \
	Om::Operations::DropOperation

	#include "om/default_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operations_DropOperation_GetName_() \
	"drop"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::DropOperation

		/*!
		\brief
			The \ref om__operations__drop_operation__ operation implementation.
		*/
		class DropOperation:
		public DefaultOperation<DropOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheDropOperation>
			static void GiveElements(
				TheDropOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

			virtual bool ReadQuotedElements(
				Evaluation &,
				Parser &
			);

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

			static System::Definition<DropOperation> const theDropDefinition;

		}

	}

}

	#include "om/operations/drop_operation.cpp"

#endif
