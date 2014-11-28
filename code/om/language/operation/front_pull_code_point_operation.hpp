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

\defgroup om__operation__front_pull_code_point_operation__ <-[code` points]
	\ingroup om__operation__
	\brief
		Pops the first code point, quoted.
	\par Implementation
		Om::Language::Operation::FrontPullCodePointOperation
*/

#ifndef Om_Language_Operation_FrontPullCodePointOperation_

	#define Om_Language_Operation_FrontPullCodePointOperation_ \
	Om::Language::Operation::FrontPullCodePointOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_FrontPullCodePointOperation_GetName_() \
	"<-[code points]"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::FrontPullCodePointOperation

			/*!
			\brief
				The \ref om__operation__front_pull_code_point_operation__ operation implementation.
			*/
			class FrontPullCodePointOperation {

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

				static System::Definition<FrontPullCodePointOperation> const theFrontPullCodePointDefinition;

			}

		}

	}

}

	#include "om/language/operation/front_pull_code_point_operation.cpp"

#endif
