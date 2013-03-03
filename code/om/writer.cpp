/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Writer_ )

	#include "om/writer.hpp"

	#if defined( Om_Macros_Test_ )

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE( WriterTest )

		BOOST_AUTO_TEST_CASE( GeneralTest ) {
			char const theCode[] = "\n\t {\n\t {\n\t }\n\t }\n\t";
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
				theWriter.ReadElements( theParser );
			}
			BOOST_CHECK_EQUAL(
				"\n\t {\n\t {\n\t }\n\t }\n\t",
				theResult
			);
		}

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#include "om/null.hpp"
	#include "om/operator.hpp"
	#include "om/sink.hpp"
	#include "om/sources/code_point_source.hpp"
	#include "om/symbols/operator_symbol.hpp"
	#include "om/symbols/separator_symbol.hpp"

// MARK: - Om::Writer

	#define Type_ \
	Om::Writer

// MARK: public (non-static)

inline Type_::Writer(
	Sink< CodePoint const > & theCodePointSink
):
thisCodePointSink( theCodePointSink ) {}

inline bool Type_::operator ==( Program const & theProgram ) const {
	return(
		theProgram.IsEmpty()
	);
}

inline void Type_::Clear() {}

inline void Type_::GiveElements( Queue & ) {}

inline void Type_::GiveElements( Queue & ) const {}

inline std::auto_ptr< Om::Program > Type_::GiveProgram() {
	return(
		std::auto_ptr< Program >( new Null )
	);
}

inline std::auto_ptr< Om::Program > Type_::GiveProgram() const {
	return(
		std::auto_ptr< Program >( new Null )
	);
}

inline bool Type_::IsEmpty() const {
	return( true );
}

inline void Type_::ReadElements( Parser & theParser ) {
	for(
		;
		theParser;
		theParser.Pop()
	) {
		this->thisCodePointSink.Push( *theParser );
	}
}

inline void Type_::ReadQuotedElements( Parser & theParser ) {
	this->thisCodePointSink.Push( Symbols::theStartOperandSymbol );
	this->ReadElements( theParser );
	this->thisCodePointSink.Push( Symbols::theEndOperandSymbol );
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & theOperand ) {
	assert(
		!theOperand.IsEmpty()
	);
	this->TakeQuotedQueue(
		*theOperand.GetProgram()
	);
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & theOperator ) {
	assert(
		!theOperator.IsEmpty()
	);
	std::string const & theString = theOperator.GetString();
	for(
		Sources::CodePointSource< std::string::const_iterator > theCodePointSource(
			theString.begin(),
			theString.end()
		);
		theCodePointSource;
		theCodePointSource.Pop()
	) {
		switch( CodePoint const theCodePoint = *theCodePointSource ) {
		Om_Symbols_SeparatorSymbol_GetCases_():
			// Fall through.
		Om_Symbols_OperandSymbol_GetCases_():
			// Fall through.
		case Symbols::theEncodeOperatorSymbol:
			this->thisCodePointSink.Push( Symbols::theEncodeOperatorSymbol );
			// Fall through.
		default:
			this->thisCodePointSink.Push( theCodePoint );
			// Fall through.
		}
	}
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & theQueue ) {
	this->thisCodePointSink.Push( Symbols::theStartOperandSymbol );
	theQueue.GiveElements( *this );
	this->thisCodePointSink.Push( Symbols::theEndOperandSymbol );
}

template< typename TheSeparator >
inline void Type_::TakeSeparator( TheSeparator & theSeparator ) {
	assert(
		!theSeparator.IsEmpty()
	);
	std::string const & theString = theSeparator.GetString();
	for(
		Sources::CodePointSource< std::string::const_iterator > theCodePointSource(
			theString.begin(),
			theString.end()
		);
		theCodePointSource;
		theCodePointSource.Pop()
	) {
		this->thisCodePointSink.Push( *theCodePointSource );
	}
}

	#undef Type_

#endif
