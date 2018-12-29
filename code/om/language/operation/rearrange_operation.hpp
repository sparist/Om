/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb

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
		<table>
			<tr><td><tt><b>rearrange {C B A} {A B C} {1} {2} {3}</b></tt></td></tr>
			<tr><td><tt><em>{3}{2}{1}</em></tt></td></tr>
		</table>
	\par Implementation
		Om::Language::Operation::RearrangeOperation
*/

#ifndef Om_Language_Operation_RearrangeOperation_

	#define Om_Language_Operation_RearrangeOperation_ \
	Om::Language::Operation::RearrangeOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_RearrangeOperation_GetName_() \
	"rearrange"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::RearrangeOperation

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

}

	#include "om/language/operation/rearrange_operation.cpp"

#endif
