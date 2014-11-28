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

\defgroup om__operation__do_operation__ do
	\ingroup om__operation__
	\brief
		Converts an \ref om__operand__ to a quoted \ref om__operator__, then \ref om__operation__dequote_operation__ "dequotes".
	\par Input
		<tt>{hello, world!}</tt>
	\par Output
		<tt>hello,` world!</tt>
	\par Implementation
		Om::Language::Operation::DoOperation
*/

#ifndef Om_Language_Operation_DoOperation_

	#define Om_Language_Operation_DoOperation_ \
	Om::Language::Operation::DoOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_DoOperation_GetName_() \
	"do"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::DoOperation

			/*!
			\brief
				The \ref om__operation__do_operation__ operation implementation.
			*/
			class DoOperation {

			public: // MARK: public (static)

				static char const * GetName();

				static void Give(Evaluation &);

			};

			namespace {

				static System::Definition<DoOperation> const theDoDefinition;

			}

		}

	}

}

	#include "om/language/operation/do_operation.cpp"

#endif
