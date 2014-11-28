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

\defgroup om__operation__find_operation__ find
	\ingroup om__operation__
	\brief
		Finds the \ref om__operator__, and its \ref om__operand__ mapping (if any), in a \ref om__lexicon__.
	\par Input
		<tt>{operator} {lexicon}</tt>
	\par Output
		-	If the \ref om__operator__ is found:
			-	If an \ref om__operand__ is mapped to the \ref om__operator__ "Operator":
				<blockquote><tt>{lexicon}{operator{operand}}</tt></blockquote>
			-	Else:
				<blockquote><tt>{lexicon}{operator{}}</tt></blockquote>
		-	Else:
				<blockquote><tt>{lexicon}{}</tt></blockquote>
	\par Implementation
		Om::Language::Operation::FindOperation
*/

#ifndef Om_Language_Operation_FindOperation_

	#define Om_Language_Operation_FindOperation_ \
	Om::Language::Operation::FindOperation

	#include "om/language/operation/default_incomplete_operation.hpp"
	#include "om/language/system.hpp"

	#define Om_Language_Operation_FindOperation_GetName_() \
	"find"

namespace Om {

	namespace Language {

		//! \cond
		class Lexicon;
		//! \endcond

		namespace Operation {

			// MARK: - Om::Language::Operation::FindOperation

			/*!
			\brief
				The \ref om__operation__find_operation__ operation implementation.
			*/
			class FindOperation:
			public DefaultIncompleteOperation<FindOperation> {

			public: // MARK: public (static)

				static char const * GetName();

				template <typename TheFindOperation>
				static void GiveElements(
					TheFindOperation &,
					Consumer &
				);

			public: // MARK: public (non-static)

				FindOperation();

				template <typename TheOperand>
				bool TakeOperand(
					Evaluation &,
					TheOperand &
				);

				template <typename TheProducer>
				bool TakeQuotedProducer(
					Evaluation &,
					TheProducer &
				);

			private: // MARK: private (non-static)

				/*!
				\brief
					The Operator to find.
				*/
				boost::optional<Operator> thisOperator;

			};

			namespace {

				static System::Definition<FindOperation> const theFindDefinition;

			}

		}

	}

}

	#include "om/language/operation/find_operation.cpp"

#endif
