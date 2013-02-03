/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_TranslateOperation_ )

	#define Om_Operations_TranslateOperation_ \
	Om::Operations::TranslateOperation

	#include "om/default_operation.hpp"
	#include "om/lexicon.hpp"

namespace Om {
	namespace Operations {

		// MARK: - Om::Operations::TranslateOperation
		/*!
		\brief
			An Operation that applies each Translator to a Program.
		*/
		template< typename ThisImplementation >
		class TranslateOperation:
		public DefaultOperation< ThisImplementation > {
		public: // MARK: public (static)

			template< typename TheTranslateOperation >
			static void GiveElements(
				TheTranslateOperation &,
				Queue &
			);

		public: // MARK: public (non-static)

			virtual ~TranslateOperation() = 0;

			template< typename TheOperand >
			bool TakeOperand(
				Evaluation &,
				TheOperand &
			);

			template< typename TheQueue >
			bool TakeQuotedQueue(
				Evaluation &,
				TheQueue &
			);

		protected: // MARK: protected (non-static)

			TranslateOperation();

			boost::optional< Lexicon > thisLexicon;
		};
	}
}

	#include "om/operations/translate_operation.cpp"

#endif
