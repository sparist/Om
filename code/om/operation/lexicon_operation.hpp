/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup om__operation__lexicon_operation__ lexicon
	\ingroup om__operation__
	\brief
		Normalizes the \ref om__operand__ as a quoted \ref om__lexicon__.
	\par Implementation
		Om::Operation::LexiconOperation

	A \ref om__program__ is interpreted as a \ref om__lexicon__ as follows:
	-	Each \ref om__operator__ is a key, indexing to the \ref om__operand__ to its right.
	-	In the case of duplicate \ref om__operator__ "Operators", the prior is removed.
	-	An \ref om__operator__ without an \ref om__operand__ indicates that the system mapping for the \ref om__operator__ is to be explicitly included.
	-	An \ref om__operand__ without an \ref om__operator__ indicates the default mapping, which is used for any \ref om__operator__ not found in the \ref om__lexicon__.
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
