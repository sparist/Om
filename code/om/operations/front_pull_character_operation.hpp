/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
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

\defgroup front_pull_character_operation <-characters
	\ingroup operations
	\brief
		Pops the first character, quoted.
	\par Implementation
		Om#Operations#FrontPullCharacterOperation
*/
#if !defined( Om_Operations_FrontPullCharacterOperation_ )
	#define Om_Operations_FrontPullCharacterOperation_ \
	Om::Operations::FrontPullCharacterOperation

	#include "om/definition.hpp"

	#define Om_Operations_FrontPullCharacterOperation_GetName_() "<-characters"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::FrontPullCharacterOperation
		/*!
		\brief
			The \ref front_pull_character_operation Operation implementation.
		*/
		struct FrontPullCharacterOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheEvaluandTaker >
			static void Give( TheEvaluandTaker & );

			//! The callback for PullOperation.
			template< typename TheQueue >
			static void Pull( Operator &, TheQueue & );
		};

		namespace
		{
			static Definition<
				FrontPullCharacterOperation
			> const theFrontPullCharacterDefinition;
		}
	}
}

	#include "om/operations/front_pull_character_operation.cpp"
#endif
