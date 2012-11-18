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

\defgroup lexicon_operation lexicon
	\ingroup operation
	\brief
		Normalizes the \ref operand as a quoted \ref lexicon.
	\par Implementation
		Om#Operations#LexiconOperation

	A program is interpreted as a lexicon as follows:
	-	Each \ref operator is a key, indexing to the \ref operand to its right.
	-	In the case of duplicate \ref operator "Operators", the prior is
		removed.
	-	An \ref operator without an \ref operand indicates no mapping.
	-	An \ref operand without an \ref operator indicates the "default"
		mapping, which is used for any \ref operator not found in the
		\ref lexicon.
*/
#if !defined( Om_Operations_LexiconOperation_ )
	#define Om_Operations_LexiconOperation_ Om::Operations::LexiconOperation

	#include "om/definition.hpp"
	#include "om/lexicon.hpp"
	#include "om/operations/program_operation.hpp"

namespace Om
{
	namespace Operations
	{
		//! The \ref lexicon_operation Operation implementation.
		typedef ProgramOperation< Lexicon > LexiconOperation;

		namespace
		{
			static Definition< LexiconOperation > const theLexiconDefinition;
		}
	}
}

#endif
