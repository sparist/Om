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

#ifndef Om_Operations_BackPullPairOperation_

	#define Om_Operations_BackPullPairOperation_ \
	Om::Operations::BackPullPairOperation

	#include "om/definition.hpp"

	#define Om_Operations_BackPullPairOperation_GetName_() \
	"pairs->"

namespace Om {

	//! \cond

	class Lexicon;

	//! \endcond

	namespace Operations {

		// MARK: - Om::Operations::BackPullPairOperation

		/*!
		\brief
			The \ref om__operations__back_pull_pair_operation__ operation implementation.
		*/
		class BackPullPairOperation {

		public: // MARK: public (static)

			static char const * GetName();

			static void Give(Evaluation &);

			/*!
			\brief
				The callback for PullOperation.
			*/
			template <typename TheQueue>
			static void Pull(
				Lexicon &,
				TheQueue &
			);

		};

		namespace {

			static Definition<BackPullPairOperation> const theBackPullPairDefinition;

		}

	}

}

	#include "om/operations/back_pull_pair_operation.cpp"

#endif
