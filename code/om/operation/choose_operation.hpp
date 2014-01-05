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
	\author
		Jason Erb

\defgroup om__operation__choose_operation__ choose
	\ingroup om__operation__
	\brief
		If the third \ref om__operand__ is empty, it is replaced with the first \ref om__operand__; otherwise, it is replaced with the second.
	\par Input
		<tt>{empty case} {non-empty case} {conditional}</tt>
	\par Output
		If <tt>{conditional}</tt> is empty, <tt>{empty case}</tt>; otherwise, <tt>{non-empty case}</tt>.
	\par Implementation
		Om::Operation::ChooseOperation
*/

#ifndef Om_Operation_ChooseOperation_

	#define Om_Operation_ChooseOperation_ \
	Om::Operation::ChooseOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_ChooseOperation_GetName_() \
	"choose"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::ChooseOperation

		/*!
		\brief
			The \ref om__operation__choose_operation__ operation implementation.
		*/
		class ChooseOperation:
		public DefaultIncompleteOperation<ChooseOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheChooseOperation>
			static void GiveElements(
				TheChooseOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

			ChooseOperation();

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

			/*!
			\brief
				The empty case handler.
			*/
			Operand thisEmptyCase;

			/*!
			\brief
				The non-empty case handler.
			*/
			Operand thisNonEmptyCase;

			/*!
			\brief
				The number of Operands received thus far.
			*/
			char thisOperandCount;

		};

		namespace {

			static System::Definition<ChooseOperation> const theChooseDefinition;

		}

	}

}

	#include "om/operation/choose_operation.cpp"

#endif
