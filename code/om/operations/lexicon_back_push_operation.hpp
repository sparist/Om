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

\defgroup lexicon_back_push_operation lexicon<-
	\ingroup operations
	\brief
		Pushes the contents of an \ref operand onto the back of a \ref lexicon
		(quoted).
	\par Input
		<tt>{A} {B}</tt>
	\par Output
		<tt>{B<br/>
		A}</tt>
	\par Implementation
		Om#Operations#LexiconBackPushOperation
*/
#if !defined( Om_Operations_LexiconBackPushOperation_ )
	#define Om_Operations_LexiconBackPushOperation_ \
	Om::Operations::LexiconBackPushOperation

	#include "om/definition.hpp"

	#define Om_Operations_LexiconBackPushOperation_GetName_() "lexicon<-"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::LexiconBackPushOperation
		/*!
		\brief
			The \ref lexicon_back_push_operation Operation implementation.
		*/
		struct LexiconBackPushOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Expansion & );
		};

		namespace
		{
			static Definition<
				LexiconBackPushOperation
			> const theLexiconBackPushDefinition;
		}
	}
}

	#include "om/operations/lexicon_back_push_operation.cpp"
#endif
