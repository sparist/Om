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

#ifndef Om_Operations_FindOperation_

	#define Om_Operations_FindOperation_ \
	Om::Operations::FindOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_FindOperation_GetName_() \
	"find"

namespace Om {

	//! \cond
	class Lexicon;
	//! \endcond

	namespace Operations {

		// MARK: - Om::Operations::FindOperation

		/*!
		\brief
			The \ref om__operations__find_operation__ operation implementation.
		*/
		class FindOperation:
		public DefaultOperation<FindOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheFindOperation>
			static void GiveElements(
				TheFindOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

			FindOperation();

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

		private: // MARK: private (non-static)

			/*!
			\brief
				The Operator to find.
			*/
			boost::optional<Operator> thisOperator;

		};

		namespace {

			static Definition<FindOperation> const theFindDefinition;

		}

	}

}

	#include "om/operations/find_operation.cpp"

#endif
