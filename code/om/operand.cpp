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
#if defined( Om_Operand_ )

	#include "om/null.hpp"

// MARK: Om::Operand

	#define Type_ Om::Operand

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operand_GetName_() );
}

// MARK: public (non-static)

inline Type_::Operand()
:
thisProgram()
{
}

template< typename TheProgram >
inline Type_::Operand( std::auto_ptr< TheProgram > theProgram )
:
thisProgram( theProgram )
{
}

inline Type_ & Type_::operator =( Operand theOperand )
{
	this->Swap( theOperand );
	return( *this );
}

inline bool Type_::operator ==( Operand const & theOperand ) const
{
	return( this->GetProgram() == theOperand.GetProgram() );
}

inline Om::Program & Type_::operator *()
{
	return( this->GetProgram() );
}

inline Om::Program const & Type_::operator *() const
{
	return( this->GetProgram() );
}

inline Om::Program & Type_::GetProgram()
{
	return( this->thisProgram ? *this->thisProgram : Null::Get() );
}

inline Om::Program const & Type_::GetProgram() const
{
	return( this->thisProgram ? *this->thisProgram : Null::Get() );
}

inline bool Type_::IsEmpty() const
{
	return( false );
}

inline void Type_::ReadElements( Parser & theParser )
{
	for( ; theParser; theParser.Pop() ){}
}

inline void Type_::ReadQuotedElements( Parser & theParser )
{
	for( ; theParser; theParser.Pop() ){}
}

template< typename TheProgram >
inline void Type_::SetProgram( std::auto_ptr< TheProgram > theProgram )
{
	this->thisProgram.SetValue( theProgram );
}

inline void Type_::Swap( Operand & theOperand )
{
	this->thisProgram.Swap( theOperand.thisProgram );
}

inline void Type_::TakeElements( Queue & )
{
}

inline void Type_::TakeElements( Queue const & )
{
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & )
{
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & )
{
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & )
{
}

template< typename TheSeparator >
inline void Type_::TakeSeparator( TheSeparator & )
{
}

	#undef Type_

// MARK: -
// MARK: boost

template<>
inline void boost::swap( Om::Operand & theFirst, Om::Operand & theSecond )
{
	theFirst.Swap( theSecond );
}

#else
	#include "om/operand.hpp"
#endif
