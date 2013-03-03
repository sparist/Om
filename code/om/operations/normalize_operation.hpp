/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_NormalizeOperation_ )

	#define Om_Operations_NormalizeOperation_ \
	Om::Operations::NormalizeOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_NormalizeOperation_GetName_() \
	"normalize"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::NormalizeOperation
		/*!
		\brief
			The \ref om__operations__normalize_operation__ operation implementation.
		*/
		class NormalizeOperation:
		public DefaultOperation< NormalizeOperation > {
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheNormalizeOperation >
			static void GiveElements(
				TheNormalizeOperation &,
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

			static Definition< NormalizeOperation > const theNormalizeDefinition;

		}

	}

}

	#include "om/operations/normalize_operation.cpp"

#endif
