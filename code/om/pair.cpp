/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Pair_ )

// MARK: Om::Pair

	#define Type_ \
	Om::Pair

// MARK: public (static)

inline Om::Pair const & Type_::GetEmpty()
{
	static Pair thePair;
	return( thePair );
}

// MARK: public (non-static)

inline Type_::~Pair()
{
}

inline Type_::Pair():
thisOperator(),
thisOperand()
{
}

inline void Type_::ClearOperand()
{
	this->thisOperand.Clear();
}

inline Om::Operand const & Type_::GetOperand() const
{
	return( this->thisOperand );
}

inline Om::Operator const & Type_::GetOperator() const
{
	return( this->thisOperator );
}

inline void Type_::GiveElements( Queue & theQueue )
{
	this->GiveElements(
		*this,
		theQueue
	);
	this->thisOperator.Clear();
	this->thisOperand.Clear();
}

inline void Type_::GiveElements( Queue & theQueue ) const
{
	this->GiveElements(
		*this,
		theQueue
	);
}

inline bool Type_::IsEmpty() const
{
	return(
		this->thisOperator.IsEmpty() &&
		this->thisOperand.IsEmpty()
	);
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & theOperand )
{
	this->thisOperand.Take( theOperand );
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & theOperator )
{
	this->thisOperator.Take( theOperator );
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & theQueue )
{
	this->thisOperand.SetProgram( theQueue.GiveProgram() );
}

// MARK: private (non-static)

template< typename ThePair >
inline void Type_::GiveElements(
	ThePair & thePair,
	Queue & theQueue
)
{
	if( !thePair.thisOperator.IsEmpty() ){
		theQueue.TakeElement( thePair.thisOperator );
	}
	if( !thePair.thisOperand.IsEmpty() ){
		theQueue.TakeElement( thePair.thisOperand );
	}
}

	#undef Type_

#else

	#include "om/pair.hpp"

#endif
