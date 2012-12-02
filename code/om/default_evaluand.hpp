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
*/
#if !defined( Om_DefaultEvaluand_ )
	#define Om_DefaultEvaluand_ Om::DefaultEvaluand

	#include "om/evaluand.hpp"

namespace Om
{
	//! \cond
	struct Operator;
	//! \endcond

	// MARK: - Om::Operations::DefaultEvaluand
	/*!
	\brief
		A partial implementation of Evaluand.
	*/
	template< typename ThisImplementation >
	struct DefaultEvaluand
	:
	Evaluand
	{
	public: // MARK: public (static)

		static Operator const & GetOperator();

		template< typename TheEvaluandTaker >
		static void Give( TheEvaluandTaker & );

	public: // MARK: public (non-static)

		virtual ~DefaultEvaluand() = 0;

		virtual void GiveElements( Queue & );

		virtual void GiveElements( Queue & ) const;

		virtual bool ReadQuotedElements( Evaluator &, Parser & );

		/*!
		\brief
			Takes the Operand and gives the result to the Evaluator.
		\return
			True if this call completes the Evaluand, in which case any
			further calls on the Evaluand are undefined.
		*/
		virtual bool TakeElement( Evaluator &, Operand & );

		//! \overload
		virtual bool TakeElement( Evaluator &, Operand const & );

		virtual bool TakeQuotedElements( Evaluator &, Queue & );

		virtual bool TakeQuotedElements( Evaluator &, Queue const & );
	};
}

	#include "om/default_evaluand.cpp"
#endif
