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

#ifndef Om_Operation_LexiconOperation_

	#define Om_Operation_LexiconOperation_ \
	Om::Operation::LexiconOperation

	#include "om/lexicon.hpp"
	#include "om/operation/program_operation.hpp"
	#include "om/system.hpp"

namespace Om {

	namespace Operation {

		/*!
		\brief
			The \ref om__operation__lexicon_operation__ operation implementation.
		*/
		typedef ProgramOperation<Lexicon> LexiconOperation;

		namespace {

			static System::Definition<LexiconOperation> const theLexiconDefinition;

		}

	}

}

#endif
