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

\defgroup om__operation__environment_operation__ environment
	\ingroup om__operation__
	\brief
		Produces the \ref om__lexicon__ for the current environment.
	\par Details
		An environment is used by the evaluator for \ref om__operator__ resolution. An environment contains a \ref om__lexicon__ list, and each \ref om__operator__ is resolved by an environment as follows:
		-	Each \ref om__lexicon__ is checked for an explicit mapping for the \ref om__operator__, starting with the last, until one is found.
		-	If no explicit mapping is found, each \ref om__lexicon__ is checked for a default mapping (i.e. the mapping for the empty \ref om__operator__), starting with the last, until one is found.
		-	If no default mapping is found, the \ref om__operator__ is unresolved.
	\par Implementation
		Om::Language::Operation::EnvironmentOperation
*/

#ifndef Om_Language_Operation_EnvironmentOperation_

	#define Om_Language_Operation_EnvironmentOperation_ \
	Om::Language::Operation::EnvironmentOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_EnvironmentOperation_GetName_() \
	"environment"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::EnvironmentOperation

			/*!
			\brief
				The \ref om__operation__system_operation__ operation implementation.
			*/
			class EnvironmentOperation {

			public: // MARK: public (static)

				static char const * GetName();

				static void Give(Evaluation &);

			};

			namespace {

				static System::Definition<EnvironmentOperation> const theEnvironmentDefinition;

			}

		}

	}

}

	#include "om/language/operation/environment_operation.cpp"

#endif
