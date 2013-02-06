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

#if !defined( Om_Sources_DefaultSource_ )

	#include "om/sources/default_source.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om {

	namespace Sources {

		SUITE( DefaultSource ) {}

	}

}

	#endif

#else

// MARK: - Om::Sources::DefaultSource

	#define Template_ \
	template< \
		typename ThisItem, \
		typename ThisImplementation \
	>

	#define Type_ \
	Om::Sources::DefaultSource< \
		ThisItem, \
		ThisImplementation \
	>

// MARK: public (non-static)

Template_
inline Type_::~DefaultSource() {}

Template_
inline bool Type_::operator ==(
	Source< ThisItem > const & theSource
) const {
	assert(
		dynamic_cast< ThisImplementation const * >( this )
	);
	ThisImplementation const * const theImplementation = static_cast< ThisImplementation const * >( &theSource );
	return(
		theImplementation &&
		static_cast< ThisImplementation const & >( *this ) == *theImplementation
	);
}

Template_
inline ThisImplementation & Type_::operator ++() {
	assert(
		dynamic_cast< ThisImplementation * >( this )
	);
	assert( *this );
	this->Pop();
	return(
		static_cast< ThisImplementation & >( *this )
	);
}

Template_
inline ThisImplementation Type_::operator ++( int ) {
	assert(
		dynamic_cast< ThisImplementation * >( this )
	);
	ThisImplementation theSource(
		static_cast< ThisImplementation & >( *this )
	);
	++*this;
	return( theSource );
}

	#undef Type_
	#undef Template_

#endif
