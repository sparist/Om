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
#if !defined( Om_Evaluation_ )
	#define Om_Evaluation_ Om::Evaluation

	#include "om/code_point.hpp"

namespace Om
{
	//! \cond
	struct Evaluator;

	struct Operand;

	struct Parser;

	struct Queue;
	//! \endcond

	// MARK: - Om::Evaluation
	/*!
	\brief
		A native \ref operations "Operation" that is partially applied to zero
		or more \ref Operand "Operands".

	The Evaluator takes and stores \ref Evaluation "Evaluations".  The internal
	Evaluation vector inside the Evaluator represents the entire state of the
	currently-evaluating Program.
	*/
	struct Evaluation
	{
	public: // MARK: public (non-static)

		virtual ~Evaluation() = 0;

		/*!
		\brief
			Gives the contents.
		\post
			Any calls on the Evaluation are undefined.
		*/
		virtual void GiveElements( Queue & ) = 0;

		//! \overload
		virtual void GiveElements( Queue & ) const = 0;

		virtual bool ReadQuotedElements( Evaluator &, Parser & ) = 0;

		/*!
		\brief
			Takes a Operand.
		\return
			True if this call completes the Evaluation, in which case any
			further calls on the Evaluation are undefined.
		\post
			If true was returned, any further calls on the Evaluation are
			undefined.
		*/
		virtual bool TakeElement( Evaluator &, Operand & ) = 0;

		//! \overload
		virtual bool TakeElement( Evaluator &, Operand const & ) = 0;

		/*!
		\brief
			Constructs and takes an Operand, which takes each Element from the
			argument.
		\return
			True if this call completes the Evaluation, in which case any
			further calls on the Evaluation are undefined.
		\post
			If true was returned, any further calls on the Evaluation are
			undefined.
		*/
		virtual bool TakeQuotedElements( Evaluator &, Queue & ) = 0;

		//! \overload
		virtual bool TakeQuotedElements( Evaluator &, Queue const & ) = 0;

	protected: // MARK: protected (non-static)

		Evaluation();

	private: // MARK: private (non-static)

		Evaluation( Evaluation const & );

		Evaluation const & operator =( Evaluation const & );
	};
}

	#include "om/evaluation.cpp"
#endif
