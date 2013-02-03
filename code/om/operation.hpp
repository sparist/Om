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

#if !defined( Om_Operation_ )

	#define Om_Operation_ \
	Om::Operation

	#include "om/code_point.hpp"

namespace Om {

	//! \cond
	class Evaluation;

	class Operand;

	class Parser;

	class Queue;
	//! \endcond

	// MARK: - Om::Operation
	/*!
	\brief
		An \ref operations "Operation" that has yet to consume one or more \ref Operand "Operands", and therefore must live in memory while "incomplete".
	*/
	class Operation {
	public: // MARK: public (non-static)

		virtual ~Operation() = 0;

		/*!
		\brief
			Gives the contents.
		\post
			Any calls on the Operation are undefined.
		*/
		virtual void GiveElements( Queue & ) = 0;

		/*!
		\brief
			\overload
		*/
		virtual void GiveElements( Queue & ) const = 0;

		virtual bool ReadQuotedElements(
			Evaluation &,
			Parser &
		) = 0;

		/*!
		\brief
			Takes an Operand.
		\return
			True if this call completes the Operation, in which case any further calls on the Operation are undefined.
		\post
			If true was returned, any further calls on the Operation are undefined.
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
			True if this call completes the Operation, in which case any further calls on the Operation are undefined.
		\post
			If true was returned, any further calls on the Operation are undefined.
		*/
		virtual bool TakeQuotedElements(
			Evaluation &,
			Queue &
		) = 0;

		/*!
		\brief
			\overload
		*/
		virtual bool TakeQuotedElements(
			Evaluation &,
			Queue const &
		) = 0;

	protected: // MARK: protected (non-static)

		Operation();

	private: // MARK: private (non-static)

		Operation( Operation const & );

		Operation const & operator =( Operation const & );
	};
}

	#include "om/operation.cpp"

#endif
