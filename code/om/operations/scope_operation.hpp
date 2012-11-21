/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup scope_operation scope
	\ingroup operations
	\brief
		Applies a \ref lexicon to an \ref expression resulting in recursive
		\ref operator replacement, using definitions from the enclosing scope.
	\par Input
		<tt>{lexicon} {expression}</tt>
	\par Output
		<tt>{lexicon} {evaluation}</tt>
	\par Examples
		-	<tt>scope{A{1}}{do{A}}</tt>
			<blockquote><tt>{A{1}}{1}</tt></blockquote>
	\par Implementation
		Om#Operations#ScopeOperation
	\see
		substitute_operation

	Looking up an \ref operator in the \ref lexicon has the following possible
	outcomes:
	-	The \ref operator not found:
		-	The enclosing scope is checked.
		-	If not found, the default (empty \ref operator mapping) in the
			\ref lexicon is checked.
		-	If not found, the default (empty \ref operator mapping) in the
			enclosing scope is checked.
	-	The \ref operator is found, but has no mapping:
		-	The \ref operator is considered "undefined" and no further checking
			is done.
	-	The \ref operator is found, and has an \ref operand mapping:
		-	The \ref operator is replaced with the \ref operand
			\ref programs "Program".
*/
#if !defined( Om_Operations_ScopeOperation_ )
	#define Om_Operations_ScopeOperation_ Om::Operations::ScopeOperation

	#include "om/definition.hpp"
	#include "om/default_evaluand.hpp"
	#include "om/operations/translate_operation.hpp"

	#define Om_Operations_ScopeOperation_GetName_() "scope"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::ScopeOperation
		/*!
		\brief
			The \ref scope_operation Operation implementation.
		*/
		struct ScopeOperation
		:
		TranslateOperation< ScopeOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

		public: // MARK: public (non-static)

			template< typename TheQueue >
			void Translate( Evaluator const &, TheQueue &, Expression & ) const;
		};

		namespace
		{
			static Definition< ScopeOperation > const theScopeDefinition;
		}
	}
}

	#include "om/operations/scope_operation.cpp"
#endif
