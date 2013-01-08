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

\defgroup system_operation system
	\ingroup operations
	\brief
		Produces the system \ref lexicon.
	\par Details
		The system \ref lexicon contains each \ref operator defined by the
		system.  Each \ref operator is without an \ref operand mapping to
		indicate that the "native" system operation is to be used.
	\par Implementation
		Om::Operations::SystemOperation
*/
#if !defined( Om_Operations_SystemOperation_ )
	#define Om_Operations_SystemOperation_ Om::Operations::SystemOperation

	#include "om/definition.hpp"

	#define Om_Operations_SystemOperation_GetName_() "system"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::SystemOperation
		/*!
		\brief
			The \ref system_operation Operation implementation.
		*/
		struct SystemOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );
		};

		namespace
		{
			static Definition< SystemOperation > const theSystemDefinition;
		}
	}
}

	#include "om/operations/system_operation.cpp"
#endif
