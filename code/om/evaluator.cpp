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

	#include "om/evaluand.hpp"
	#include "om/evaluation.hpp"
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
thisEvaluandVector(),
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
	this->thisEvaluandVector.clear();
}

inline Om::Translator const & Type_::GetTranslator() const
{
	return( this->thisTranslator );
}

inline void Type_::GiveElements( Queue & theQueue )
{
	this->GiveElements(
		this->thisEvaluandVector.begin(),
		this->thisEvaluandVector.end(),
		theQueue
	);
	this->Clear();
}

inline void Type_::GiveElements( Queue & theQueue ) const
{
	this->GiveElements(
		this->thisEvaluandVector.begin(),
		this->thisEvaluandVector.end(),
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
	return( this->thisEvaluandVector.empty() );
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
	if( this->thisEvaluandVector.empty() ){
		this->thisOutput.ReadQuotedElements( theParser );
		this->thisGaveElementToOutput = true;
	} else{
		std::auto_ptr< Evaluand > theEvaluand(
			this->thisEvaluandVector.pop_back().release()
		);
		assert( theEvaluand.get() );
		if( !theEvaluand->ReadQuotedElements( *this, theParser ) ){
			this->thisEvaluandVector.push_back( theEvaluand );
		}
	}
}

template< typename TheEvaluand >
inline void Type_::TakeEvaluand( std::auto_ptr< TheEvaluand > theEvaluand )
{
	this->thisEvaluandVector.push_back( theEvaluand );
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & theOperand )
{
	if( this->thisEvaluandVector.empty() ){
		this->thisOutput.TakeElement( theOperand );
		this->thisGaveElementToOutput = true;
	} else{
		std::auto_ptr< Evaluand > theEvaluand(
			this->thisEvaluandVector.pop_back().release()
		);
		assert( theEvaluand.get() );
		if( !theEvaluand->TakeElement( *this, theOperand ) ){
			this->thisEvaluandVector.push_back( theEvaluand );
		}
	}
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & theOperator )
{
	assert( !theOperator.IsEmpty() );
	Evaluation theEvaluation( *this );
	this->Evaluate( theEvaluation, theOperator );
	for( ; ; ){
		Operator theChildOperator;
		theEvaluation.GiveOperator( theChildOperator );
		if( theChildOperator.IsEmpty() ){ break; }
		this->Evaluate( theEvaluation, theChildOperator );
	}
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & theQueue )
{
	if( this->thisEvaluandVector.empty() ){
		this->thisOutput.TakeQuotedElements( theQueue );
		this->thisGaveElementToOutput = true;
	} else{
		std::auto_ptr< Evaluand > theEvaluand(
			this->thisEvaluandVector.pop_back().release()
		);
		assert( theEvaluand.get() );
		if( !theEvaluand->TakeQuotedElements( *this, theQueue ) ){
			this->thisEvaluandVector.push_back( theEvaluand );
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

template< typename TheOperator >
inline void Type_::Evaluate(
	Evaluation & theEvaluation,
	TheOperator & theOperator
)
{
	assert( !theOperator.IsEmpty() );
	switch( this->thisTranslator.Translate( theEvaluation, theOperator ) ){
	case 1:
		break;
	case 0:
		if( this->thisTranslator.Translate( theEvaluation, Operator() ) < 2 ){
			break;
		}
	default:
		theEvaluation.GiveOperands( *this );
		return;
	}

	// Flush the evaluation.
	if( this->thisGaveElementToOutput ){
		this->thisOutput.TakeElement( Separator::GetLineSeparator() );
	}
	if( !this->IsEmpty() ){
		// Starts with Operator; leading Operands would have been sent.
		this->GiveElements( this->thisOutput );
		this->thisOutput.TakeElement( Separator::GetLineSeparator() );
	}
	this->thisOutput.TakeElement( theOperator );
	theEvaluation.GiveOperands( this->thisOutput );
	this->thisGaveElementToOutput = true;
}

	#undef Type_

#else
	#include "om/evaluator.hpp"
#endif
