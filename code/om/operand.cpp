/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Operand_ )

	#include "om/literal.hpp"
	#include "om/null.hpp"

// MARK: Om::Operand

	#define Type_ \
	Om::Operand

// MARK: public (static)

inline char const * Type_::GetName() {
	return( Om_Operand_GetName_() );
}

// MARK: public (non-static)

inline Type_::Operand():
thisProgram() {}

template< typename TheProgram >
inline Type_::Operand(
	std::auto_ptr< TheProgram > theProgram
):
thisProgram( theProgram ) {}

inline Type_ & Type_::operator =( Operand theOperand ) {
	this->Swap( theOperand );
	return( *this );
}

inline bool Type_::operator ==( Operand const & theOperand ) const {
	return(
		this->IsEmpty()?
		theOperand.IsEmpty():
		( *this->GetProgram() == *theOperand.GetProgram() )
	);
}

inline Om::Program & Type_::operator *() {
	return(
		this->thisProgram.IsEmpty()?
		Null::Get():
		*this->thisProgram
	);
}

inline Om::Program const & Type_::operator *() const {
	return(
		this->thisProgram.IsEmpty()?
		Null::Get():
		*this->thisProgram
	);
}

inline void Type_::Clear() {
	this->thisProgram.Clear();
}

inline Om::Program * Type_::GetProgram() {
	return( this->thisProgram.GetValue() );
}

inline Om::Program const * Type_::GetProgram() const {
	return( this->thisProgram.GetValue() );
}

inline bool Type_::IsEmpty() const {
	return( !this->thisProgram );
}

inline void Type_::ReadElements( Parser & theParser ) {
	if( this->IsEmpty() ) {
		for(
			;
			;
			theParser.Pop()
		) {
			if( !theParser ) {
				return;
			}
			assert( Symbols::theEndOperandSymbol != *theParser );
			switch( *theParser ) {
			default:
				continue;
			case Symbols::theStartOperandSymbol:
				theParser.Pop();
				{
					// Ensure against copy constructor call.
					Source< CodePoint const > & theCodePointSource = theParser;

					Parser theOperandParser( theCodePointSource );
					this->ReadQuotedElements( theOperandParser );
				}
				assert(
					!theParser ||
					Symbols::theEndOperandSymbol == *theParser
				);
				// Fall through.
			}
			break;
		}
	}

	for(
		;
		theParser;
		theParser.Pop()
	) {}
}

inline void Type_::ReadQuotedElements( Parser & theParser ) {
	Literal theLiteral;
	theLiteral.ReadElements( theParser );
	this->TakeQuotedQueue( theLiteral );
}

template< typename TheProgram >
inline void Type_::SetProgram(
	std::auto_ptr< TheProgram > theProgram
) {
	this->thisProgram.SetValue( theProgram );
}

inline void Type_::Swap( Operand & theOperand ) {
	this->thisProgram.Swap( theOperand.thisProgram );
}

inline void Type_::TakeElements( Queue & theQueue ) {
	if( this->IsEmpty() ) {
		DefaultElement< Operand >::TakeElements( theQueue );
	}
}

inline void Type_::TakeElements( Queue const & theQueue ) {
	if( this->IsEmpty() ) {
		DefaultElement< Operand >::TakeElements( theQueue );
	}
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & theOperand ) {
	if( this->IsEmpty() ) {
		this->Take( theOperand );
	}
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & ) {}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & theQueue ) {
	if( this->IsEmpty() ) {
		this->SetProgram( theQueue.GiveProgram() );
	}
}

template< typename TheSeparator >
inline void Type_::TakeSeparator( TheSeparator & ) {}

	#undef Type_

// MARK: -
// MARK: boost

template<>
inline void boost::swap(
	Om::Operand & theFirst,
	Om::Operand & theSecond
) {
	theFirst.Swap( theSecond );
}

#else

	#include "om/operand.hpp"

#endif
