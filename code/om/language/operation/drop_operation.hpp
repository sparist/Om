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

\defgroup om__operation__drop_operation__ drop
	\ingroup om__operation__
	\brief
		Deletes an \ref om__operand__.
	\par Input
		<tt>{A} ...</tt>
	\par Output
		<tt>...</tt>
	\par Implementation
		Om::Language::Operation::DropOperation
*/

#ifndef Om_Language_Operation_DropOperation_

	#define Om_Language_Operation_DropOperation_ \
	Om::Language::Operation::DropOperation

	#include "om/language/operation/default_incomplete_operation.hpp"
	#include "om/language/system.hpp"

	#define Om_Language_Operation_DropOperation_GetName_() \
	"drop"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::DropOperation

			/*!
			\brief
				The \ref om__operation__drop_operation__ operation implementation.
			*/
			class DropOperation:
			public DefaultIncompleteOperation<DropOperation> {

			public: // MARK: public (static)

				static char const * GetName();

				template <typename TheDropOperation>
				static void GiveElements(
					TheDropOperation &,
					Consumer &
				);

			public: // MARK: public (non-static)

				virtual bool ParseQuotedElements(
					Evaluation &,
					Reader &
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

}

	#include "om/language/operation/drop_operation.cpp"

#endif
