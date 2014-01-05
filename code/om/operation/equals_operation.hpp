/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup om__operation__equals_operation__ =
	\ingroup om__operation__
	\brief
		Compares two \ref om__operand__ "Operands" for equality.
	\par Examples
		-	<tt>= {A} {A}</tt>
			<blockquote><tt>{{A}}</tt></blockquote>
		-	<tt>= {A} {B}</tt>
			<blockquote><tt>{}</tt></blockquote>
		-	<tt>= {} {A}</tt>
			<blockquote><tt>{}</tt></blockquote>
		-	<tt>= {} {}</tt>
			<blockquote><tt>{{}}</tt></blockquote>
	\par Implementation
		Om::Operation::EqualsOperation
*/

#ifndef Om_Operation_EqualsOperation_

	#define Om_Operation_EqualsOperation_ \
	Om::Operation::EqualsOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_EqualsOperation_GetName_() \
	"="

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::EqualsOperation

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

	#include "om/operation/equals_operation.cpp"

#endif
