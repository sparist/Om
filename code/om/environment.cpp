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
#if defined( Om_Environment_ )

	#include "om/system.hpp"

// MARK: Om::Environment

	#define Type_ Om::Environment

// MARK: public (non-static)

inline Type_::Environment()
{
}

inline Type_::Environment( Translator const & theTranslator )
:
Translator( theTranslator )
{
}

inline Type_ & Type_::operator =( Translator const & theTranslator )
{
	this->Translator::operator =( theTranslator );
	return( *this );
}

template< typename TheCodePointSource, typename TheCodePointSink >
inline void Type_::Evaluate(
	TheCodePointSource & theCodePointSource,
	TheCodePointSink & theCodePointSink
)
{
	Writer theWriter( theCodePointSink );
	Parser theParser( theCodePointSource );
	Evaluator( theWriter, *this ).ReadElements( theParser );
}

inline std::string Type_::Evaluate( char const theCodeUnitIterator[] )
{
	assert( theCodeUnitIterator );
	std::string theString;
	{
		Sources::CodePointSource<> theCodePointSource( theCodeUnitIterator );
		Sinks::CodePointSink<
			std::back_insert_iterator< std::string >
		> theCodePointSink( std::back_inserter( theString ) );
		this->Evaluate( theCodePointSource, theCodePointSink );
	}
	return( theString );
}

inline int Type_::Translate(
	Expansion & theExpansion,
	Operator const & theOperator
) const
{
	return(
		(
			2 == this->Translator::Translate( theExpansion, theOperator ) ||
			System::Get().Translate( theExpansion, theOperator )
		) ? 2 : 0
	);
}

	#undef Type_

#else
	#include "om/environment.hpp"
#endif
