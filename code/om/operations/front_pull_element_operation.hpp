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

#ifndef Om_Operations_FrontPullElementOperation_

	#define Om_Operations_FrontPullElementOperation_ \
	Om::Operations::FrontPullElementOperation

	#include "om/definition.hpp"

	#define Om_Operations_FrontPullElementOperation_GetName_() \
	"<-elements"

namespace Om {

	//! \cond
	class Literal;
	//! \endcond

	namespace Operations {

		// MARK: - Om::Operations::FrontPullElementOperation

		/*!
		\brief
			The \ref om__operations__front_pull_element_operation__ operation implementation.
		*/
		class FrontPullElementOperation {

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

			static Definition<FrontPullElementOperation> const theFrontPullElementDefinition;

		}

	}

}

	#include "om/operations/front_pull_element_operation.cpp"

#endif
