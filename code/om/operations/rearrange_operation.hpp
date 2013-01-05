/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
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

\defgroup rearrange_operation rearrange
	\ingroup operations
	\brief
		Rearranges \ref operand "Operands".
	\par Input
		<blockquote><tt>{new arrangement} {current arrangement} ...</tt>
		</blockquote>
		where remaining \ref operand "Operands" are pulled and mapped to
		\ref operator "Operators" in:
		<blockquote><tt>{current arrangement}</tt></blockquote>
		to construct a scope that is used to evaluate, then
		\ref dequote_operation "dequote":
		<blockquote><tt>{new arrangement}</tt></blockquote>
	\par Output
		The \ref dequote_operation "dequoted" evaluation of:
		<blockquote><tt>{new arrangement}</tt></blockquote>
		using the scope constructed by \ref fill_operation "filling" into:
		<blockquote><tt>{current arrangement}</tt></blockquote>
	\par Examples
		-	<tt>rearrange{C B A}{A B C}{1}{2}{3}</tt>
			<blockquote><tt>{3}{2}{1}</tt></blockquote>
	\par Implementation
		Om#Operations#RearrangeOperation
*/
#if !defined( Om_Operations_RearrangeOperation_ )
	#define Om_Operations_RearrangeOperation_ \
	Om::Operations::RearrangeOperation

	#include "om/definition.hpp"

	#define Om_Operations_RearrangeOperation_GetName_() "rearrange"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::RearrangeOperation
		/*!
		\brief
			The \ref rearrange_operation Operation implementation.
		*/
		struct RearrangeOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );
		};

		namespace
		{
			static Definition<
				RearrangeOperation
			> const theRearrangeDefinition;
		}
	}
}

	#include "om/operations/rearrange_operation.cpp"
#endif
