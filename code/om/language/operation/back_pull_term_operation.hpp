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

\defgroup om__operation__back_pull_term_operation__ [terms]->
	\ingroup om__operation__
	\brief
		Pops the last term (\ref om__operator__ or \ref om__operand__), quoted.
	\par Input
		<tt>{A B}</tt>
	\par Output
		<tt>{B} {A}</tt>
	\par Examples
		<table>
			<tr><td><tt><b>[terms]-> {A B}</b></tt></td></tr>
			<tr><td><tt><em>{B}{A}</em></tt></td></tr>
		</table>
		<table>
			<tr><td><tt><b>[terms]-> {A {B}}</b></tt></td></tr>
			<tr><td><tt><em>{{B}}{A}</em></tt></td></tr>
		</table>
		<table>
			<tr><td><tt><b>[terms]-> {A B }</b></tt></td></tr>
			<tr><td><tt><em>{B}{A}</em></tt></td></tr>
		</table>
		<table>
			<tr><td><tt><b>[terms]-> {A {B} C}</b></tt></td></tr>
			<tr><td><tt><em>{C}{A{B}}</em></tt></td></tr>
		</table>
		<table>
			<tr><td><tt><b>[terms]-> {}</b></tt></td></tr>
			<tr><td><tt><em>{}{}</em></tt></td></tr>
		</table>
	\par Implementation
		Om::Language::Operation::BackPullTermOperation
*/

#ifndef Om_Language_Operation_BackPullTermOperation_

	#define Om_Language_Operation_BackPullTermOperation_ \
	Om::Language::Operation::BackPullTermOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_BackPullTermOperation_GetName_() \
	"[terms]->"

namespace Om {

	namespace Language {

		//! \cond
		class Expression;
		//! \endcond

		namespace Operation {

			// MARK: - Om::Language::Operation::BackPullTermOperation

			/*!
			\brief
				The \ref om__operation__back_pull_term_operation__ operation implementation.
			*/
			class BackPullTermOperation {

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

				static System::Definition<BackPullTermOperation> const theBackPullTermDefinition;

			}

		}

	}

}

	#include "om/language/operation/back_pull_term_operation.cpp"

#endif
