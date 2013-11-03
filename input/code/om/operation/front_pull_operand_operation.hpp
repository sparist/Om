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

#ifndef Om_Operation_FrontPullOperandOperation_

	#define Om_Operation_FrontPullOperandOperation_ \
	Om::Operation::FrontPullOperandOperation

	#include "om/system.hpp"

	#define Om_Operation_FrontPullOperandOperation_GetName_() \
	"<-[operand|elements]"

namespace Om {

	//! \cond
	class Literal;
	//! \endcond

	namespace Operation {

		// MARK: - Om::Operation::FrontPullOperandOperation

		/*!
		\brief
			The \ref om__operation__front_pull_operand_operation__ operation implementation.
		*/
		class FrontPullOperandOperation {

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

			static System::Definition<FrontPullOperandOperation> const theFrontPullOperandDefinition;

		}

	}

}

	#include "om/operation/front_pull_operand_operation.cpp"

#endif
