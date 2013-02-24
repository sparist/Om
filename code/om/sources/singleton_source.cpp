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

#if !defined( Om_Sources_SingletonSource_ )

	#include "om/sources/singleton_source.hpp"

	#if defined( Om_Macros_Test_ )

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Sources {

		BOOST_AUTO_TEST_SUITE( SingletonSourceTest )
		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

// MARK: - Om::Sources::SingletonSource

	#define Template_ \
	template< typename ThisItem >

	#define Type_ \
	Om::Sources::SingletonSource< ThisItem >

// MARK: public (non-static)

Template_
inline Type_::SingletonSource():
thisItem() {}

Template_
inline Type_::SingletonSource( ThisItem & theItem ):
thisItem( &theItem ) {}

Template_
inline Type_ & Type_::operator =( SingletonSource theSingletonSource ) {
	this->Swap( theSingletonSource );
	return( *this );
}

Template_
inline bool Type_::operator ==( SingletonSource const & theSource ) const {
	return( this->thisItem == theSource.thisItem );
}

Template_
inline bool Type_::operator !() const {
	return( !this->thisItem );
}

Template_
inline ThisItem & Type_::operator *() const {
	assert( this->thisItem );
	return( *this->thisItem );
}

Template_
inline void Type_::Pop() {
	assert( this->thisItem );
	this->thisItem = 0;
}

Template_
inline void Type_::Swap( SingletonSource & theSingletonSource ) {
	boost::swap(
		this->thisItem,
		theSingletonSource.thisItem
	);
}

	#undef Type_
	#undef Template_

// MARK: - boost

template< typename ThisItem >
inline void boost::swap(
	Om::Sources::SingletonSource< ThisItem > & theFirst,
	Om::Sources::SingletonSource< ThisItem > & theSecond
) {
	theFirst.Swap( theSecond );
}

#endif
