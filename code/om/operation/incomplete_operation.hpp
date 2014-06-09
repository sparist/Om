/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Operation_IncompleteOperation_

	#define Om_Operation_IncompleteOperation_ \
	Om::Operation::IncompleteOperation

	#include "om/code_point.hpp"

namespace Om {

	//! \cond
	class Consumer;

	class Evaluation;

	class Operand;

	class Producer;

	class Reader;
	//! \endcond

	namespace Operation {

		// MARK: - Om::Operation::IncompleteOperation

		/*!
		\brief
			An Operation that has yet to consume one or more \ref Operand "Operands" and must live in memory until complete.
		*/
		class IncompleteOperation {

		public: // MARK: public (non-static)

			virtual ~IncompleteOperation() = 0;

			/*!
			\brief
				Gives the contents.
			\post
				Any calls on the object are undefined.
			*/
			virtual void GiveElements(Consumer &) = 0;

			/*!
			\brief
				\overload
			*/
			virtual void GiveElements(Consumer &) const = 0;

			virtual bool ParseQuotedElements(
				Evaluation &,
				Reader &
			) = 0;

			/*!
			\brief
				Takes an Operand.
			\return
				True if this call completes the Operation, in which case any further calls on the object are undefined.
			\post
				If true was returned, any further calls on the object are undefined.
			*/
			virtual bool TakeElement(
				Evaluation &,
				Operand &
			) = 0;

			/*!
			\brief
				\overload
			*/
			virtual bool TakeElement(
				Evaluation &,
				Operand const &
			) = 0;

			/*!
			\brief
				Constructs and takes an Operand, which takes each Element from the argument.
			\return
				True if this call completes the Operation, in which case any further calls on the object are undefined.
			\post
				If true was returned, any further calls on the object are undefined.
			*/
			virtual bool TakeQuotedElements(
				Evaluation &,
				Producer &
			) = 0;

			/*!
			\brief
				\overload
			*/
			virtual bool TakeQuotedElements(
				Evaluation &,
				Producer const &
			) = 0;

		protected: // MARK: protected (non-static)

			IncompleteOperation();

		private: // MARK: private (non-static)

			IncompleteOperation(IncompleteOperation const &);

			IncompleteOperation const & operator =(IncompleteOperation const &);

		};

	}

}

	#include "om/operation/incomplete_operation.cpp"

#endif
