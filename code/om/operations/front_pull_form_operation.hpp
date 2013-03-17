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

#ifndef Om_Operations_FrontPullFormOperation_

	#define Om_Operations_FrontPullFormOperation_ \
	Om::Operations::FrontPullFormOperation

	#include "om/definition.hpp"

	#define Om_Operations_FrontPullFormOperation_GetName_() \
	"<-forms"

namespace Om {

	//! \cond
	class Expression;
	//! \endcond

	namespace Operations {

		// MARK: - Om::Operations::FrontPullFormOperation

		/*!
		\brief
			The \ref om__operations__front_pull_form_operation__ operation implementation.
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

			static Definition<FrontPullFormOperation> const theFrontPullFormDefinition;

		}

	}

}

	#include "om/operations/front_pull_form_operation.cpp"

#endif
