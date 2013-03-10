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

#ifndef Om_Operations_FrontPullTermOperation_

	#define Om_Operations_FrontPullTermOperation_ \
	Om::Operations::FrontPullTermOperation

	#include "om/definition.hpp"

	#define Om_Operations_FrontPullTermOperation_GetName_() \
	"<-terms"

namespace Om {

	//! \cond
	class Expression;
	//! \endcond

	namespace Operations {

		// MARK: - Om::Operations::FrontPullTermOperation
		/*!
		\brief
			The \ref om__operations__front_pull_term_operation__ operation implementation.
		*/
		class FrontPullTermOperation {
		public: // MARK: public (static)

			static char const * GetName();

			static void Give(Evaluation &);

			/*!
			\brief
				The callback for PullOperation.
			*/
			template <typename TheQueue>
			static void Pull(
				Expression &,
				TheQueue &
			);

		};

		namespace {

			static Definition<FrontPullTermOperation> const theFrontPullTermDefinition;

		}

	}

}

	#include "om/operations/front_pull_term_operation.cpp"

#endif
