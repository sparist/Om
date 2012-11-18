/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
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

\defgroup encode_operation encode
	\ingroup operation
	\brief
		Encodes all special characters (non-recursively).
	\par Input
		<tt>{program}</tt>
	\par Output
		<tt>{operator}</tt>
	\par Implementation
		Om#Operations#EncodeOperation
*/
#if !defined( Om_Operations_EncodeOperation_ )
	#define Om_Operations_EncodeOperation_ Om::Operations::EncodeOperation

	#include "om/definition.hpp"
	#include "om/default_evaluand.hpp"

	#define Om_Operations_EncodeOperation_GetName_() "encode"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::EncodeOperation
		/*!
		\brief
			The \ref encode_operation Operation implementation.
		*/
		struct EncodeOperation
		:
		DefaultEvaluand< EncodeOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheEncodeOperation >
			static void GiveElements( TheEncodeOperation &, Queue & );

		public: // MARK: public (non-static)

			template< typename TheOperand >
			bool TakeOperand( Evaluator &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluator &, TheQueue & );
		};

		namespace
		{
			static Definition< EncodeOperation > const theEncodeDefinition;
		}
	}
}

	#include "om/operations/encode_operation.cpp"
#endif
