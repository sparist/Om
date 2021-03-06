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

\defgroup om__operation__back_pull_element_operation__ [...]->
	\ingroup om__operation__
	\brief
		Pops the last element, quoted.
	\par Input
		<tt>{A B}</tt>
	\par Output
		<tt>{B} {A }</tt>
	\par Implementation
		Om::Language::Operation::BackPullElementOperation
*/

#ifndef Om_Language_Operation_BackPullElementOperation_

	#define Om_Language_Operation_BackPullElementOperation_ \
	Om::Language::Operation::BackPullElementOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_BackPullElementOperation_GetName_() \
	"[...]->"

namespace Om {

	namespace Language {

		//! \cond
		class Literal;
		//! \endcond

		namespace Operation {

			// MARK: - Om::Language::Operation::BackPullElementOperation

			/*!
			\brief
				The \ref om__operation__back_pull_element_operation__ operation implementation.
			*/
			class BackPullElementOperation {

			public: // MARK: public (static)

				static char const * GetName();

				static void Give(Evaluation &);

				/*!
				\brief
					The callback for PullOperation.
				*/
				template <typename TheConsumer>
				static void Pull(
					Literal &,
					TheConsumer &
				);

			};

			namespace {

				static System::Definition<BackPullElementOperation> const theBackPullElementDefinition;

			}

		}

	}

}

	#include "om/language/operation/back_pull_element_operation.cpp"

#endif
