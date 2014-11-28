/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb

\defgroup om__operation__normalize_operation__ normalize
	\ingroup om__operation__
	\brief
		Performs a Unicode compatibility normalization (<a href="http://unicode.org/reports/tr15/">NFKD</a>) on the contents of the \ref om__operand__.
	\par Implementation
		Om::Language::Operation::NormalizeOperation
*/

#ifndef Om_Language_Operation_NormalizeOperation_

	#define Om_Language_Operation_NormalizeOperation_ \
	Om::Language::Operation::NormalizeOperation

	#include "om/language/operation/default_incomplete_operation.hpp"
	#include "om/language/system.hpp"

	#define Om_Language_Operation_NormalizeOperation_GetName_() \
	"normalize"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::NormalizeOperation

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

}

	#include "om/language/operation/normalize_operation.cpp"

#endif
