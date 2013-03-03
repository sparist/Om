/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_DefineOperation_ )

	#define Om_Operations_DefineOperation_ \
	Om::Operations::DefineOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_DefineOperation_GetName_() \
	"define"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::DefineOperation
		/*!
		\brief
			The \ref om__operations__define_operation__ operation implementation.
		*/
		class DefineOperation:
		public DefaultOperation< DefineOperation > {
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheDefineOperation >
			static void GiveElements(
				TheDefineOperation &,
				Queue &
			);

		public: // MARK: public (non-static)

			DefineOperation();

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

		private: // MARK: private (non-static)

			boost::optional< Lexicon > thisLexicon;

		};

		namespace {

			static Definition< DefineOperation > const theDefineDefinition;

		}

	}

}

	#include "om/operations/define_operation.cpp"

#endif
