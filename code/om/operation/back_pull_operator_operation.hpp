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

\defgroup om__operation__back_pull_operator_operation__ [...operator]->
	\ingroup om__operation__
	\brief
		Pops the last \ref om__operator__ (if any), quoted.
	\par Input
		<tt>{A B}</tt>
	\par Output
		<tt>{B} {A }</tt>
	\par Implementation
		Om::Operation::BackPullOperatorOperation
*/

#ifndef Om_Operation_BackPullOperatorOperation_

	#define Om_Operation_BackPullOperatorOperation_ \
	Om::Operation::BackPullOperatorOperation

	#include "om/system.hpp"

	#define Om_Operation_BackPullOperatorOperation_GetName_() \
	"[...operator]->"

namespace Om {

	//! \cond
	class Literal;
	//! \endcond

	namespace Operation {

		// MARK: - Om::Operation::BackPullOperatorOperation

		/*!
		\brief
			The \ref om__operation__back_pull_operator_operation__ operation implementation.
		*/
		class BackPullOperatorOperation {

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

			static System::Definition<BackPullOperatorOperation> const theBackPullOperatorDefinition;

		}

	}

}

	#include "om/operation/back_pull_operator_operation.cpp"

#endif
