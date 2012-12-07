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
#if defined( Om_Translator_ )

	#include "om/expansion.hpp"
	#include "om/lexicon.hpp"

// MARK: Om::Translator

	#define Type_ Om::Translator

// MARK: public (non-static)

inline Type_::Translator()
:
thisLexiconVector()
{
}

inline Type_ & Type_::operator =( Translator theTranslator )
{
	this->Swap( theTranslator );
	return( *this );
}

inline int Type_::Translate(
	Expansion & theExpansion,
	Operator const & theOperator
) const
{
	typedef LexiconVector::const_reverse_iterator Iterator;
	Iterator const theEnd = this->thisLexiconVector.rend();
	Iterator theIterator = this->thisLexiconVector.rbegin();
	for( Program const * theProgram; theEnd != theIterator; ++theIterator ){
		if( ( *theIterator )->Find( theOperator, theProgram ) ){
			if( theProgram ){
				theExpansion.TakeQueue( *theProgram );
				return( 2 );
			}
			return( 1 );
		}
	}
	return( 0 );
}

inline void Type_::Push( Lexicon const & theLexicon )
{
	this->thisLexiconVector.push_back( &theLexicon );
}

inline void Type_::Swap( Translator & theTranslator )
{
	this->thisLexiconVector.swap( theTranslator.thisLexiconVector );
}

	#undef Type_

// MARK: -
// MARK: boost

template<>
inline void boost::swap( Om::Translator & theFirst, Om::Translator & theSecond )
{
	theFirst.Swap( theSecond );
}

#else
	#include "om/translator.hpp"
#endif
