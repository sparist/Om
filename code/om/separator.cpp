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
#if defined( Om_Separator_ )

// MARK: Om::Separator

	#define Type_ Om::Separator

// MARK: public (static)

inline Type_ const & Type_::GetLineSeparator()
{
	static Separator const theSeparator( Symbols::theLineSeparatorSymbol );
	return( theSeparator );
}

inline char const * Type_::GetName()
{
	return( Om_Separator_GetName_() );
}

// MARK: public (non-static)

inline Type_::Separator()
{
}

inline Type_::Separator( Source< CodePoint const > & theCodePointSource )
:
DefaultAtom()
{
	for( ; theCodePointSource; theCodePointSource.Pop() ){
		switch( *theCodePointSource ){
		default:
			return;
		Om_Symbols_SeparatorSymbol_GetCases_():
			this->thisString.push_back(
				static_cast< char >( *theCodePointSource )
			);
		}
	}
}

inline Type_::Separator( Symbols::SeparatorSymbol const theSeparatorSymbol )
:
DefaultAtom( static_cast< char >( theSeparatorSymbol ) )
{
	assert(
		Symbols::theSpaceSeparatorSymbol == theSeparatorSymbol ||
		Symbols::theLineSeparatorSymbol == theSeparatorSymbol ||
		Symbols::theTabSeparatorSymbol == theSeparatorSymbol
	);
}

inline Type_ & Type_::operator =( Separator theSeparator )
{
	this->Swap( theSeparator );
	return( *this );
}

inline void Type_::ReadElements( Parser & theParser )
{
	for( ; theParser; theParser.Pop() ){
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
			continue;
		Om_Symbols_SeparatorSymbol_GetCases_():
			this->thisString.push_back( static_cast< char >( *theParser ) );
		}
	}
}

inline void Type_::ReadQuotedElements( Parser & theParser )
{
	for( ; theParser; theParser.Pop() ){}
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
inline void Type_::TakeSeparator( TheSeparator & theSeparator )
{
	assert( !theSeparator.IsEmpty() );
	this->thisString.append( theSeparator.thisString );
}

inline void Type_::TakeSeparatorSymbol(
	Symbols::SeparatorSymbol const theSymbol
)
{
	this->thisString.push_back( static_cast< char >( theSymbol ) );
}

	#undef Type_

// MARK: -
// MARK: boost

template<>
inline void boost::swap( Om::Separator & theFirst, Om::Separator & theSecond )
{
	theFirst.Swap( theSecond );
}

#else
	#include "om/separator.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/writer.hpp"
		#include "UnitTest++.h"

namespace Om
{
	// MARK: -
	SUITE( Separator )
	{
		TEST( Read )
		{
			char const theCode[] = "0\n\t {1\n\t {2\n\t } 3\n\t } {4\n\t} 5\n";
			std::string theResult;
			{
				Sinks::CodePointSink<
					std::back_insert_iterator< std::string >
				> theCodePointSink( std::back_inserter( theResult ) );
				Writer theWriter( theCodePointSink );

				Sources::CodePointSource<> theCodePointSource( theCode );
				Parser theParser( theCodePointSource );
				Separator theSeparator;
				theSeparator.ReadElements( theParser );
				theSeparator.GiveElements( theWriter );
			}
			CHECK_EQUAL( "\n\t   \n", theResult );
		}
	}
}

	#endif

#endif
