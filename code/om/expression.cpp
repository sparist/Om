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

#if !defined( Om_Expression_ )

	#include "om/expression.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"

		#if !defined( Om_Macros_Precompilation_ )

			#include "UnitTest++.h"

		#endif

namespace Om {

	SUITE( Expression ) {

		TEST( General ) {
			CHECK_EQUAL(
				(
					"{"
					"{a}{b}\n"
					"c{d}"
					"}"
				),
				System::Get().Evaluate( "evaluate {{a}{b}c{d}}" )
			);

			CHECK_EQUAL(
				"{c{d}{a}{b}}",
				System::Get().Evaluate( "evaluate {c{d}{a}{b}}" )
			);

			CHECK_EQUAL(
				(
					"{"
					"a{b}{c}\n"
					"d{e}{f}"
					"}"
				),
				System::Get().Evaluate( "evaluate {a{b}{c}d{e}{f}}" )
			);

			CHECK_EQUAL(
				"{c}",
				System::Get().Evaluate( "evaluate {c}" )
			);

			CHECK_EQUAL(
				"{{d}}",
				System::Get().Evaluate( "evaluate {{d}}" )
			);

			CHECK_EQUAL(
				"{}",
				System::Get().Evaluate( "evaluate {}" )
			);
		}

		TEST( Equality ) {
			// Positive match
			CHECK_EQUAL(
				(
					"{"
					"{"
					"a{b}{c}\n"
					"d{e}"
					"}"
					"}"
				),
				System::Get().Evaluate(
					"= expression{a{b}{c}d{e}} {"
					"a{b}{c}\n"
					"d{e}"
					"}"
				)
			);

			// Positive match
			CHECK_EQUAL(
				"{{a{b}{c}}}",
				System::Get().Evaluate( "= expression{a{b}{c}} {a{b}{c}}" )
			);

			// Positive match
			CHECK_EQUAL(
				"{{a{b}}}",
				System::Get().Evaluate( "= expression{a{b}} {a{b}}" )
			);

			// Positive match
			CHECK_EQUAL(
				"{{a}}",
				System::Get().Evaluate( "= expression{a} {a}" )
			);

			// Positive match
			CHECK_EQUAL(
				"{{{a}}}",
				System::Get().Evaluate( "= expression{{a}}{{a}}" )
			);

			// Negative match
			CHECK_EQUAL(
				"{}",
				System::Get().Evaluate( "= expression{a{b}{c}} {A{B}{C}}" )
			);

			// Negative match
			CHECK_EQUAL(
				"{}",
				System::Get().Evaluate( "= expression{} {a{b}{c}}" )
			);

			// Positive empty match
			CHECK_EQUAL(
				"{{}}",
				System::Get().Evaluate( "= expression{} {}" )
			);
		}

		TEST( Read ) {
			char const theCode[] = (
				"0\n"
				"\t {1\n"
				"\t {2\n"
				"\t } 3\n"
				"\t } {4\n"
				"\t} 5\n"
			);
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
				Expression theExpression;
				theExpression.ReadElements( theParser );
				theExpression.GiveElements( theWriter );
			}
			CHECK_EQUAL(
				(
					"0{1\n"
					"\t {2\n"
					"\t } 3\n"
					"\t }{4\n"
					"\t}\n"
					"5"
				),
				theResult
			);
		}

	}

}

	#endif

#else

	#include "om/literal.hpp"

	#if !defined( Om_Macros_Precompilation_ )

		#include "boost/ref.hpp"

	#endif

// MARK: - Om::Expression

	#define Type_ \
	Om::Expression

// MARK: public (static)

inline char const * Type_::GetName() {
	return(
		Om_Expression_GetName_()
	);
}

// MARK: public (non-static)

inline Type_::Expression():
thisFormDeque() {}

inline Type_ & Type_::operator =( Expression theExpression ) {
	this->Swap( theExpression );
	return( *this );
}

inline void Type_::BackGiveForm( Queue & theQueue ) {
	if(
		!this->thisFormDeque.empty()
	) {
		this->thisFormDeque.back().GiveElements( theQueue );
		this->thisFormDeque.pop_back();
	}
}

inline void Type_::BackGiveTerm( Queue & theQueue ) {
	if(
		!this->thisFormDeque.empty()
	) {
		Form & theForm = this->thisFormDeque.back();
		if(
			theForm.BackGiveTerm( theQueue )
		) {
			assert(
				theForm.IsEmpty()
			);
			this->thisFormDeque.pop_back();
		}
	}
}

inline void Type_::BackPopTerm() {
	assert(
		!this->thisFormDeque.empty()
	);
	Form & theForm = this->thisFormDeque.back();
	if(
		theForm.BackPopTerm()
	) {
		assert(
			theForm.IsEmpty()
		);
		this->thisFormDeque.pop_back();
	}
}

template< typename TheOperand >
inline void Type_::BackTakeOperand( TheOperand & theOperand ) {
	this->GetBackTaker().BackTakeOperand( theOperand );
}

template< typename TheOperator >
inline void Type_::BackTakeOperator( TheOperator & theOperator ) {
	assert(
		!theOperator.IsEmpty()
	);
	this->thisFormDeque.push_back(
		Form()
	);
	this->thisFormDeque.back().TakeOperator( theOperator );
}

template< typename TheQueue >
inline void Type_::BackTakeQuotedQueue( TheQueue & theQueue ) {
	this->GetBackTaker().BackTakeQuotedQueue( theQueue );
}

inline void Type_::Clear() {
	this->thisFormDeque.clear();
}

inline void Type_::FrontGiveForm( Queue & theQueue ) {
	if(
		!this->thisFormDeque.empty()
	) {
		this->thisFormDeque.front().GiveElements( theQueue );
		this->thisFormDeque.pop_front();
	}
}

inline void Type_::FrontGiveTerm( Queue & theQueue ) {
	if(
		!this->thisFormDeque.empty()
	) {
		Form & theForm = this->thisFormDeque.front();
		if(
			theForm.FrontGiveTerm( theQueue )
		) {
			assert(
				theForm.IsEmpty()
			);
			this->thisFormDeque.pop_front();
		}
	}
}

inline void Type_::FrontPopTerm() {
	assert(
		!this->thisFormDeque.empty()
	);
	Form & theForm = this->thisFormDeque.front();
	if(
		theForm.FrontPopTerm()
	) {
		assert(
			theForm.IsEmpty()
		);
		this->thisFormDeque.pop_front();
	}
}

template< typename TheOperand >
inline void Type_::FrontTakeOperand( TheOperand & theOperand ) {
	this->GetFrontTaker().FrontTakeOperand( theOperand );
}

template< typename TheOperator >
inline void Type_::FrontTakeOperator( TheOperator & theOperator ) {
	assert(
		!theOperator.IsEmpty()
	);
	this->GetFrontTaker().TakeOperator( theOperator );
}

template< typename TheQueue >
inline void Type_::FrontTakeQuotedQueue( TheQueue & theQueue ) {
	this->GetFrontTaker().FrontTakeQuotedQueue( theQueue );
}

inline std::auto_ptr<
	Om::Source< Om::Element const >
> Type_::GetElementRange() const {
	return(
		std::auto_ptr<
			Source< Element const >
		>(
			new ElementRange( *this )
		)
	);
}

inline void Type_::GiveElements( Queue & theQueue ) {
	this->GiveElements(
		theQueue,
		this->thisFormDeque.begin(),
		this->thisFormDeque.end()
	);
	this->Clear();
}

inline void Type_::GiveElements( Queue & theQueue ) const {
	this->GiveElements(
		theQueue,
		this->thisFormDeque.begin(),
		this->thisFormDeque.end()
	);
}

inline bool Type_::IsEmpty() const {
	return(
		this->thisFormDeque.empty()
	);
}

inline void Type_::ReadElements( Parser & theParser ) {
	while( theParser ) {
		assert( Symbols::theEndOperandSymbol != *theParser );
		switch( *theParser ) {
		case Symbols::theStartOperandSymbol:
			theParser.Pop();
			{
				// Ensure that this does not resolve to the copy constructor.
				Source< CodePoint const > & theCodePointSource = theParser;

				Parser theOperandParser( theCodePointSource );
				this->ReadQuotedElements( theOperandParser );
			}
			if( !theParser ) {
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

inline void Type_::ReadQuotedElements( Parser & theParser ) {
	Literal theLiteral;
	theLiteral.ReadElements( theParser );
	this->TakeQuotedQueue( theLiteral );
}

inline void Type_::Swap( Expression & theExpression ) {
	this->thisFormDeque.swap( theExpression.thisFormDeque );
}

inline void Type_::TakeElements( Expression & theExpression ) {
	if(
		!theExpression.IsEmpty()
	) {
		if(
			this->IsEmpty()
		) {
			this->Take( theExpression );
		} else {
			FormDeque & theFormDeque = theExpression.thisFormDeque;
			assert(
				!theFormDeque.empty()
			);

			FormDeque::iterator theCurrent = theFormDeque.begin();
			if(
				theCurrent->GetOperator().IsEmpty()
			) {
				theFormDeque.front().GiveElements( *this );
				theFormDeque.pop_front();
				if(
					theFormDeque.empty()
				) {
					return;
				}
				theCurrent = theFormDeque.begin();
			}

			FormDeque::iterator const theEnd = theFormDeque.end();
			assert( theEnd != theCurrent );
			do {
				assert(
					!theCurrent->GetOperator().IsEmpty()
				);
				this->thisFormDeque.push_back(
					Form()
				);
				this->thisFormDeque.back().Swap( *theCurrent );
			} while( theEnd != ++theCurrent );

			Expression().Swap( theExpression );
		}
	}
}

inline void Type_::TakeElements( Expression const & theExpression ) {
	if(
		!theExpression.IsEmpty()
	) {
		if(
			this->IsEmpty()
		) {
			this->Take( theExpression );
		} else {
			FormDeque const & theFormDeque = theExpression.thisFormDeque;
			assert(
				!theFormDeque.empty()
			);

			FormDeque::const_iterator const theEnd = theFormDeque.end();
			FormDeque::const_iterator theCurrent = theFormDeque.begin();
			assert( theEnd != theCurrent );
			if(
				theCurrent->GetOperator().IsEmpty()
			) {
				theFormDeque.front().GiveElements( *this );
				++theCurrent;
			}
			this->thisFormDeque.insert(
				this->thisFormDeque.end(),
				theCurrent,
				theEnd
			);
		}
	}
}

inline void Type_::TakeElements( Queue & theQueue ) {
	if(
		typeid( theQueue ) == typeid( Expression )
	) {
		this->TakeElements(
			static_cast< Expression & >( theQueue )
		);
	} else {
		theQueue.GiveElements( *this );
	}
}

inline void Type_::TakeElements( Queue const & theQueue ) {
	if(
		typeid( theQueue ) == typeid( Expression const )
	) {
		this->TakeElements(
			static_cast< Expression const & >( theQueue )
		);
	} else {
		theQueue.GiveElements( *this );
	}
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & theOperand ) {
	assert(
		!theOperand.IsEmpty()
	);
	this->BackTakeOperand( theOperand );
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & theOperator ) {
	assert(
		!theOperator.IsEmpty()
	);
	this->BackTakeOperator( theOperator );
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & theQueue ) {
	this->BackTakeQuotedQueue( theQueue );
}

template< typename TheSeparator >
inline void Type_::TakeSeparator( TheSeparator & ) {}

// MARK: private (static)

template< typename TheFormIterator >
inline void Type_::GiveElements(
	Queue & theQueue,
	TheFormIterator theCurrent,
	TheFormIterator const theEnd
) {
	if( theEnd != theCurrent ) {
		for(
			;
			;
			theQueue.TakeElement(
				Separator::GetLineSeparator()
			)
		) {
			assert(
				!theCurrent->IsEmpty()
			);
			theCurrent->GiveElements( theQueue );
			if( theEnd == ++theCurrent ) {
				return;
			}
		}
	}
}

// MARK: private (non-static)

inline Om::Form & Type_::GetBackTaker() {
	if(
		this->thisFormDeque.empty()
	) {
		this->thisFormDeque.push_back(
			Form()
		);
	}
	return(
		this->thisFormDeque.back()
	);
}

inline Om::Form & Type_::GetFrontTaker() {
	if(
		this->thisFormDeque.empty() ||
		!this->thisFormDeque.front().GetOperator().IsEmpty()
	) {
		this->thisFormDeque.push_front(
			Form()
		);
	}
	return(
		this->thisFormDeque.front()
	);
}

	#undef Type_

// MARK: - Om::Expression::FormRange

	#define Type_ \
	Om::Expression::FormRange

// MARK: public (non-static)

inline Type_< Om::Form >::FormRange( Expression & theExpression ):
Sources::CollectionFrontSource<
	Form,
	FormDeque::iterator
>( theExpression.thisFormDeque ) {}

inline Type_< Om::Form const >::FormRange( Expression const & theExpression ):
Sources::CollectionFrontSource<
	Form const,
	FormDeque::const_iterator
>( theExpression.thisFormDeque ) {}

	#undef Type_

// MARK: - Om::Expression::ElementRange

	#define Type_ \
	Om::Expression::ElementRange

// MARK: public (non-static)

inline Type_::ElementRange( Expression const & theExpression ):
thisFormIterator(
	theExpression.thisFormDeque.begin()
),
thisFormEnd(
	theExpression.thisFormDeque.end()
),
thisFormElementRange() {
	if( this->thisFormEnd != this->thisFormIterator ) {
		this->thisFormElementRange = boost::in_place(
			boost::ref( *this->thisFormIterator )
		);
		assert( *this->thisFormElementRange );
	}
}

inline bool Type_::operator ==( ElementRange const & theRange ) const {
	return(
		( this->thisFormElementRange == theRange.thisFormElementRange ) &&
		( this->thisFormIterator == theRange.thisFormIterator )
	);
}

inline bool Type_::operator !() const {
	return( !this->thisFormElementRange );
}

inline Om::Element const & Type_::operator *() const {
	assert( this->thisFormElementRange );
	return(
		( *this->thisFormElementRange )?
		( **this->thisFormElementRange ):
		Separator::GetLineSeparator()
	);
}

inline void Type_::End() {
	this->thisFormElementRange = boost::none;
}

inline void Type_::Pop() {
	assert( this->thisFormElementRange );
	assert( this->thisFormEnd != this->thisFormIterator );
	if( *this->thisFormElementRange ) {
		this->thisFormElementRange->Pop();
		if( !*this->thisFormElementRange ) {
			if( this->thisFormEnd == ++this->thisFormIterator ) {
				this->End();
			}
		}
	} else {
		this->thisFormElementRange = boost::in_place(
			boost::ref( *this->thisFormIterator )
		);
		assert( *this->thisFormElementRange );
	}
}

	#undef Type_

// MARK: - boost

template<>
inline void boost::swap(
	Om::Expression & theFirst,
	Om::Expression & theSecond
) {
	theFirst.Swap( theSecond );
}

#endif
