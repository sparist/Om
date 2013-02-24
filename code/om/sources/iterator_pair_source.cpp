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

#if !defined( Om_Sources_IteratorPairSource_ )

	#include "om/sources/iterator_pair_source.hpp"

	#if defined( Om_Macros_Test_ )

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Sources {

		BOOST_AUTO_TEST_SUITE( IteratorPairSourceTest )
		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

// MARK: - Om::Sources::IteratorPairSource

	#define Template_ \
	template< \
		typename ThisItem, \
		typename ThisIterator \
	>

	#define Type_ \
	Om::Sources::IteratorPairSource< \
		ThisItem, \
		ThisIterator \
	>

// MARK: public (non-static)

Template_
inline Type_::IteratorPairSource(
	ThisIterator theCurrent,
	ThisIterator const theEnd
):
thisCurrent( theCurrent ),
thisEnd( theEnd ) {}

Template_
inline Type_ & Type_::operator =( IteratorPairSource theIteratorPairSource ) {
	this->Swap( theIteratorPairSource );
	return( *this );
}

Template_
inline bool Type_::operator ==( IteratorPairSource const & theSource ) const {
	return( this->thisCurrent == theSource.thisCurrent );
}

Template_
inline bool Type_::operator !() const {
	return( this->thisEnd == this->thisCurrent );
}

Template_
inline ThisItem & Type_::operator *() const {
	assert( this->thisEnd != this->thisCurrent );
	return( *this->thisCurrent );
}

Template_
inline void Type_::End() {
	this->thisCurrent = this->thisEnd;
}

Template_
inline void Type_::Pop() {
	assert( this->thisEnd != this->thisCurrent );
	++this->thisCurrent;
}

Template_
inline void Type_::Swap( IteratorPairSource & theIteratorPairSource ) {
	boost::swap(
		this->thisCurrent,
		theIteratorPairSource.thisCurrent
	);
	boost::swap(
		this->thisEnd,
		theIteratorPairSource.thisEnd
	);
}

	#undef Type_
	#undef Template_

// MARK: - boost

template<
	typename ThisItem,
	typename ThisIterator
>
inline void boost::swap(
	Om::Sources::IteratorPairSource<
		ThisItem,
		ThisIterator
	> & theFirst,
	Om::Sources::IteratorPairSource<
		ThisItem,
		ThisIterator
	> & theSecond
) {
	theFirst.Swap( theSecond );
}

#endif
