/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if !defined( Om_Operations_FillOperation_ )
	#define Om_Operations_FillOperation_ Om::Operations::FillOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"
	#include "om/expression.hpp"

	#define Om_Operations_FillOperation_GetName_() "fill"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::FillOperation
		/*!
		\brief
			The \ref fill_operation Operation implementation.
		*/
		struct FillOperation
		:
		DefaultOperation< FillOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheFillOperation >
			static void GiveElements( TheFillOperation &, Queue & );

		public: // MARK: public (non-static)

			FillOperation();

			template< typename TheOperand >
			bool TakeOperand( Evaluation &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluation &, TheQueue & );

		private: // MARK: private (static)

			typedef Expression::FormRange< Form > FormRange;

		private: // MARK: private (non-static)

			//! The output argument that is being filled.
			Expression thisExpression;

			//! The current position in the output argument.
			boost::optional< FormRange > thisFormRange;
		};

		namespace
		{
			static Definition< FillOperation > const theReadDefinition;
		}
	}
}

	#include "om/operations/fill_operation.cpp"
#endif
