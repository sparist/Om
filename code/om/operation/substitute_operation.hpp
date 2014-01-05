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
		-	<tt>substitute{A{1}}{A}</tt>
			<blockquote><tt>{A{1}}{1}</tt></blockquote>
		-	<tt>substitute{A{1}}{do{A}}</tt>
			<blockquote><tt>{A{1}}{do{A}}</tt></blockquote>
	\par Implementation
		Om::Operation::SubstituteOperation

	Looking up an \ref om__operator__ in the \ref om__lexicon__ has the following possible outcomes:
	-	The \ref om__operator__ not found:
		-	The default (empty \ref om__operator__ mapping), if any, is used.
	-	The \ref om__operator__ is found, but has no mapping:
		-	The \ref om__operator__ is considered undefined, and no further checking is done.
	-	The \ref om__operator__ is found, and has an \ref om__operand__ mapping:
		-	The \ref om__operator__ is replaced with the \ref om__operand__ \ref om__program__.
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
