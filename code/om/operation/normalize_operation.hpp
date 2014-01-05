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

\defgroup om__operation__normalize_operation__ normalize
	\ingroup om__operation__
	\brief
		Performs a Unicode compatibility normalization (<a href="http://unicode.org/reports/tr15/">NFKD</a>) on the contents of the \ref om__operand__.
	\par Implementation
		Om::Operation::NormalizeOperation
*/

#ifndef Om_Operation_NormalizeOperation_

	#define Om_Operation_NormalizeOperation_ \
	Om::Operation::NormalizeOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_NormalizeOperation_GetName_() \
	"normalize"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::NormalizeOperation

		/*!
		\brief
			The \ref om__operation__normalize_operation__ operation implementation.
		*/
		class NormalizeOperation:
		public DefaultIncompleteOperation<NormalizeOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheNormalizeOperation>
			static void GiveElements(
				TheNormalizeOperation &,
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

			static System::Definition<NormalizeOperation> const theNormalizeDefinition;

		}

	}

}

	#include "om/operation/normalize_operation.cpp"

#endif
