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

\defgroup om__operation__back_pull_form_operation__ [forms]->
	\ingroup om__operation__
	\brief
		Pops the last form (a non-empty list of zero or one \ref om__operator__ "Operator(s)", followed by zero or more \ref om__operand__ "Operands"), quoted.
	\par Implementation
		Om::Language::Operation::BackPullFormOperation
*/

#ifndef Om_Language_Operation_BackPullFormOperation_

	#define Om_Language_Operation_BackPullFormOperation_ \
	Om::Language::Operation::BackPullFormOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_BackPullFormOperation_GetName_() \
	"[forms]->"

namespace Om {

	namespace Language {

		//! \cond
		class Expression;
		//! \endcond

		namespace Operation {

			// MARK: - Om::Language::Operation::BackPullFormOperation

			/*!
			\brief
				The \ref om__operation__back_pull_form_operation__ operation implementation.
			*/
			class BackPullFormOperation {

			public: // MARK: public (static)

				static char const * GetName();

				static void Give(Evaluation &);

				/*!
				\brief
					The callback for PullOperation.
				*/
				template <typename TheConsumer>
				static void Pull(
					Expression &,
					TheConsumer &
				);

			};

			namespace {

				static System::Definition<BackPullFormOperation> const theBackPullFormDefinition;

			}

		}

	}

}

	#include "om/language/operation/back_pull_form_operation.cpp"

#endif
