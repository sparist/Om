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
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup environment_operation environment
	\ingroup operations
	\brief
		Produces the \ref lexicon for the current environment.
	\par Details
		An environment is used by the evaluator for \ref operator resolution.
		An environment contains a \ref lexicon list, and each \ref operator
		is resolved by an environment as follows:
		-	Each \ref lexicon is checked for an explicit mapping for the
			\ref operator, starting with the last, until one is found.
		-	If no explicit mapping is found, each \ref lexicon is checked for
			a "default mapping" (i.e. the mapping for the empty \ref operator),
			starting with the last, until one is found.
		-	If no default mapping is found, the \ref operator is unresolved.
	\par Implementation
		Om#Operations#EnvironmentOperation
*/
#if !defined( Om_Operations_EnvironmentOperation_ )
	#define Om_Operations_EnvironmentOperation_ \
	Om::Operations::EnvironmentOperation

	#include "om/definition.hpp"

	#define Om_Operations_EnvironmentOperation_GetName_() "environment"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::EnvironmentOperation
		/*!
		\brief
			The \ref system_operation Operation implementation.
		*/
		struct EnvironmentOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );
		};

		namespace
		{
			static Definition<
				EnvironmentOperation
			> const theEnvironmentDefinition;
		}
	}
}

	#include "om/operations/environment_operation.cpp"
#endif
