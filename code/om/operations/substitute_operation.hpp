/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup substitute_operation substitute
	\ingroup operations
	\brief
		Applies a \ref lexicon to an \ref expression resulting in recursive
		\ref operator replacement, without using definitions from the enclosing
		scope.
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
		Om#Operations#SubstituteOperation

	Looking up an \ref operator in the \ref lexicon has the following possible
	outcomes:
	-	The \ref operator not found:
		-	The default (empty \ref operator mapping), if any, is used.
	-	The \ref operator is found, but has no mapping:
		-	The \ref operator is considered "undefined" and no further checking
			is done.
	-	The \ref operator is found, and has an \ref operand mapping:
		-	The \ref operator is replaced with the \ref operand
			\ref programs "Program".
*/
#if !defined( Om_Operations_SubstituteOperation_ )
	#define Om_Operations_SubstituteOperation_ \
	Om::Operations::SubstituteOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"
	#include "om/operations/translate_operation.hpp"

	#define Om_Operations_SubstituteOperation_GetName_() "substitute"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::SubstituteOperation
		/*!
		\brief
			The \ref substitute_operation Operation implementation.
		*/
		struct SubstituteOperation
		:
		TranslateOperation< SubstituteOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

		public: // MARK: public (non-static)

			template< typename TheQueue >
			void Translate(
				Translator const &,
				TheQueue &,
				Expression &
			) const;
		};

		namespace
		{
			static Definition<
				SubstituteOperation
			> const theSubstituteDefinition;
		}
	}
}

	#include "om/operations/substitute_operation.cpp"
#endif
