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

#if !defined( Om_Shareable_ )

	#include "om/shareable.hpp"

	#if defined( Om_Macros_Test_ )

		#if !defined( Om_Macros_Precompilation_ )

			#include "UnitTest++.h"

		#endif

namespace Om {

	SUITE( Shareable ) {}

}

	#endif

#else

	#if !defined( Om_Macros_Precompilation_ )

		#include <stdexcept>
		#include "boost/checked_delete.hpp"
		#include "boost/integer_traits.hpp"

	#endif

// MARK: - Om::Shareable

	#define Template_ \
	template< typename ThisOwnerCount >

	#define Type_ \
	Om::Shareable< ThisOwnerCount >

// MARK: public (non-static)

Template_
inline Type_::~Shareable() {
	assert(
		!this->thisOwnerCount &&
		"Non-zero owner count."
	);
}

Template_
inline ThisOwnerCount Type_::GetOwnerCount() const {
	return( this->thisOwnerCount );
}

// MARK: protected (non-static)

Template_
inline Type_::Shareable():
thisOwnerCount() {}

Template_
inline Type_::Shareable( Shareable const & ):
thisOwnerCount() {}

Template_
inline Type_ & Type_::operator =( Shareable const & ) {
	return( *this );
}

// MARK: private (non-static)

Template_
inline void Type_::DecrementOwnerCount() {
	assert(
		this->thisOwnerCount &&
		"Owner count underflow."
	);
	--this->thisOwnerCount;
}

Template_
inline void Type_::IncrementOwnerCount() {
	if(
		boost::integer_traits< ThisOwnerCount >::const_max == this->thisOwnerCount
	) {
		throw(
			std::overflow_error( "Owner count overflow." )
		);
	}
	++this->thisOwnerCount;
}

	#undef Type_
	#undef Template_

// MARK: - Om

template< typename TheOwnerCount >
inline void Om::intrusive_ptr_add_ref(
	Shareable< TheOwnerCount > * const thePointee
) {
	assert(
		thePointee &&
		"The pointer cannot be null."
	);
	thePointee->IncrementOwnerCount();
}

template< typename TheOwnerCount >
inline void Om::intrusive_ptr_release(
	Shareable< TheOwnerCount > * const thePointee
) {
	assert(
		thePointee &&
		"The pointer cannot be null."
	);
	thePointee->DecrementOwnerCount();
	if( !thePointee->thisOwnerCount ) {
		boost::checked_delete( thePointee );
	}
}

#endif
