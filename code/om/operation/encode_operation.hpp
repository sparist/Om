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

\defgroup om__operation__encode_operation__ encode
	\ingroup om__operation__
	\brief
		Encodes all special characters (non-recursively).
	\par Input
		<tt>{program}</tt>
	\par Output
		<tt>{operator}</tt>
	\par Implementation
		Om::Operation::EncodeOperation
*/

#ifndef Om_Operation_EncodeOperation_

	#define Om_Operation_EncodeOperation_ \
	Om::Operation::EncodeOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_EncodeOperation_GetName_() \
	"encode"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::EncodeOperation

		/*!
		\brief
			The \ref om__operation__encode_operation__ operation implementation.
		*/
		class EncodeOperation:
		public DefaultIncompleteOperation<EncodeOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheEncodeOperation>
			static void GiveElements(
				TheEncodeOperation &,
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

			static System::Definition<EncodeOperation> const theEncodeDefinition;

		}

	}

}

	#include "om/operation/encode_operation.cpp"

#endif
