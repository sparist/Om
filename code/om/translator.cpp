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

#if defined( Om_Translator_ )

	#include "om/writer.hpp"
	#include "om/evaluator.hpp"

// MARK: Om::Translator

	#define Type_ \
	Om::Translator

// MARK: public (non-static)

inline void Type_::Evaluate(
	Source< CodePoint const > & theCodePointSource,
	Sink< CodePoint const > & theCodePointSink
) const {
	Writer theWriter( theCodePointSink );
	Parser theParser( theCodePointSource );
	Evaluator(
		theWriter,
		*this
	).ReadElements( theParser );
}

inline std::string Type_::Evaluate( char const theCodeUnitIterator[] ) const {
	assert( theCodeUnitIterator );
	std::string theString;
	{
		Sources::CodePointSource<> theCodePointSource( theCodeUnitIterator );
		Sinks::CodePointSink<
			std::back_insert_iterator< std::string >
		> theCodePointSink(
			std::back_inserter( theString )
		);
		this->Evaluate(
			theCodePointSource,
			theCodePointSink
		);
	}
	return( theString );
}

inline void Type_::GiveElements( Queue & theQueue ) const {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline bool Type_::IsEmpty() const {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline bool Type_::Translate(
	Evaluation &,
	Operator const &
) const {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

	#undef Type_

#else

	#include "om/translator.hpp"

#endif
