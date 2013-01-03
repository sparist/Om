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

\defgroup separator_operation separator
	\ingroup operations
	\brief
		Normalizes the \ref operand as a quoted \ref separator.
	\par Implementation
		Om#Operations#SeparatorOperation
*/
#if !defined( Om_Operations_SeparatorOperation_ )
	#define Om_Operations_SeparatorOperation_ Om::Operations::SeparatorOperation

	#include "om/definition.hpp"
	#include "om/operations/program_operation.hpp"

namespace Om
{
	namespace Operations
	{
		//! The \ref separator_operation Operation implementation.
		typedef ProgramOperation< Separator > SeparatorOperation;

		namespace
		{
			static Definition<
				SeparatorOperation
			> const theSeparatorDefinition;
		}
	}
}

#endif
