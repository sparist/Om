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

#ifndef Om_Operations_CopyOperation_

	#define Om_Operations_CopyOperation_ \
	Om::Operations::CopyOperation

	#include "om/default_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operations_CopyOperation_GetName_() \
	"copy"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::CopyOperation

		/*!
		\brief
			The \ref om__operations__copy_operation__ operation implementation.
		*/
		class CopyOperation:
		public DefaultOperation<CopyOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheCopyOperation>
			static void GiveElements(
				TheCopyOperation &,
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

			static System::Definition<CopyOperation> const theCopyDefinition;

		}

	}

}

	#include "om/operations/copy_operation.cpp"

#endif
