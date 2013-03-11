/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operations_BackPullOperatorOperation_

	#define Om_Operations_BackPullOperatorOperation_ \
	Om::Operations::BackPullOperatorOperation

	#include "om/definition.hpp"

	#define Om_Operations_BackPullOperatorOperation_GetName_() \
	"elements->operator"

namespace Om {

	//! \cond
	class Literal;
	//! \endcond

	namespace Operations {

		// MARK: - Om::Operations::BackPullOperatorOperation

		/*!
		\brief
			The \ref om__operations__back_pull_operator_operation__ operation implementation.
		*/
		class BackPullOperatorOperation {

		public: // MARK: public (static)

			static char const * GetName();

			static void Give(Evaluation &);

			/*!
			\brief
				The callback for PullOperation.
			*/
			template <typename TheQueue>
			static void Pull(
				Literal &,
				TheQueue &
			);

		};

		namespace {

			static Definition<BackPullOperatorOperation> const theBackPullOperatorDefinition;

		}

	}

}

	#include "om/operations/back_pull_operator_operation.cpp"

#endif
