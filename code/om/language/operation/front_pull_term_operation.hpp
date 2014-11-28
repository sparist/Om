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

\defgroup om__operation__front_pull_term_operation__ <-[terms]
	\ingroup om__operation__
	\brief
		Pops the first term (\ref om__operator__ or \ref om__operand__), quoted.
	\par Input
		<tt>{A B}</tt>
	\par Output
		<tt>{A}{B}</tt>
	\par Examples
		-	<tt><-[terms] {A B}</tt>
			<blockquote><tt>{A}{B}</tt></blockquote>
		-	<tt><-[terms] {{A} B}</tt>
			<blockquote><tt>{{A}}{B}</tt></blockquote>
		-	<tt><-[terms] {A B }</tt>
			<blockquote><tt>{A}{B}</tt></blockquote>
		-	<tt><-[terms] {A {B} C}</tt>
			<blockquote><tt>{A}{{B}<br/>C}</tt></blockquote>
		-	<tt><-[terms] {}</tt>
			<blockquote><tt>{}{}</tt></blockquote>
	\par Implementation
		Om::Language::Operation::FrontPullTermOperation
*/

#ifndef Om_Language_Operation_FrontPullTermOperation_

	#define Om_Language_Operation_FrontPullTermOperation_ \
	Om::Language::Operation::FrontPullTermOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_FrontPullTermOperation_GetName_() \
	"<-[terms]"

namespace Om {

	namespace Language {

		//! \cond
		class Expression;
		//! \endcond

		namespace Operation {

			// MARK: - Om::Language::Operation::FrontPullTermOperation

			/*!
			\brief
				The \ref om__operation__front_pull_term_operation__ operation implementation.
			*/
			class FrontPullTermOperation {

			public: // MARK: public (static)

				static char const * GetName();

				static void Give(Evaluation &);

				/*!
				\brief
					The callback for PullOperation.
				*/
				template <typename TheConsumer>
				static void Pull(
					Expression &,
					TheConsumer &
				);

			};

			namespace {

				static System::Definition<FrontPullTermOperation> const theFrontPullTermDefinition;

			}

		}

	}

}

	#include "om/language/operation/front_pull_term_operation.cpp"

#endif
