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

#ifndef Om_Operations_TranslateOperation_

	#define Om_Operations_TranslateOperation_ \
	Om::Operations::TranslateOperation

	#include "om/lexicon.hpp"
	#include "om/operations/default_incomplete_operation.hpp"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::TranslateOperation

		/*!
		\brief
			An \ref om__operations__ "Operation" that applies each Translator to a Program.
		*/
		template <typename ThisImplementation>
		class TranslateOperation :
		public DefaultIncompleteOperation<ThisImplementation>
		{

		public: // MARK: public (static)

			template <typename TheTranslateOperation>
			static void GiveElements(
				TheTranslateOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

			virtual ~TranslateOperation() = 0;

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

		protected: // MARK: protected (non-static)

			TranslateOperation();

			boost::optional<Lexicon> thisLexicon;

		};

	}

}

	#include "om/operations/translate_operation.cpp"

#endif
