/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Operator_ )

	#include "om/operand.hpp"
	#include "om/separator.hpp"
	#include "om/sinks/code_point_sink.hpp"
	#include "om/sources/code_point_source.hpp"
	#include "om/sources/code_point_string_back_source.hpp"
	#include "om/sources/code_point_string_front_source.hpp"
	#include "om/writer.hpp"

// MARK: Om::Operator

	#define Type_ \
	Om::Operator

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operator_GetName_() );
}

// MARK: public (non-static)

inline Type_::Operator()
{
}

inline Type_::Operator( std::string const & theString )
{
	boost::locale::normalize(
		theString,
		boost::locale::norm_nfd
	).swap( this->thisString );
}

inline Type_::Operator( char const theCodeUnitIterator[] )
{
	boost::locale::normalize(
		theCodeUnitIterator,
		boost::locale::norm_nfd
	).swap( this->thisString );
}

inline Type_::Operator(
	Source< CodePoint const > & theCodePointSource
)
{
	std::string theString;
	std::back_insert_iterator< std::string > theInserter( theString );
	for(
		;
		theCodePointSource;
		theCodePointSource.Pop()
	){
		switch( *theCodePointSource ){
		Om_Symbols_OperandSymbol_GetCases_():
			// Fall through.
		Om_Symbols_SeparatorSymbol_GetCases_():
			break;
		case Symbols::theEncodeOperatorSymbol:
			theCodePointSource.Pop();
			if( !theCodePointSource ){
				theString.push_back( Symbols::theEndOperandSymbol );
				break;
			}
			// Fall through.
		default:
			Utf8::encode(
				*theCodePointSource,
				theInserter
			);
			continue;
		}
		break;
	}
	boost::locale::normalize(
		theString,
		boost::locale::norm_nfd
	).swap( this->thisString );
}

inline Type_::Operator( Symbols::OperandSymbol const theOperandSymbol )
:
DefaultAtom< Operator >(
	static_cast< char >( theOperandSymbol )
)
{
}

inline Type_::Operator( Symbols::OperatorSymbol const theOperatorSymbol )
:
DefaultAtom< Operator >(
	static_cast< char >( theOperatorSymbol )
)
{
}

inline Type_::Operator( Symbols::SeparatorSymbol const theSeparatorSymbol )
:
DefaultAtom< Operator >(
	static_cast< char >( theSeparatorSymbol )
)
{
}

inline Type_ & Type_::operator =( Operator theOperator )
{
	this->Swap( theOperator );
	return( *this );
}

inline void Type_::BackGiveCodePoint( Queue & theQueue )
{
	if( !this->thisString.empty() ){
		Operator theOperator;
		{
			std::string & theString = theOperator.thisString;
			{
				Sources::CodePointStringBackSource< std::string::const_iterator > theCodePointStringRange(
					this->thisString.begin(),
					this->thisString.end()
				);
				assert( theCodePointStringRange );
				theCodePointStringRange->swap( theString );
			}
			assert( !theString.empty() );
			this->thisString.erase( this->thisString.size() - theString.size() );
		}
		theQueue.TakeElement( theOperator );
	}
}

template< boost::locale::boundary::boundary_type theSegment >
inline void Type_::BackGiveSegment( Queue & theQueue )
{
	if( !this->thisString.empty() ){
		Operator theOperator;
		{
			std::string & theString = theOperator.thisString;
			{
				typedef boost::locale::boundary::segment_index< std::string::const_iterator > SegmentCollection;

				typedef SegmentCollection::const_iterator SegmentIterator;

				SegmentCollection const theSegmentCollection(
					static_cast< boost::locale::boundary::boundary_type >( theSegment ),
					this->thisString.begin(),
					this->thisString.end()
				);

				SegmentIterator theSegmentIterator( theSegmentCollection.end() );
				assert( theSegmentCollection.begin() != theSegmentIterator );
				--theSegmentIterator;
				theSegmentIterator->str().swap( theString );
			}
			assert( !theString.empty() );
			this->thisString.erase( this->thisString.size() - theString.size() );
		}
		theQueue.TakeElement( theOperator );
	}
}

template< typename TheQueue >
inline void Type_::Decode( TheQueue & theQueue ) const
{
	Sources::CodePointSource< std::string::const_iterator > theCodePointSource(
		this->thisString.begin(),
		this->thisString.end()
	);
	Parser theParser( theCodePointSource );
	theQueue.ReadElements( theParser );
}

template< typename TheQueue >
inline void Type_::Encode( TheQueue & theQueue )
{
	this->thisString.clear();
	Sinks::CodePointSink<
		std::back_insert_iterator< std::string >
	> theCodePointSink(
		std::back_inserter( this->thisString )
	);
	Writer theWriter( theCodePointSink );
	theQueue.GiveElements( theWriter );
}

inline void Type_::FrontGiveCodePoint( Queue & theQueue )
{
	if( !this->thisString.empty() ){
		Operator theOperator;
		{
			std::string & theString = theOperator.thisString;
			{
				Sources::CodePointStringFrontSource< std::string::const_iterator > theCodePointStringRange(
					this->thisString.begin(),
					this->thisString.end()
				);
				assert( theCodePointStringRange );
				theCodePointStringRange->swap( theString );
			}
			assert( !theString.empty() );
			this->thisString.erase(
				0,
				theString.size()
			);
		}
		theQueue.TakeElement( theOperator );
	}
}

template< boost::locale::boundary::boundary_type theSegment >
inline void Type_::FrontGiveSegment( Queue & theQueue )
{
	if( !this->thisString.empty() ){
		Operator theOperator;
		{
			std::string & theString = theOperator.thisString;
			{
				typedef boost::locale::boundary::segment_index< std::string::const_iterator > SegmentCollection;

				SegmentCollection const theSegmentCollection(
					static_cast< boost::locale::boundary::boundary_type >( theSegment ),
					this->thisString.begin(),
					this->thisString.end()
				);

				SegmentCollection::const_iterator const theSegmentIterator( theSegmentCollection.begin() );
				assert( theSegmentCollection.end() != theSegmentIterator );
				theSegmentIterator->str().swap( theString );
			}
			assert( !theString.empty() );
			this->thisString.erase(
				0,
				theString.size()
			);
		}
		theQueue.TakeElement( theOperator );
	}
}

inline void Type_::Normalize()
{
	boost::locale::normalize(
		this->thisString,
		boost::locale::norm_nfkd
	).swap( this->thisString );
}

inline void Type_::ReadElements( Parser & theParser )
{
	while( theParser ){
		switch( *theParser ){
		case Symbols::theEndOperandSymbol:
			// Fall through.
		case Symbols::theStartOperandSymbol:
			// Fall through.
		Om_Symbols_SeparatorSymbol_GetCases_():
			this->thisString.push_back(
				static_cast< char >( *theParser )
			);
			theParser.Pop();
			continue;
		}
		Operator theOperator( theParser );
		this->TakeOperator( theOperator );
	}
}

inline void Type_::ReadQuotedElements( Parser & theParser )
{
	this->thisString.push_back( Symbols::theStartOperandSymbol );
	this->ReadElements( theParser );
	this->thisString.push_back( Symbols::theEndOperandSymbol );
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & theOperand )
{
	assert( !theOperand.IsEmpty() );
	this->TakeQuotedQueue( *theOperand.GetProgram() );
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & theOperator )
{
	assert(
		typeid( theOperator ) == typeid( *this )
	);
	assert( !theOperator.IsEmpty() );
	assert(
		boost::locale::normalize(
			theOperator.thisString,
			boost::locale::norm_nfd
		) == theOperator.thisString &&
		"Operator strings must be NFC normalized."
	);

	if( this->IsEmpty() ){
		this->Take( theOperator );
		return;
	}

	this->thisString.append( theOperator.thisString );

	// Normalization is required even when combining two NFD-normalized strings.
	// TODO: Optimize to only do an incremental normalization at the boundary.
	boost::locale::normalize(
		this->thisString,
		boost::locale::norm_nfd
	).swap( this->thisString );
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & theQueue )
{
	this->thisString.push_back( Symbols::theStartOperandSymbol );
	theQueue.GiveElements( *this );
	this->thisString.push_back( Symbols::theEndOperandSymbol );
}

template< typename TheSeparator >
inline void Type_::TakeSeparator( TheSeparator & theSeparator )
{
	assert( !theSeparator.IsEmpty() );
	this->thisString.append( theSeparator.GetString() );
}

	#undef Type_

// MARK: -
// MARK: boost

template<>
inline void boost::swap(
	Om::Operator & theFirst,
	Om::Operator & theSecond
)
{
	theFirst.Swap( theSecond );
}

#else

	#include "om/operator.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

namespace Om
{
	// MARK: -
	SUITE( Operator )
	{
		TEST( Basic )
		{
			CHECK_EQUAL(
				"{a` `{b`}}",
				System::Get().Evaluate( "operator{a {b}}" )
			);
		}

		TEST( Equality )
		{
			// Positive match
			CHECK_EQUAL(
				"{{test` `{ing`}}}",
				System::Get().Evaluate( "= operator{test {ing}} {test` `{ing`}}" )
			);

			// Positive match
			CHECK_EQUAL(
				"{{a`{b`}`{c`}`\nd`{e`}}}",
				System::Get().Evaluate( "= operator{a{b}{c}\nd{e}} {a`{b`}`{c`}`\nd`{e`}}" )
			);

			// Negative match
			CHECK_EQUAL(
				"{}",
				System::Get().Evaluate( "= operator{a{b}{c}} {a`{b`}`{d`}}" )
			);

			// Empty match
			CHECK_EQUAL(
				"{}",
				System::Get().Evaluate( "= operator{} {a{b}{c}}" )
			);

			// Empty match
			CHECK_EQUAL(
				"{{}}",
				System::Get().Evaluate( "= operator{} {}" )
			);
		}

		TEST( TakeQuotedElements )
		{
			Operator theOperator;
			{
				Literal theLiteral;
				{
					Sources::CodePointSource<> theCodePointSource( "a{b{c}}" );
					Parser theParser( theCodePointSource );
					theLiteral.ReadElements( theParser );
				}
				theOperator.TakeQuotedQueue( theLiteral );
				assert( theLiteral.IsEmpty() );
			}
			CHECK_EQUAL(
				"{a{b{c}}}",
				theOperator.GetString()
			);
		}

		TEST( Normalization )
		{
			// Test combining character reordering under NFD.
			Operator theLeftOperator( "s\xCC\x87" );
			Operator theRightOperator( "\xCC\xA3" );
			theLeftOperator.TakeElement( theRightOperator );
			CHECK_EQUAL(
				"s\xCC\xA3\xCC\x87",
				theLeftOperator.GetString()
			);
		}

		TEST( Read )
		{
			char const theCode[] = "0\n\t {1\n\t {2\n\t } 3\n\t } {4\n\t} 5\n";
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
				Operator theOperator;
				theOperator.ReadElements( theParser );
				theOperator.GiveElements( theWriter );
			}
			CHECK_EQUAL(
				(
					"0`\n"
					"`\t` `{1`\n"
					"`\t` `{2`\n"
					"`\t` `}` 3`\n"
					"`\t` `}` `{4`\n"
					"`\t`}` 5`\n"
				),
				theResult
			);
		}
	}
}

	#endif

#endif
