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

\defgroup lexicon_front_push_operation ->lexicon
	\ingroup operation
	\brief
		Push the contents of an \ref operand onto the front of a \ref lexicon
		(quoted).
	\par Input
		<tt>{A} {B}</tt>
	\par Output
		<tt>{A<br/>
		B}</tt>
	\par Implementation
		Om#Operations#LexiconFrontPushOperation
*/
#if !defined( Om_Operations_LexiconFrontPushOperation_ )
	#define Om_Operations_LexiconFrontPushOperation_ \
	Om::Operations::LexiconFrontPushOperation

	#include "om/definition.hpp"

	#define Om_Operations_LexiconFrontPushOperation_GetName_() "->lexicon"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::LexiconFrontPushOperation
		/*!
		\brief
			The \ref lexicon_front_push_operation Operation implementation.
		*/
		struct LexiconFrontPushOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );
		};

		namespace
		{
			static Definition<
				LexiconFrontPushOperation
			> const theLexiconFrontPushDefinition;
		}
	}
}

	#include "om/operations/lexicon_front_push_operation.cpp"
#endif
