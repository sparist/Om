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

#ifndef Om_Operation_SubstituteOperation_

	#define Om_Operation_SubstituteOperation_ \
	Om::Operation::SubstituteOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/operation/translate_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_SubstituteOperation_GetName_() \
	"substitute"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::SubstituteOperation

		/*!
		\brief
			The \ref om__operation__substitute_operation__ operation implementation.
		*/
		class SubstituteOperation:
		public TranslateOperation<SubstituteOperation> {

		public: // MARK: public (static)

			static char const * GetName();

		public: // MARK: public (non-static)

			template <typename TheProducer>
			void Translate(
				Translator const &,
				TheProducer &,
				Expression &
			) const;

		};

		namespace {

			static System::Definition<SubstituteOperation> const theSubstituteDefinition;

		}

	}

}

	#include "om/operation/substitute_operation.cpp"

#endif
