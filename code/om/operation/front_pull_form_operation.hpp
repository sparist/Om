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

\defgroup om__operation__front_pull_form_operation__ <-[forms]
	\ingroup om__operation__
	\brief
		Pops the first form (a non-empty list of zero or one \ref om__operator__ "Operator(s)", followed by zero or more \ref om__operand__ "Operands"), quoted.
	\par Implementation
		Om::Operation::FrontPullFormOperation
*/

#ifndef Om_Operation_FrontPullFormOperation_

	#define Om_Operation_FrontPullFormOperation_ \
	Om::Operation::FrontPullFormOperation

	#include "om/system.hpp"

	#define Om_Operation_FrontPullFormOperation_GetName_() \
	"<-[forms]"

namespace Om {

	//! \cond
	class Expression;
	//! \endcond

	namespace Operation {

		// MARK: - Om::Operation::FrontPullFormOperation

		/*!
		\brief
			The \ref om__operation__front_pull_form_operation__ operation implementation.
		*/
		class FrontPullFormOperation {

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

			static System::Definition<FrontPullFormOperation> const theFrontPullFormDefinition;

		}

	}

}

	#include "om/operation/front_pull_form_operation.cpp"

#endif
