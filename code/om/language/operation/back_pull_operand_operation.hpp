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

\defgroup om__operation__back_pull_operand_operation__ [...operand]->
	\ingroup om__operation__
	\brief
		Pops the last \ref om__operand__ (if any), quoted.
	\par Input
		<tt>{A {B}}</tt>
	\par Output
		<tt>{{B}} {A }</tt>
	\par Implementation
		Om::Language::Operation::BackPullOperandOperation
*/

#ifndef Om_Language_Operation_BackPullOperandOperation_

	#define Om_Language_Operation_BackPullOperandOperation_ \
	Om::Language::Operation::BackPullOperandOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_BackPullOperandOperation_GetName_() \
	"[...operand]->"

namespace Om {

	namespace Language {

		//! \cond
		class Literal;
		//! \endcond

		namespace Operation {

			// MARK: - Om::Language::Operation::BackPullOperandOperation

			/*!
			\brief
				The \ref om__operation__back_pull_operand_operation__ operation implementation.
			*/
			class BackPullOperandOperation {

			public: // MARK: public (static)

				static char const * GetName();

				static void Give(Evaluation &);

				/*!
				\brief
					The callback for PullOperation.
				*/
				template <typename TheConsumer>
				static void Pull(
					Literal &,
					TheConsumer &
				);

			};

			namespace {

				static System::Definition<BackPullOperandOperation> const theBackPullOperandDefinition;

			}

		}

	}

}

	#include "om/language/operation/back_pull_operand_operation.cpp"

#endif
