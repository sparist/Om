/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup om__operation__rearrange_operation__ rearrange
	\ingroup om__operation__
	\brief
		Rearranges \ref om__operand__ "Operands".
	\par Input
		<blockquote><tt>{new arrangement} {current arrangement} ...</tt></blockquote>
		where remaining \ref om__operand__ "Operands" are pulled and mapped to \ref om__operator__ "Operators" in:
		<blockquote><tt>{current arrangement}</tt></blockquote>
		to construct a scope that is used to evaluate, then \ref om__operation__dequote_operation__ "dequote":
		<blockquote><tt>{new arrangement}</tt></blockquote>
	\par Output
		The \ref om__operation__dequote_operation__ "dequoted" evaluation of:
		<blockquote><tt>{new arrangement}</tt></blockquote>
		using the scope constructed by \ref om__operation__fill_operation__ "filling" into:
		<blockquote><tt>{current arrangement}</tt></blockquote>
	\par Examples
		-	<tt>rearrange{C B A}{A B C}{1}{2}{3}</tt>
			<blockquote><tt>{3}{2}{1}</tt></blockquote>
	\par Implementation
		Om::Operation::RearrangeOperation
*/

#ifndef Om_Operation_RearrangeOperation_

	#define Om_Operation_RearrangeOperation_ \
	Om::Operation::RearrangeOperation

	#include "om/system.hpp"

	#define Om_Operation_RearrangeOperation_GetName_() \
	"rearrange"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::RearrangeOperation

		/*!
		\brief
			The \ref om__operation__rearrange_operation__ operation implementation.
		*/
		class RearrangeOperation {

		public: // MARK: public (static)

			static char const * GetName();

			static void Give(Evaluation &);

		};

		namespace {

			static System::Definition<RearrangeOperation> const theRearrangeDefinition;

		}

	}

}

	#include "om/operation/rearrange_operation.cpp"

#endif
