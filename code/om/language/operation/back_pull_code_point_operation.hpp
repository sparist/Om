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

\defgroup om__operation__back_pull_code_point_operation__ [code` points]->
	\ingroup om__operation__
	\brief
		Pops the last code point, quoted.
	\par Implementation
		Om::Language::Operation::BackPullCodePointOperation
*/

#ifndef Om_Language_Operation_BackPullCodePointOperation_

	#define Om_Language_Operation_BackPullCodePointOperation_ \
	Om::Language::Operation::BackPullCodePointOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_BackPullCodePointOperation_GetName_() \
	"[code points]->"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::BackPullCodePointOperation

			/*!
			\brief
				The \ref om__operation__back_pull_code_point_operation__ operation implementation.
			*/
			class BackPullCodePointOperation {

			public: // MARK: public (static)

				static char const * GetName();

				static void Give(Evaluation &);

				/*!
				\brief
					The callback for PullOperation.
				*/
				template <typename TheConsumer>
				static void Pull(
					Operator &,
					TheConsumer &
				);

			};

			namespace {

				static System::Definition<BackPullCodePointOperation> const theBackPullCodePointDefinition;

			}

		}

	}

}

	#include "om/language/operation/back_pull_code_point_operation.cpp"

#endif
