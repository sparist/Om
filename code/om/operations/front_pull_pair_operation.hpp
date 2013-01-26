/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_FrontPullPairOperation_ )

	#define Om_Operations_FrontPullPairOperation_ \
	Om::Operations::FrontPullPairOperation

	#include "om/definition.hpp"

	#define Om_Operations_FrontPullPairOperation_GetName_() \
	"<-pairs"

namespace Om
{
	//! \cond
	struct Lexicon;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::FrontPullPairOperation
		/*!
		\brief
			The \ref front_pull_pair_operation Operation implementation.
		*/
		struct FrontPullPairOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );

			//! The callback for PullOperation.
			template< typename TheQueue >
			static void Pull(
				Lexicon &,
				TheQueue &
			);
		};

		namespace
		{
			static Definition< FrontPullPairOperation > const theFrontPullPairDefinition;
		}
	}
}

	#include "om/operations/front_pull_pair_operation.cpp"

#endif
