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

\defgroup om__operation__equals_operation__ =
	\ingroup om__operation__
	\brief
		Compares two \ref om__operand__ "Operands" for equality.
	\par Examples
		<table>
			<tr><td><tt><b>= {A} {A}</b></tt></td></tr>
			<tr><td><tt><em>{{A}}</em></tt></td></tr>
		</table>
		<table>
			<tr><td><tt><b>= {A} {B}</b></tt></td></tr>
			<tr><td><tt><em>{}</em></tt></td></tr>
		</table>
		<table>
			<tr><td><tt><b>= {} {A}</b></tt></td></tr>
			<tr><td><tt><em>{}</em></tt></td></tr>
		</table>
		<table>
			<tr><td><tt><b>= {} {}</b></tt></td></tr>
			<tr><td><tt><em>{{}}</em></tt></td></tr>
		</table>
	\par Implementation
		Om::Language::Operation::EqualsOperation
*/

#ifndef Om_Language_Operation_EqualsOperation_

	#define Om_Language_Operation_EqualsOperation_ \
	Om::Language::Operation::EqualsOperation

	#include "om/language/operation/default_incomplete_operation.hpp"
	#include "om/language/system.hpp"

	#define Om_Language_Operation_EqualsOperation_GetName_() \
	"="

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::EqualsOperation

			/*!
			\brief
				The \ref om__operation__equals_operation__ operation implementation.
			*/
			class EqualsOperation:
			public DefaultIncompleteOperation<EqualsOperation> {

			public: // MARK: public (static)

				static char const * GetName();

				template <typename TheEqualsOperation>
				static void GiveElements(
					TheEqualsOperation &,
					Consumer &
				);

			public: // MARK: public (non-static)

				EqualsOperation();

				template <typename TheOperand>
				bool TakeOperand(
					Evaluation &,
					TheOperand &
				);

				template <typename TheProducer>
				bool TakeQuotedProducer(
					Evaluation &,
					TheProducer &
				);

			private: // MARK: private (non-static)

				template <typename TheProducer>
				bool IsMatch(TheProducer &) const;

				/*!
				\brief
					The Operand to compare with.
				*/
				Operand thisOperand;

			};

			namespace {

				static System::Definition<EqualsOperation> const theEqualsDefinition;

			}

		}

	}

}

	#include "om/language/operation/equals_operation.cpp"

#endif
