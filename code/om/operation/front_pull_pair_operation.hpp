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

\defgroup om__operation__front_pull_pair_operation__ <-[pairs]
	\ingroup om__operation__
	\brief
		Pops the first pair (a non-empty list of zero or one \ref om__operator__ "Operator(s)", followed by zero or one \ref om__operand__ "Operand(s)"), quoted.
	\par Implementation
		Om::Operation::FrontPullPairOperation
*/

#ifndef Om_Operation_FrontPullPairOperation_

	#define Om_Operation_FrontPullPairOperation_ \
	Om::Operation::FrontPullPairOperation

	#include "om/system.hpp"

	#define Om_Operation_FrontPullPairOperation_GetName_() \
	"<-[pairs]"

namespace Om {

	//! \cond
	class Lexicon;
	//! \endcond

	namespace Operation {

		// MARK: - Om::Operation::FrontPullPairOperation

		/*!
		\brief
			The \ref om__operation__front_pull_pair_operation__ operation implementation.
		*/
		class FrontPullPairOperation {

		public: // MARK: public (static)

			static char const * GetName();

			static void Give(Evaluation &);

			/*!
			\brief
				The callback for PullOperation.
			*/
			template <typename TheConsumer>
			static void Pull(
				Lexicon &,
				TheConsumer &
			);

		};

		namespace {

			static System::Definition<FrontPullPairOperation> const theFrontPullPairDefinition;

		}

	}

}

	#include "om/operation/front_pull_pair_operation.cpp"

#endif
