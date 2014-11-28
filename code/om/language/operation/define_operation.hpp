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

\defgroup om__operation__define_operation__ define
	\ingroup om__operation__
	\brief
		\ref om__operation__evaluate_operation__ "Evaluates" and \ref om__operation__dequote_operation__ "dequotes" an \ref om__expression__ with an environment that contains additionally-defined \ref om__operator__ "Operators".
	\par Input
		A \ref om__lexicon__, containing the additional operator definition(s), and an \ref om__expression__ to evaluate.
	\par Output
		The evaluation of the \ref om__expression__ under the temporarily extended environment, \ref om__operation__dequote_operation__ "dequoted".
	\par Implementation
		Om::Language::Operation::DefineOperation
*/

#ifndef Om_Language_Operation_DefineOperation_

	#define Om_Language_Operation_DefineOperation_ \
	Om::Language::Operation::DefineOperation

	#include "om/language/operation/default_incomplete_operation.hpp"
	#include "om/language/system.hpp"

	#define Om_Language_Operation_DefineOperation_GetName_() \
	"define"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::DefineOperation

			/*!
			\brief
				The \ref om__operation__define_operation__ operation implementation.
			*/
			class DefineOperation:
			public DefaultIncompleteOperation<DefineOperation> {

			public: // MARK: public (static)

				static char const * GetName();

				template <typename TheDefineOperation>
				static void GiveElements(
					TheDefineOperation &,
					Consumer &
				);

			public: // MARK: public (non-static)

				DefineOperation();

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

				boost::optional<Lexicon> thisLexicon;

			};

			namespace {

				static System::Definition<DefineOperation> const theDefineDefinition;

			}

		}

	}

}

	#include "om/language/operation/define_operation.cpp"

#endif
