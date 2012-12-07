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

	#include "om/evaluation.hpp"
	#include "om/expansion.hpp"
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
thisEvaluationVector(),
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
	this->thisEvaluationVector.clear();
}

inline Om::Translator const & Type_::GetTranslator() const
{
	return( this->thisTranslator );
}

inline void Type_::GiveElements( Queue & theQueue )
{
	this->GiveElements(
		this->thisEvaluationVector.begin(),
		this->thisEvaluationVector.end(),
		theQueue
	);
	this->Clear();
}

inline void Type_::GiveElements( Queue & theQueue ) const
{
	this->GiveElements(
		this->thisEvaluationVector.begin(),
		this->thisEvaluationVector.end(),
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
	return( this->thisEvaluationVector.empty() );
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
	if( this->thisEvaluationVector.empty() ){
		this->thisOutput.ReadQuotedElements( theParser );
		this->thisGaveElementToOutput = true;
	} else{
		std::auto_ptr< Evaluation > theEvaluation(
			this->thisEvaluationVector.pop_back().release()
		);
		assert( theEvaluation.get() );
		if( !theEvaluation->ReadQuotedElements( *this, theParser ) ){
			this->thisEvaluationVector.push_back( theEvaluation );
		}
	}
}

template< typename TheEvaluation >
inline void Type_::TakeEvaluation( std::auto_ptr< TheEvaluation > theEvaluation )
{
	this->thisEvaluationVector.push_back( theEvaluation );
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & theOperand )
{
	if( this->thisEvaluationVector.empty() ){
		this->thisOutput.TakeElement( theOperand );
		this->thisGaveElementToOutput = true;
	} else{
		std::auto_ptr< Evaluation > theEvaluation(
			this->thisEvaluationVector.pop_back().release()
		);
		assert( theEvaluation.get() );
		if( !theEvaluation->TakeElement( *this, theOperand ) ){
			this->thisEvaluationVector.push_back( theEvaluation );
		}
	}
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & theOperator )
{
	assert( !theOperator.IsEmpty() );
	Expansion theExpansion( *this );
	this->EvaluateOperator( theExpansion, theOperator );
	for( ; ; ){
		Operator theChildOperator;
		theExpansion.GiveOperator( theChildOperator );
		if( theChildOperator.IsEmpty() ){ break; }
		this->EvaluateOperator( theExpansion, theChildOperator );
	}
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & theQueue )
{
	if( this->thisEvaluationVector.empty() ){
		this->thisOutput.TakeQuotedElements( theQueue );
		this->thisGaveElementToOutput = true;
	} else{
		std::auto_ptr< Evaluation > theEvaluation(
			this->thisEvaluationVector.pop_back().release()
		);
		assert( theEvaluation.get() );
		if( !theEvaluation->TakeQuotedElements( *this, theQueue ) ){
			this->thisEvaluationVector.push_back( theEvaluation );
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
inline void Type_::EvaluateOperator(
	Expansion & theExpansion,
	TheOperator & theOperator
)
{
	assert( !theOperator.IsEmpty() );
	switch( this->thisTranslator.Translate( theExpansion, theOperator ) ){
	case 1:
		break;
	case 0:
		if( this->thisTranslator.Translate( theExpansion, Operator() ) < 2 ){
			break;
		}
	default:
		theExpansion.GiveOperands( *this );
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
	theExpansion.GiveOperands( this->thisOutput );
	this->thisGaveElementToOutput = true;
}

	#undef Type_

#else
	#include "om/evaluator.hpp"
#endif
