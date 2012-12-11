/*!
\file
	\brief
		Om cpp file.
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
#if defined( Om_Expansion_ )

	#include "om/evaluator.hpp"

// MARK: Om::Expansion

	#define Type_ Om::Expansion

// MARK: public (non-static)

inline Type_::~Expansion()
{
	assert(
		this->thisExpression.IsEmpty() &&
		"The Expansion was not fully consumed."
	);
}

inline Type_::Expansion( Evaluator & theEvaluator )
:
thisExpression(),
thisEvaluator( theEvaluator )
{
}

inline Om::Translator const & Type_::GetTranslator() const
{
	return( this->thisEvaluator.GetTranslator() );
}

inline bool Type_::GiveTerm( Evaluator & theEvaluator )
{
	if( this->thisExpression.IsEmpty() ){ return( false ); }
	Expression::FormRange< Form > theFormRange( this->thisExpression );
	assert( theFormRange );
	if( theFormRange->GetOperator().IsEmpty() ){
		Operand theOperand;
		{
			Form::OperandRange< Operand > theOperandRange( *theFormRange );
			assert( theOperandRange );
			theOperand.Swap( *theOperandRange );
		}
		this->thisExpression.FrontPopTerm();
		theEvaluator.TakeOperand( *this, theOperand );
	} else{
		Operator theOperator;
		this->thisExpression.FrontGiveTerm( theOperator );
		theEvaluator.TakeOperator( *this, theOperator );
	}
	return( true );
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & theOperand )
{
	this->thisExpression.FrontTakeOperand( theOperand );
}

template< typename TheOperation >
inline void Type_::TakeOperation( std::auto_ptr< TheOperation > theOperation )
{
	this->thisEvaluator.TakeOperation( theOperation );
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & theOperator )
{
	this->thisExpression.FrontTakeOperator( theOperator );
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & theQueue )
{
	this->thisExpression.FrontTakeQuotedQueue( theQueue );
}

template< typename TheQueue >
inline void Type_::TakeQueue( TheQueue & theQueue )
{
	Expression theExpression;
	theExpression.TakeElements( theQueue );
	theExpression.TakeElements( this->thisExpression );
	this->thisExpression.Swap( theExpression );
}

	#undef Type_

#else
	#include "om/expansion.hpp"
#endif
