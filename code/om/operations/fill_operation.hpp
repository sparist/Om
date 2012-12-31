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

\defgroup fill_operation fill
	\ingroup operations
	\brief
		"Fills" an \ref expression such that none of its
		\ref operator "Operators" is not followed by an \ref operand.
	\par Input
		<tt>{expression} ...</tt>
	\par Output
		<tt>{expression}</tt>
	\par Examples
		-	<tt>fill {A B{2} C} {1} {3}</tt>
			<blockquote>
				<tt>{A{1}<br/>
				B{2}<br/>
				C{3}}</tt>
			</blockquote>
	\par Implementation
		Om#Operations#FillOperation

	For each \ref operator in an \ref expression that has no \ref operand
	following it, pulls the next \ref operand following the \ref expression and
	inserts it after the \ref operator.
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
