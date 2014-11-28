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
*/

#ifndef Om_Language_Operation_FrontPushOperation_

	#define Om_Language_Operation_FrontPushOperation_ \
	Om::Language::Operation::FrontPushOperation

	#include "om/language/operation/default_incomplete_operation.hpp"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::FrontPushOperation

			/*!
			\brief
				An Operation that joins an Operand to the front of a Program.
			*/
			template <
				typename ThisProgram,
				typename ThisImplementation
			>
			class FrontPushOperation:
			public DefaultIncompleteOperation<
				FrontPushOperation<
					ThisProgram,
					ThisImplementation
				>
			> {

			public: // MARK: public (static)

				template <typename TheFrontPushOperation>
				static void GiveElements(
					TheFrontPushOperation &,
					Consumer &
				);

			public: // MARK: public (non-static)

				FrontPushOperation();

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

			private: // MARK: private (static)

				static Operator const & GetOperator();

			private: // MARK: private (non-static)

				ThisProgram thisProgram;

			};

		}

	}

}

	#include "om/language/operation/front_push_operation.cpp"

#endif
