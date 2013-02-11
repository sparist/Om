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

#if !defined( Om_Parser_ )

	#include "om/parser.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om {

	SUITE( Parser ) {}

}

	#endif

#else

	#include "om/symbols/operand_symbol.hpp"
	#include "om/symbols/operator_symbol.hpp"

// MARK: - Om::Parser

	#define Type_ \
	Om::Parser

// MARK: public (non-static)

inline Type_::Parser(
	Source< CodePoint const > & theCodePointSource
):
thisCodePointSource( theCodePointSource ),
thisDepth(),
thisIsEncoded() {}

inline bool Type_::operator ==( Parser const & theParser ) const {
	assert(
		( this->thisCodePointSource != theParser.thisCodePointSource ) ||
		( this->thisDepth == theParser.thisDepth )
	);
	return( this->thisCodePointSource == theParser.thisCodePointSource );
}

inline Om::CodePoint const & Type_::operator *() const {
	assert(
		!this->operator !()
	);
	return( *this->thisCodePointSource );
}

inline bool Type_::operator !() const {
	return(
		!this->thisCodePointSource ||
		(
			!this->thisDepth &&
			!this->thisIsEncoded &&
			( Symbols::theEndOperandSymbol == *this->thisCodePointSource )
		)
	);
}

inline void Type_::Pop() {
	assert( this->thisCodePointSource );
	switch( *this->thisCodePointSource ) {
	case Symbols::theStartOperandSymbol:
		if( this->thisIsEncoded ) {
			this->thisIsEncoded = false;
		} else {
			if(
				static_cast< size_t >( -1 ) == this->thisDepth
			) {
				throw(
					std::overflow_error( "Operand overflow." )
				);
			}
			++this->thisDepth;
		}
		break;
	case Symbols::theEndOperandSymbol:
		if( this->thisIsEncoded ) {
			this->thisIsEncoded = false;
		} else {
			assert( this->thisDepth );
			--this->thisDepth;
		}
		break;
	case Symbols::theEncodeOperatorSymbol:
		this->thisIsEncoded = !this->thisIsEncoded;
		break;
	default:
		this->thisIsEncoded = false;
		// Fall through.
	}
	this->thisCodePointSource.Pop();
}

	#undef Type_

#endif
