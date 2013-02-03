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

#if !defined( Om_DefaultOperation_ )

	#define Om_DefaultOperation_ \
	Om::DefaultOperation

	#include "om/operation.hpp"

namespace Om {

	//! \cond
	struct Operator;
	//! \endcond

	// MARK: - Om::Operations::DefaultOperation
	/*!
	\brief
		A partial implementation of Operation.
	*/
	template< typename ThisImplementation >
	struct DefaultOperation:
	public Operation {
	public: // MARK: public (static)

		static Operator const & GetOperator();

		static void Give( Evaluation & );

	public: // MARK: public (non-static)

		virtual ~DefaultOperation() = 0;

		virtual void GiveElements( Queue & );

		virtual void GiveElements( Queue & ) const;

		virtual bool ReadQuotedElements(
			Evaluation &,
			Parser &
		);

		/*!
		\brief
			Takes the Operand and gives the result to the Evaluation.
		\return
			True if this call completes the Operation, in which case any further calls on the Operation are undefined.
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
			Queue &
		);

		virtual bool TakeQuotedElements(
			Evaluation &,
			Queue const &
		);
	};
}

	#include "om/default_operation.cpp"

#endif
