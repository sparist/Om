/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_ChooseOperation_ )

	#define Om_Operations_ChooseOperation_ \
	Om::Operations::ChooseOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_ChooseOperation_GetName_() \
	"choose"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::ChooseOperation
		/*!
		\brief
			The \ref choose_operation Operation implementation.
		*/
		struct ChooseOperation:
		DefaultOperation< ChooseOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheChooseOperation >
			static void GiveElements(
				TheChooseOperation &,
				Queue &
			);

		public: // MARK: public (non-static)

			ChooseOperation();

			template< typename TheOperand >
			bool TakeOperand(
				Evaluation &,
				TheOperand &
			);

			template< typename TheQueue >
			bool TakeQuotedQueue(
				Evaluation &,
				TheQueue &
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
			char unsigned thisOperandCount;
		};

		namespace
		{
			static Definition< ChooseOperation > const theChooseDefinition;
		}
	}
}

	#include "om/operations/choose_operation.cpp"

#endif
