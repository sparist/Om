/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup back_pull_character_operation characters->
	\ingroup operations
	\brief
		Pops the last character, quoted.
	\par Implementation
		Om#Operations#BackPullCharacterOperation
*/
#if !defined( Om_Operations_BackPullCharacterOperation_ )
	#define Om_Operations_BackPullCharacterOperation_ \
	Om::Operations::BackPullCharacterOperation

	#include "om/definition.hpp"

	#define Om_Operations_BackPullCharacterOperation_GetName_() "characters->"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::BackPullCharacterOperation
		/*!
		\brief
			The \ref back_pull_character_operation Operation implementation.
		*/
		struct BackPullCharacterOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );

			//! The callback for PullOperation.
			template< typename TheQueue >
			static void Pull( Operator &, TheQueue & );
		};

		namespace
		{
			static Definition<
				BackPullCharacterOperation
			> const theBackPullCharacterDefinition;
		}
	}
}

	#include "om/operations/back_pull_character_operation.cpp"
#endif
