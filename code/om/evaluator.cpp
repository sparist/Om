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
#if defined( Om_Evaluator_ )

	#include "om/expansion.hpp"
	#include "om/operation.hpp"
	#include "om/operator.hpp"
	#include "om/translator.hpp"

// MARK: Om::Evaluator

	#define Type_ Om::Evaluator

// MARK: public (non-static)

inline Type_::~Evaluator()
{
	try{
		if( !this->IsEmpty() ){
			if( this->thisGaveElementToOutput ){
				this->thisOutput.TakeElement( Separator::GetLineSeparator() );
			}
			this->GiveElements( this->thisOutput );
		}
	} catch( ... ){}
}

inline Type_::Evaluator( Queue & theOutput, Translator const & theTranslator )
:
thisOutput( theOutput ),
thisTranslator( theTranslator ),
thisOperationVector(),
thisGaveElementToOutput()
{
}

inline bool Type_::operator ==( Program const & theProgram ) const
{
	Expression theExpression;
	this->GiveElements( theExpression );
	return( theExpression == theProgram );
}

inline void Type_::Clear()
{
	this->thisOperationVector.clear();
}

inline Om::Translator const & Type_::GetTranslator() const
{
	return( this->thisTranslator );
}

inline void Type_::GiveElements( Queue & theQueue )
{
	this->GiveElements(
		this->thisOperationVector.begin(),
		this->thisOperationVector.end(),
		theQueue
	);
	this->Clear();
}

inline void Type_::GiveElements( Queue & theQueue ) const
{
	this->GiveElements(
		this->thisOperationVector.begin(),
		this->thisOperationVector.end(),
		theQueue
	);
}

inline std::auto_ptr< Om::Program > Type_::GiveProgram()
{
	return( this->GiveProgram( *this ) );
}

inline std::auto_ptr< Om::Program > Type_::GiveProgram() const
{
	return( this->GiveProgram( *this ) );
}

inline bool Type_::IsEmpty() const
{
	return( this->thisOperationVector.empty() );
}

inline void Type_::ReadElements( Parser & theParser )
{
	while( theParser ){
		assert( Symbols::theEndOperandSymbol != *theParser );
		switch( *theParser ){
		case Symbols::theStartOperandSymbol:
			theParser.Pop();
			{
				// Ensure that this does not resolve to the copy constructor.
				Source< CodePoint const > & theCodePointSource = theParser;

				Parser theOperandParser( theCodePointSource );
				this->ReadQuotedElements( theOperandParser );
			}
			if( !theParser ){ return; }
			assert( Symbols::theEndOperandSymbol == *theParser );
		Om_Symbols_SeparatorSymbol_GetCases_():
			theParser.Pop();
			continue;
		}
		Operator theOperator( theParser );
		this->TakeOperator( theOperator );
	}
}

inline void Type_::ReadQuotedElements( Parser & theParser )
{
	Expansion theExpansion( *this );
	this->ReadQuotedElements( theExpansion, theParser );
	this->Evaluate( theExpansion );
}

inline void Type_::ReadQuotedElements(
	Expansion & theExpansion,
	Parser & theParser
)
{
	if( this->thisOperationVector.empty() ){
		this->thisOutput.ReadQuotedElements( theParser );
		this->thisGaveElementToOutput = true;
	} else{
		std::auto_ptr< Operation > theOperation(
			this->thisOperationVector.pop_back().release()
		);
		assert( theOperation.get() );
		if( !theOperation->ReadQuotedElements( theExpansion, theParser ) ){
			this->thisOperationVector.push_back( theOperation );
		}
	}
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & theOperand )
{
	Expansion theExpansion( *this );
	this->TakeOperand( theExpansion, theOperand );
	this->Evaluate( theExpansion );
}

template< typename TheOperand >
inline void Type_::TakeOperand(
	Expansion & theExpansion,
	TheOperand & theOperand
)
{
	if( this->thisOperationVector.empty() ){
		this->thisOutput.TakeElement( theOperand );
		this->thisGaveElementToOutput = true;
	} else{
		std::auto_ptr< Operation > theOperation(
			this->thisOperationVector.pop_back().release()
		);
		assert( theOperation.get() );
		if( !theOperation->TakeElement( theExpansion, theOperand ) ){
			this->thisOperationVector.push_back( theOperation );
		}
	}
}

template< typename TheOperation >
inline void Type_::TakeOperation( std::auto_ptr< TheOperation > theOperation )
{
	this->thisOperationVector.push_back( theOperation );
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & theOperator )
{
	Expansion theExpansion( *this );
	this->TakeOperator( theExpansion, theOperator );
	this->Evaluate( theExpansion );
}

template< typename TheOperator >
inline void Type_::TakeOperator(
	Expansion & theExpansion,
	TheOperator & theOperator
)
{
	assert( !theOperator.IsEmpty() );
	switch( this->thisTranslator.Translate( theExpansion, theOperator ) ){
	case 0:
		switch( this->thisTranslator.Translate( theExpansion, Operator() ) ){
		case 0:
		case 1:
			break;
		default:
			return;
		}
	case 1:
		break;
	default:
		return;
	}

	// Flush everything up to, and including, the operator.
	{
		// At the very least, the operator will be flushed.
		if( this->thisGaveElementToOutput ){
			this->thisOutput.TakeElement( Separator::GetLineSeparator() );
		}

		// Flush the evaluation.
		// Starts with Operator; leading Operands would have been sent.
		if( !this->IsEmpty() ){
			this->GiveElements( this->thisOutput );
			this->thisOutput.TakeElement( Separator::GetLineSeparator() );
		}

		// Flush the operator.
		this->thisOutput.TakeElement( theOperator );
		this->thisGaveElementToOutput = true;
	}
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & theQueue )
{
	Expansion theExpansion( *this );
	this->TakeQuotedQueue( theExpansion, theQueue );
	this->Evaluate( theExpansion );
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue(
	Expansion & theExpansion,
	TheQueue & theQueue
)
{
	if( this->thisOperationVector.empty() ){
		this->thisOutput.TakeQuotedElements( theQueue );
		this->thisGaveElementToOutput = true;
	} else{
		std::auto_ptr< Operation > theOperation(
			this->thisOperationVector.pop_back().release()
		);
		assert( theOperation.get() );
		if( !theOperation->TakeQuotedElements( theExpansion, theQueue ) ){
			this->thisOperationVector.push_back( theOperation );
		}
	}
}

template< typename TheSeparator >
inline void Type_::TakeSeparator( TheSeparator & )
{
}

// MARK: private (static)

template< typename TheIterator >
inline void Type_::GiveElements(
	TheIterator theIterator,
	TheIterator const theEnd,
	Queue & theQueue
)
{
	if( theEnd != theIterator ){
		for( ; ; theQueue.TakeElement( Separator::GetLineSeparator() ) ){
			theIterator->GiveElements( theQueue );
			if( theEnd == ++theIterator ){ break; }
		}
	}
}

template< typename TheEvaluator >
inline std::auto_ptr< Om::Program > Type_::GiveProgram(
	TheEvaluator & theEvaluator
)
{
	std::auto_ptr< Program > theExpression( new Expression );
	assert( theExpression.get() );
	theEvaluator.GiveElements( *theExpression );
	return( theExpression );
}

// MARK: private (non-static)

inline void Type_::Evaluate( Expansion & theExpansion )
{
	while( theExpansion.GiveTerm( *this ) ){}
}

	#undef Type_

#else
	#include "om/evaluator.hpp"
#endif
