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

\defgroup om__operation__substitute_operation__ substitute
	\ingroup om__operation__
	\brief
		Applies a \ref om__lexicon__ to an \ref om__expression__ resulting in recursive \ref om__operator__ replacement, without using definitions from the enclosing scope.
	\par Input
		<tt>{lexicon} {expression}</tt>
	\par Output
		<tt>{lexicon} {evaluation}</tt>
	\par Examples
		<table>
			<tr><td><tt><b>substitute {A{1}} {A}</b></tt></td></tr>
			<tr><td><tt><em>{A{1}}{1}</em></tt></td></tr>
		</table>
		<table>
			<tr><td><tt><b>substitute {A{1}} {do{A}}</b></tt></td></tr>
			<tr><td><tt><em>{A{1}}{do{A}}</em></tt></td></tr>
		</table>
	\par Implementation
		Om::Language::Operation::SubstituteOperation

	Looking up an \ref om__operator__ in the \ref om__lexicon__ has the following possible outcomes:
	-	The \ref om__operator__ not found:
		-	The default (empty \ref om__operator__ mapping), if any, is used.
	-	The \ref om__operator__ is found, but has no mapping:
		-	The \ref om__operator__ is considered undefined, and no further checking is done.
	-	The \ref om__operator__ is found, and has an \ref om__operand__ mapping:
		-	The \ref om__operator__ is replaced with the \ref om__operand__ \ref om__program__.
*/

#ifndef Om_Language_Operation_SubstituteOperation_

	#define Om_Language_Operation_SubstituteOperation_ \
	Om::Language::Operation::SubstituteOperation

	#include "om/language/operation/default_incomplete_operation.hpp"
	#include "om/language/operation/translate_operation.hpp"
	#include "om/language/system.hpp"

	#define Om_Language_Operation_SubstituteOperation_GetName_() \
	"substitute"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::SubstituteOperation

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

}

	#include "om/language/operation/substitute_operation.cpp"

#endif
