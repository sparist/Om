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

#if defined( Om_Lexicon_ )

	#include "om/evaluation.hpp"
	#include "om/literal.hpp"
	#include "om/system.hpp"

// MARK: Om::Lexicon

	#define Type_ \
	Om::Lexicon

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Lexicon_GetName_() );
}

// MARK: public (non-static)

inline Type_::Lexicon():
thisMap(),
thisFirstNode(),
thisLastNode()
{
}

inline Type_::Lexicon( Lexicon const & theLexicon ):
DefaultProgram< Lexicon >( theLexicon ),
thisMap(),
thisFirstNode(),
thisLastNode()
{
	for(
		Node const * theNode = theLexicon.thisFirstNode;
		theNode;
		theNode = theNode->GetNext()
	){
		std::auto_ptr< Node > theNewNode(
			new Node( *theNode )
		);
		assert( theNewNode.get() );
		theNewNode->LinkToBack(
			this->thisFirstNode,
			this->thisLastNode
		);

		std::string const & theString = theNewNode->GetOperator().GetString();
		this->thisMap.insert(
			theString,
			theNewNode
		);
	}
}

inline Type_ & Type_::operator =( Lexicon theLexicon )
{
	this->Swap( theLexicon );
	return( *this );
}

inline void Type_::BackGivePair( Queue & theQueue )
{
	if( this->thisLastNode ){
		Map::iterator const theIterator = this->thisMap.find( this->thisLastNode->GetOperator().GetString() );
		assert( this->thisMap.end() != theIterator );

		assert( this->thisFirstNode );
		Node::UnlinkLast(
			this->thisFirstNode,
			this->thisLastNode
		);

		Map::auto_type theNode = this->thisMap.release( theIterator );
		assert( theNode );
		theNode->GiveElements( theQueue );
	}
}

inline void Type_::Clear()
{
	this->thisMap.clear();
	this->thisFirstNode = this->thisLastNode = 0;
}

inline Om::Pair const & Type_::Find( Operator const & theOperator ) const
{
	typedef Map::const_iterator Iterator;
	Iterator theIterator(
		this->thisMap.find( theOperator.GetString() )
	);
	if( this->thisMap.end() == theIterator ){
		return( Pair::GetEmpty() );
	}
	return( *theIterator->second );
}

inline void Type_::FrontGivePair( Queue & theQueue )
{
	if( this->thisFirstNode ){
		Map::iterator const theIterator = this->thisMap.find( this->thisFirstNode->GetOperator().GetString() );
		assert( this->thisMap.end() != theIterator );

		assert( this->thisLastNode );
		Node::UnlinkFirst(
			this->thisFirstNode,
			this->thisLastNode
		);

		Map::auto_type theNode = this->thisMap.release( theIterator );
		assert( theNode );
		theNode->GiveElements( theQueue );
	}
}

inline std::auto_ptr<
	Om::Source< Om::Element const >
> Type_::GetElementRange() const
{
	return(
		std::auto_ptr<
			Source< Element const >
		>(
			new ElementRange( *this )
		)
	);
}

inline void Type_::GiveElements( Queue & theQueue )
{
	this->GiveElements(
		this->GetFirstNode(),
		theQueue
	);
	this->Clear();
}

inline void Type_::GiveElements( Queue & theQueue ) const
{
	this->GiveElements(
		this->GetFirstNode(),
		theQueue
	);
}

inline bool Type_::IsEmpty() const
{
	assert(
		!this->thisMap.empty() or
		(
			!this->thisFirstNode and
			!this->thisLastNode
		)
	);
	return( this->thisMap.empty() );
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
			if( !theParser ){
				return;
			}
			assert( Symbols::theEndOperandSymbol == *theParser );
			// Fall through.
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
	Literal theLiteral;
	theLiteral.ReadElements( theParser );
	this->TakeQuotedQueue( theLiteral );
}

inline void Type_::Swap( Lexicon & theLexicon )
{
	this->thisMap.swap( theLexicon.thisMap );
	boost::swap(
		this->thisFirstNode,
		theLexicon.thisFirstNode
	);
	boost::swap(
		this->thisLastNode,
		theLexicon.thisLastNode
	);
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & theOperand )
{
	assert( !theOperand.IsEmpty() );
	this->GetOperandTaker().TakeOperand( theOperand );
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & theOperator )
{
	assert( !theOperator.IsEmpty() );
	this->GetOperandTaker( theOperator );
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & theQueue )
{
	this->GetOperandTaker().TakeQuotedQueue( theQueue );
}

template< typename TheSeparator >
inline void Type_::TakeSeparator( TheSeparator & )
{
}

inline bool Type_::Translate(
	Evaluation & theEvaluation,
	Operator const & theOperator
) const
{
	Pair const & thePair = this->Find( theOperator );
	if( thePair.IsEmpty() ){
		return( false );
	}
	Operand const & theOperand = thePair.GetOperand();
	if( theOperand.IsEmpty() ){
		assert( thePair.GetOperator() == theOperator );
		return(
			System::Get().Translate(
				theEvaluation,
				theOperator
			)
		);
	}
	theEvaluation.TakeQueue( *theOperand.GetProgram() );
	return( true );
}

// MARK: private (static)

template< typename TheNode >
inline void Type_::GiveElements(
	TheNode * theFirstNode,
	Queue & theQueue
)
{
	if( theFirstNode ){
		for(
			;
			;
			theQueue.TakeElement( Separator::GetLineSeparator() )
		){
			assert(
				theFirstNode and
				!theFirstNode->IsEmpty()
			);
			theFirstNode->GiveElements( theQueue );
			if(
				!( theFirstNode = theFirstNode->GetNext() )
			){
				return;
			}
		}
	}
}

// MARK: private (non-static)

inline Type_::Node * Type_::GetFirstNode()
{
	return( this->thisFirstNode );
}

inline Type_::Node const * Type_::GetFirstNode() const
{
	return( this->thisFirstNode );
}

inline Type_::Node * Type_::GetLastNode()
{
	return( this->thisLastNode );
}

inline Type_::Node const * Type_::GetLastNode() const
{
	return( this->thisLastNode );
}

inline Type_::Node & Type_::GetOperandTaker()
{
	if(
		!this->thisLastNode or
		!this->thisLastNode->GetOperand().IsEmpty()
	){
		Operator const theOperator;
		return(
			this->GetOperandTaker( theOperator )
		);
	}
	return( *this->thisLastNode );
}

template< typename TheOperator >
inline Type_::Node & Type_::GetOperandTaker( TheOperator & theOperator )
{
	Node * theNode;
	std::string const & theString = theOperator.GetString();
	typename Map::iterator const theIterator = this->thisMap.find( theString );
	if( this->thisMap.end() == theIterator ){
		{
			std::auto_ptr< Node > theNewNode( new Node );
			assert( theNewNode.get() );
			theNode = theNewNode.get();
			this->thisMap.insert(
				theString,
				theNewNode
			);
		}
		theNode->TakeOperator( theOperator ); // May swap.
		theNode->LinkToBack(
			this->thisFirstNode,
			this->thisLastNode
		);
		assert( theNode->GetOperand().IsEmpty() );
	} else{
		theNode = &*theIterator->second;
		theNode->RelinkToBack(
			this->thisFirstNode,
			this->thisLastNode
		);
		theNode->ClearOperand();
	}
	return( *theNode );
}

	#undef Type_

// MARK: -
// MARK: Om::Lexicon::ElementRange

	#define Type_ \
	Om::Lexicon::ElementRange

// MARK: public (non-static)

inline Type_::ElementRange():
thisNode(),
thisOffset()
{
}

inline Type_::ElementRange( Lexicon const & theLexicon ):
thisNode( theLexicon.thisFirstNode ),
thisOffset(
	this->thisNode and
	thisNode->GetOperator().IsEmpty()
)
{
}

inline bool Type_::operator ==( ElementRange const & theElementRange ) const
{
	return(
		this->thisNode == theElementRange.thisNode and
		this->thisOffset == theElementRange.thisOffset
	);
}

inline bool Type_::operator !() const
{
	return( !this->thisNode );
}

inline Om::Element const & Type_::operator *() const
{
	assert( this->thisNode );
	switch( this->thisOffset ){
	case 0:
		assert( !this->thisNode->GetOperator().IsEmpty() );
		return( this->thisNode->GetOperator() );
	case 1:
		assert( !this->thisNode->GetOperand().IsEmpty() );
		return( this->thisNode->GetOperand() );
	default:
		return( Separator::GetLineSeparator() );
	}
}

inline void Type_::Pop()
{
	assert( this->thisNode );
	assert( !this->thisNode->IsEmpty() );
	switch( this->thisOffset ){
	case 0:
		if( !this->thisNode->GetOperand().IsEmpty() ){
			this->thisOffset = 1;
			return;
		}
		// Fall through.
	case 1:
		this->thisNode = this->thisNode->GetNext();
		this->thisOffset = 2;
		return;
	default:
		this->thisOffset = this->thisNode->GetOperator().IsEmpty();
		// Fall through.
	}
}

	#undef Type_

// MARK: -
// MARK: Om::Lexicon::Node

	#define Type_ \
	Om::Lexicon::Node

// MARK: public (static)

inline void Type_::UnlinkFirst(
	Node * & theFirstNode,
	Node * & theLastNode
)
{
	assert( theFirstNode );
	assert( theLastNode );
	assert( !theFirstNode->thisPriorNode );
	if( theFirstNode->thisNextNode ){
		theFirstNode = theFirstNode->thisNextNode;
		theFirstNode->thisPriorNode = 0;
	} else{
		assert( theLastNode == theFirstNode );
		theLastNode = theFirstNode = 0;
	}
}

inline void Type_::UnlinkLast(
	Node * & theFirstNode,
	Node * & theLastNode
)
{
	assert( theFirstNode );
	assert( theLastNode );
	assert( !theLastNode->thisNextNode );
	if( theLastNode->thisPriorNode ){
		theLastNode = theLastNode->thisPriorNode;
		theLastNode->thisNextNode = 0;
	} else{
		assert( theFirstNode == theLastNode );
		theFirstNode = theLastNode = 0;
	}
}

// MARK: public (non-static)

inline Type_::Node():
thisPriorNode(),
thisNextNode()
{
}

inline Type_ * Type_::GetNext()
{
	return( this->thisNextNode );
}

inline Type_ const * Type_::GetNext() const
{
	return( this->thisNextNode );
}

inline Type_ * Type_::GetPrior()
{
	return( this->thisPriorNode );
}

inline Type_ const * Type_::GetPrior() const
{
	return( this->thisPriorNode );
}

inline void Type_::LinkToBack(
	Node * & theFirstNode,
	Node * & theLastNode
)
{
	this->thisPriorNode = theLastNode;
	if( theLastNode ){
		theLastNode->thisNextNode = this;
	} else{
		assert( !theFirstNode );
		theFirstNode = this;
	}
	theLastNode = this;
}

inline void Type_::RelinkToBack(
	Node * & theFirstNode,
	Node * & theLastNode
)
{
	if( this->thisNextNode ){
		this->thisNextNode->thisPriorNode = this->thisPriorNode;
		if( this->thisPriorNode ){
			this->thisPriorNode->thisNextNode = this->thisNextNode;
		}

		this->LinkToBack(
			theFirstNode,
			theLastNode
		);
	}
}

	#undef Type_

// MARK: -
// MARK: boost

template<>
inline void boost::swap(
	Om::Lexicon & theFirst,
	Om::Lexicon & theSecond
)
{
	theFirst.Swap( theSecond );
}

#else

	#include "om/lexicon.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om
{
	// MARK: -
	SUITE( Lexicon )
	{
		TEST( Basic )
		{
			CHECK_EQUAL(
				(
					"{"
					"a{A}\n"
					"b{B}"
					"}"
				),
				System::Get().Evaluate( "lexicon {a {A} b {B}}" )
			);

			CHECK_EQUAL(
				(
					"{"
					"b\n"
					"a"
					"}"
				),
				System::Get().Evaluate( "->lexicon{b} lexicon{a}" )
			);
		}

		TEST( Copy )
		{
			CHECK_EQUAL(
				"{{a}}{a}",
				System::Get().Evaluate( "quote copy lexicon{a}" )
			);

			CHECK_EQUAL(
				(
					"{"
					"b\n"
					"a"
					"}{a}"
				),
				System::Get().Evaluate( "->lexicon{b}copy{a}" )
			);

			CHECK_EQUAL(
				(
					"{"
					"b\n"
					"a"
					"}{a}"
				),
				System::Get().Evaluate( "->lexicon{b}copy lexicon{a}" )
			);

			CHECK_EQUAL(
				(
					"{"
					"a\n"
					"b"
					"}{a}"
				),
				System::Get().Evaluate( "lexicon<-{b}copy lexicon{a}" )
			);

			CHECK_EQUAL(
				(
					"{"
					"a{A}\n"
					"b{B}\n"
					"c{C}"
					"}{"
					"a{A}\n"
					"b{B}"
					"}"
				),
				System::Get().Evaluate(
					"lexicon<- {{C}} lexicon<- {c} "
					"copy lexicon {a {A} b {B}}"
				)
			);
		}

		TEST( Equality )
		{
			// Positive match
			CHECK_EQUAL(
				(
					"{"
					"{"
					"a{b}\n"
					"c{d}"
					"}"
					"}"
				),
				System::Get().Evaluate(
					"= lexicon{a{b}c{d}} {"
					"a{b}\n"
					"c{d}"
					"}"
				)
			);

			// Positive match
			CHECK_EQUAL(
				"{{a{b}}}",
				System::Get().Evaluate( "= lexicon{a{b}} {a{b}}" )
			);

			// Positive match
			CHECK_EQUAL(
				"{{{b}}}",
				System::Get().Evaluate( "= lexicon{{b}} {{b}}" )
			);

			// Negative match
			CHECK_EQUAL(
				"{}",
				System::Get().Evaluate( "= lexicon{a{b}} {a{c}}" )
			);

			// Empty match
			CHECK_EQUAL(
				"{}",
				System::Get().Evaluate( "= lexicon{} {a{b}}" )
			);

			// Empty match
			CHECK_EQUAL(
				"{{}}",
				System::Get().Evaluate( "= lexicon{} {}" )
			);
		}

		TEST( Read )
		{
			char const theCode[] = "0\n\t {1\n\t {2\n\t } 3\n\t } 4\n\t";
			std::string theResult;
			{
				Sinks::CodePointSink<
					std::back_insert_iterator< std::string >
				> theCodePointSink(
					std::back_inserter( theResult )
				);
				Writer theWriter( theCodePointSink );

				Sources::CodePointSource<> theCodePointSource( theCode );
				Parser theParser( theCodePointSource );
				Lexicon theLexicon;
				theLexicon.ReadElements( theParser );
				theLexicon.GiveElements( theWriter );
			}
			CHECK_EQUAL(
				(
					"0{1\n\t {2\n\t } 3\n\t }\n"
					"4"
				),
				theResult
			);
		}
	}
}

	#endif

#endif
