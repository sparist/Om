/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operation_FrontPushOperation_

	#define Om_Operation_FrontPushOperation_ \
	Om::Operation::FrontPushOperation

	#include "om/operation/default_incomplete_operation.hpp"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::FrontPushOperation

		/*!
		\brief
			An Operation that joins an Operand to the front of a Program.
		*/
		template <
			typename ThisProgram,
			typename ThisImplementation
		>
		class FrontPushOperation :
		public DefaultIncompleteOperation<
			FrontPushOperation<
				ThisProgram,
				ThisImplementation
			>
		>
		{

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

	#include "om/operation/front_push_operation.cpp"

#endif
