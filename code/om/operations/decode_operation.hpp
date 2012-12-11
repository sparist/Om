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

\defgroup decode_operation decode
	\ingroup operations
	\brief
		Decodes encoded characters (non-recursively).
	\par Input
		<tt>{operator}</tt>
	\par Output
		<tt>{literal}</tt>
	\par Implementation
		Om#Operations#DecodeOperation

	Decoding the output of \ref encode_operation results in an \ref operand
	equivalent to the input of \ref encode_operation.
*/
#if !defined( Om_Operations_DecodeOperation_ )
	#define Om_Operations_DecodeOperation_ Om::Operations::DecodeOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_DecodeOperation_GetName_() "decode"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::DecodeOperation
		/*!
		\brief
			The \ref decode_operation Operation implementation.
		*/
		struct DecodeOperation
		:
		DefaultOperation< DecodeOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheDecodeOperation >
			static void GiveElements( TheDecodeOperation &, Queue & );

		public: // MARK: public (non-static)

			template< typename TheOperand >
			bool TakeOperand( Expansion &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Expansion &, TheQueue & );
		};

		namespace
		{
			static Definition< DecodeOperation > const theDecodeDefinition;
		}
	}
}

	#include "om/operations/decode_operation.cpp"
#endif
