/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if !defined( Om_Operations_FrontPushOperation_ )
	#define Om_Operations_FrontPushOperation_ \
	Om::Operations::FrontPushOperation

	#include "om/default_operation.hpp"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::FrontPushOperation
		/*!
		\brief
			An Operation that joins an Operand to the front of a Program.
		*/
		template< typename ThisProgram, typename ThisImplementation >
		struct FrontPushOperation
		:
		DefaultOperation<
			FrontPushOperation< ThisProgram, ThisImplementation >
		>
		{
		public: // MARK: public (static)

			template< typename TheFrontPushOperation >
			static void GiveElements( TheFrontPushOperation &, Queue & );

		public: // MARK: public (non-static)

			FrontPushOperation();

			template< typename TheOperand >
			bool TakeOperand( Evaluation &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluation &, TheQueue & );

		private: // MARK: private (static)

			static Operator const & GetOperator();

		private: // MARK: private (non-static)

			ThisProgram thisProgram;
		};
	}
}

	#include "om/operations/front_push_operation.cpp"
#endif
