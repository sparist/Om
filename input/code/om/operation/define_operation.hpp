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

#ifndef Om_Operation_DefineOperation_

	#define Om_Operation_DefineOperation_ \
	Om::Operation::DefineOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_DefineOperation_GetName_() \
	"define"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::DefineOperation

		/*!
		\brief
			The \ref om__operations__define_operation__ operation implementation.
		*/
		class DefineOperation :
		public DefaultIncompleteOperation<DefineOperation>
		{

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

	#include "om/operation/define_operation.cpp"

#endif
