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

#if defined( Om_System_ )

	#include "om/lexicon.hpp"
	#include "om/operator.hpp"

// MARK: Om::System

	#define Type_ \
	Om::System

// MARK: public (static)

inline Type_ & Type_::Get()
{
	static System theSystem;
	return( theSystem );
}

// MARK: public (non-static)

inline Om::Lexicon const & Type_::GetLexicon() const
{
	static Lexicon theLexicon;
	if( theLexicon.IsEmpty() ){
		this->GiveElements( theLexicon );
	}
	return( theLexicon );
}

inline void Type_::GiveElements( Queue & theQueue ) const
{
	if( !this->IsEmpty() ){
		Map::const_iterator const theEnd = this->thisMap.end();
		Map::const_iterator theCurrent = this->thisMap.begin();
		assert( theEnd != theCurrent );
		for(
			;
			;
			theQueue.TakeElement( Separator::GetLineSeparator() )
		){
			Operator theOperator( theCurrent->first );
			theQueue.TakeElement( theOperator );
			if( theEnd == ++theCurrent ){
				return;
			}
		}
	}
}

inline void Type_::Initialize( char const theLocaleCodeUnitIterator[] )
{
	// Set the global locale.
	{
		boost::locale::generator theGenerator;
		theGenerator.characters( boost::locale::char_facet );
		std::locale::global(
			theGenerator( theLocaleCodeUnitIterator )
		);
		assert(
			std::use_facet< boost::locale::info >( std::locale() ).utf8()
		);
	}

	#if !defined( NDEBUG )
	// Assert that the name keys are NFD-normalized.
	{
		Map::const_iterator const theEnd = this->thisMap.end();
		Map::const_iterator theCurrent = this->thisMap.begin();
		for(
			;
			theEnd != theCurrent;
			++theCurrent
		){
			assert(
				boost::locale::normalize(
					theCurrent->first,
					boost::locale::norm_nfd
				) == theCurrent->first
			);
		}
	}
	#endif
}

inline bool Type_::IsEmpty() const
{
	return( this->thisMap.empty() );
}

inline bool Type_::Translate(
	Evaluation & theEvaluation,
	Operator const & theOperator
) const
{
	Map::const_iterator theIterator(
		this->thisMap.find( theOperator.GetString() )
	);
	if( this->thisMap.end() == theIterator ){
		return( false );
	}
	assert( theIterator->second );
	( *theIterator->second )( theEvaluation );
	return( true );
}

// MARK: private (non-static)

inline Type_::System()
:
thisMap()
{
}

	#undef Type_

#else

	#include "om/system.hpp"

#endif
