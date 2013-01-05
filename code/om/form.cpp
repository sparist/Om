/*!
\file
	\brief
		Om cpp file.
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
#if defined( Om_Form_ )

// MARK: Om::Form

	#define Type_ Om::Form

// MARK: public (non-static)

inline Type_::Form()
:
thisOperator(),
thisOperandDeque()
{
}

inline bool Type_::BackGiveTerm( Queue & theQueue )
{
	if( this->thisOperandDeque.empty() ){
		assert( !this->thisOperator.IsEmpty() );
		this->thisOperator.GiveElements( theQueue );
		assert( this->thisOperator.IsEmpty() );
		return( true );
	}
	this->thisOperandDeque.back().GiveElements( theQueue );
	this->thisOperandDeque.pop_back();
	return( this->IsEmpty() );
}

inline bool Type_::BackPopTerm()
{
	if( this->thisOperandDeque.empty() ){
		assert( !this->thisOperator.IsEmpty() );
		Operator().Swap( this->thisOperator );
		return( true );
	}
	this->thisOperandDeque.pop_back();
	return( this->IsEmpty() );
}

template< typename TheOperand >
inline void Type_::BackTakeOperand( TheOperand & theOperand )
{
	this->thisOperandDeque.push_back( Operand() );
	this->thisOperandDeque.back().Take( theOperand );
}

template< typename TheQueue >
inline void Type_::BackTakeQuotedQueue( TheQueue & theQueue )
{
	this->thisOperandDeque.push_back( Operand() );
	this->thisOperandDeque.back().SetProgram( theQueue.GiveProgram() );
}

inline bool Type_::FrontGiveTerm( Queue & theQueue )
{
	if( this->thisOperator.IsEmpty() ){
		assert( !this->thisOperandDeque.empty() );
		this->thisOperandDeque.front().GiveElements( theQueue );
		this->thisOperandDeque.pop_front();
	} else{
		this->thisOperator.GiveElements( theQueue );
		assert( this->thisOperator.IsEmpty() );
	}
	return( this->thisOperandDeque.empty() );
}

inline bool Type_::FrontPopTerm()
{
	if( this->thisOperator.IsEmpty() ){
		assert( !this->thisOperandDeque.empty() );
		this->thisOperandDeque.pop_front();
	} else{
		Operator().Swap( this->thisOperator );
		assert( this->thisOperator.IsEmpty() );
	}
	return( this->thisOperandDeque.empty() );
}

template< typename TheOperand >
inline void Type_::FrontTakeOperand( TheOperand & theOperand )
{
	this->thisOperandDeque.push_front( Operand() );
	this->thisOperandDeque.front().Take( theOperand );
}

template< typename TheQueue >
inline void Type_::FrontTakeQuotedQueue( TheQueue & theQueue )
{
	this->thisOperandDeque.push_front( Operand() );
	this->thisOperandDeque.front().SetProgram( theQueue.GiveProgram() );
}

inline Om::Operator const & Type_::GetOperator() const
{
	return( this->thisOperator );
}

inline void Type_::GiveElements( Queue & theQueue )
{
	this->GiveElements< OperandDeque::iterator >( *this, theQueue );
	this->thisOperandDeque.clear();
}

inline void Type_::GiveElements( Queue & theQueue ) const
{
	this->GiveElements< OperandDeque::const_iterator >( *this, theQueue );
}

inline bool Type_::IsEmpty() const
{
	return( this->thisOperator.IsEmpty() && this->thisOperandDeque.empty() );
}

inline void Type_::Swap( Form & theForm )
{
	this->thisOperator.Swap( theForm.thisOperator );
	this->thisOperandDeque.swap( theForm.thisOperandDeque );
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & theOperator )
{
	assert( !theOperator.IsEmpty() );
	this->thisOperator.Take( theOperator );
}

// MARK: private (static)

template< typename TheOperandIterator, typename TheForm >
inline void Type_::GiveElements(
	TheForm & theForm,
	Queue & theQueue
)
{
	assert( !theForm.IsEmpty() );
	if( !theForm.thisOperator.IsEmpty() ){
		theQueue.TakeElement( theForm.thisOperator );
	}
	TheOperandIterator const theEnd = theForm.thisOperandDeque.end();
	TheOperandIterator theCurrent = theForm.thisOperandDeque.begin();
	for( ; theEnd != theCurrent; ++theCurrent ){
		theQueue.TakeElement( *theCurrent );
	}
}

	#undef Type_

// MARK: -
// MARK: Om::Form::ElementRange

	#define Type_ Om::Form::ElementRange

// MARK: public (non-static)

inline Type_::ElementRange( Form const & theForm )
:
thisOperandIterator( theForm.thisOperandDeque.begin() ),
thisOperandEnd( theForm.thisOperandDeque.end() ),
thisElement( &theForm.thisOperator )
{
	if( theForm.thisOperator.IsEmpty() ){
		assert( this->thisOperandEnd != this->thisOperandIterator );
		this->thisElement = &*this->thisOperandIterator++;
	}
}

inline bool Type_::operator ==( ElementRange const & theElementRange ) const
{
	return( this->thisElement == theElementRange.thisElement );
}

inline bool Type_::operator !() const
{
	return( !this->thisElement );
}

inline Om::Element const & Type_::operator *() const
{
	assert( this->thisElement );
	return( *this->thisElement );
}

inline void Type_::End()
{
	this->thisElement = 0;
}

inline void Type_::Pop()
{
	assert( this->thisElement );
	this->thisElement = (
		this->thisOperandEnd == this->thisOperandIterator
	) ? 0 : &*this->thisOperandIterator++;
}

	#undef Type_

// MARK: -
// MARK: Om::Form::OperandRange

	#define Type_ Om::Form::OperandRange

// MARK: public (non-static)

inline Type_< Om::Operand >::OperandRange( Form & theForm )
:
Sources::CollectionFrontSource< Operand, OperandDeque::iterator >(
	theForm.thisOperandDeque
)
{
}

inline Type_< Om::Operand const >::OperandRange( Form const & theForm )
:
Sources::CollectionFrontSource< Operand const, OperandDeque::const_iterator >(
	theForm.thisOperandDeque
)
{
}

	#undef Type_

// MARK: -
// MARK: boost

template<>
inline void boost::swap( Om::Form & theFirst, Om::Form & theSecond )
{
	theFirst.Swap( theSecond );
}

#else
	#include "om/form.hpp"
#endif
