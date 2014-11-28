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

\defgroup om__operation__skip_operation__ skip
	\ingroup om__operation__
	\brief
		Skips over an \ref om__operand__ and \ref om__operation__dequote_operation__ "dequotes".
	\par Input
		<tt>{expression} {A}</tt>
	\par Output
		<tt>{A} expression</tt>
	\par Implementation
		Om::Language::Operation::SkipOperation
*/

#ifndef Om_Language_Operation_SkipOperation_

	#define Om_Language_Operation_SkipOperation_ \
	Om::Language::Operation::SkipOperation

	#include "om/language/expression.hpp"
	#include "om/language/operation/default_incomplete_operation.hpp"
	#include "om/language/system.hpp"

	#define Om_Language_Operation_SkipOperation_GetName_() \
	"skip"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::SkipOperation

			/*!
			\brief
				The \ref om__operation__skip_operation__ operation implementation.
			*/
			class SkipOperation:
			public DefaultIncompleteOperation<SkipOperation> {

			public: // MARK: public (static)

				static char const * GetName();

				template <typename TheSkipOperation>
				static void GiveElements(
					TheSkipOperation &,
					Consumer &
				);

			public: // MARK: public (non-static)

				SkipOperation();

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

				/*!
				If an empty Expression is taken as the first Operand, the Operation is complete. Therefore, the empty Expression can be used to indicate that the first Operand has not yet been received.
				*/
				Expression thisExpression;

			};

			namespace {

				static System::Definition<SkipOperation> const theSkipDefinition;

			}

		}

	}

}

	#include "om/language/operation/skip_operation.cpp"

#endif
