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

#if !defined( Om_Operations_DecodeOperation_ )

	#define Om_Operations_DecodeOperation_ \
	Om::Operations::DecodeOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_DecodeOperation_GetName_() \
	"decode"

namespace Om {
	namespace Operations {

		// MARK: - Om::Operations::DecodeOperation
		/*!
		\brief
			The \ref decode_operation Operation implementation.
		*/
		class DecodeOperation:
		public DefaultOperation< DecodeOperation > {
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheDecodeOperation >
			static void GiveElements(
				TheDecodeOperation &,
				Queue &
			);

		public: // MARK: public (non-static)

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
		};

		namespace {
			static Definition< DecodeOperation > const theDecodeDefinition;
		}
	}
}

	#include "om/operations/decode_operation.cpp"

#endif
