/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if !defined( Om_Pair_ )
	#define Om_Pair_ Om::Pair

	#include "om/operator.hpp"

namespace Om
{
	// MARK: - Om::Pair
	struct Pair
	{
	public: // MARK: public (static)

		static Pair const & GetEmpty();

	public: // MARK: public (non-static)

		virtual ~Pair();

		Pair();

		void ClearOperand();

		Operand const & GetOperand() const;

		Operator const & GetOperator() const;

		void GiveElements( Queue & );

		void GiveElements( Queue & ) const;

		bool IsEmpty() const;

		template< typename TheOperand >
		void TakeOperand( TheOperand & );

		//! Replaces the Form Operator.
		template< typename TheOperator >
		void TakeOperator( TheOperator & );

		template< typename TheQueue >
		void TakeQuotedQueue( TheQueue & );

	private: // MARK: private (static)

		template< typename ThePair >
		static void GiveElements( ThePair &, Queue & );

	private: // MARK: private (non-static)

		Operator thisOperator;

		Operand thisOperand;
	};
}

	#include "om/pair.cpp"
#endif
