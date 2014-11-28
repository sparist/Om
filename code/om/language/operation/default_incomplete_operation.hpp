/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Language_Operation_DefaultIncompleteOperation_

	#define Om_Language_Operation_DefaultIncompleteOperation_ \
	Om::Language::Operation::DefaultIncompleteOperation

	#include "om/language/operation/incomplete_operation.hpp"

namespace Om {

	namespace Language {

		//! \cond
		class Operator;
		//! \endcond

		namespace Operation {

			// MARK: - Om::Language::Operation::DefaultIncompleteOperation

			/*!
			\brief
				A partial implementation of IncompleteOperation.
			*/
			template <typename ThisImplementation>
			class DefaultIncompleteOperation:
			public IncompleteOperation {

			public: // MARK: public (static)

				static Operator const & GetOperator();

				static void Give(Evaluation &);

			public: // MARK: public (non-static)

				virtual ~DefaultIncompleteOperation() = 0;

				virtual void GiveElements(Consumer &);

				virtual void GiveElements(Consumer &) const;

				virtual bool ParseQuotedElements(
					Evaluation &,
					Reader &
				);

				/*!
				\brief
					Takes the Operand and gives the result to the Evaluation.
				\return
					True if this call completes the Operation, in which case any further calls on the object are undefined.
				*/
				virtual bool TakeElement(
					Evaluation &,
					Operand &
				);

				/*!
				\brief
					\overload
				*/
				virtual bool TakeElement(
					Evaluation &,
					Operand const &
				);

				virtual bool TakeQuotedElements(
					Evaluation &,
					Producer &
				);

				virtual bool TakeQuotedElements(
					Evaluation &,
					Producer const &
				);

			};

		}

	}

}

	#include "om/language/operation/default_incomplete_operation.cpp"

#endif
