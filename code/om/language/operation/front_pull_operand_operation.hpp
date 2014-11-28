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

\defgroup om__operation__front_pull_operand_operation__ <-[operand...]
	\ingroup om__operation__
	\brief
		Pops the first \ref om__operand__ (if any), quoted.
	\par Input
		<tt>{{A} B}</tt>
	\par Output
		<tt>{{A}} { B}</tt>
	\par Implementation
		Om::Language::Operation::FrontPullOperandOperation
*/

#ifndef Om_Language_Operation_FrontPullOperandOperation_

	#define Om_Language_Operation_FrontPullOperandOperation_ \
	Om::Language::Operation::FrontPullOperandOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_FrontPullOperandOperation_GetName_() \
	"<-[operand...]"

namespace Om {

	namespace Language {

		//! \cond
		class Literal;
		//! \endcond

		namespace Operation {

			// MARK: - Om::Language::Operation::FrontPullOperandOperation

			/*!
			\brief
				The \ref om__operation__front_pull_operand_operation__ operation implementation.
			*/
			class FrontPullOperandOperation {

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

				static System::Definition<FrontPullOperandOperation> const theFrontPullOperandDefinition;

			}

		}

	}

}

	#include "om/language/operation/front_pull_operand_operation.cpp"

#endif
