/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb

\defgroup om__operation__decode_operation__ decode
	\ingroup om__operation__
	\brief
		Decodes encoded characters (non-recursively).
	\par Input
		<tt>{operator}</tt>
	\par Output
		<tt>{literal}</tt>
	\par Implementation
		Om::Operation::DecodeOperation

	Decoding the output of \ref om__operation__encode_operation__ results in an \ref om__operand__ equivalent to the input of \ref om__operation__encode_operation__.
*/

#ifndef Om_Operation_DecodeOperation_

	#define Om_Operation_DecodeOperation_ \
	Om::Operation::DecodeOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_DecodeOperation_GetName_() \
	"decode"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::DecodeOperation

		/*!
		\brief
			The \ref om__operation__decode_operation__ operation implementation.
		*/
		class DecodeOperation:
		public DefaultIncompleteOperation<DecodeOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheDecodeOperation>
			static void GiveElements(
				TheDecodeOperation &,
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

			static System::Definition<DecodeOperation> const theDecodeDefinition;

		}

	}

}

	#include "om/operation/decode_operation.cpp"

#endif
