/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Sources_ContainerFrontSource_ )

	#include "om/sources/container_front_source.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om {

	namespace Sources {

		SUITE( ContainerFrontSource ) {}

	}

}

	#endif

#else

// MARK: - Om::Sources::ContainerFrontSource

	#define Template_ \
	template< \
		typename ThisItem, \
		typename ThisContainer \
	>

	#define Type_ \
	Om::Sources::ContainerFrontSource< \
		ThisItem, \
		ThisContainer \
	>

// MARK: public (non-static)

Template_
inline Type_::ContainerFrontSource( ThisContainer & theContainer ):
thisContainer( theContainer ) {}

Template_
inline Type_ & Type_::operator =( ContainerFrontSource theContainerFrontSource ) {
	this->Swap( theContainerFrontSource );
	return( *this );
}

Template_
inline bool Type_::operator ==( ContainerFrontSource const & theSource ) const {
	return(
		&this->thisContainer == &theSource.thisContainer or
		(
			this->thisContainer.empty() and
			theSource.thisContainer.empty()
		)
	);
}

Template_
inline bool Type_::operator !() const {
	return( this->thisContainer.empty() );
}

Template_
inline ThisItem & Type_::operator *() const {
	assert( !this->thisContainer.empty() );
	return( this->thisContainer.front() );
}

Template_
inline void Type_::Pop() {
	assert( !this->thisContainer.empty() );
	this->thisContainer.pop_front();
}

Template_
inline void Type_::Swap( ContainerFrontSource & theContainerFrontSource ) {
	boost::swap(
		this->thisContainer,
		theContainerFrontSource.thisContainer
	);
}

	#undef Type_
	#undef Template_

// MARK: - boost

template<
	typename ThisItem,
	typename ThisContainer
>
inline void boost::swap(
	Om::Sources::ContainerFrontSource<
		ThisItem,
		ThisContainer
	> & theFirst,
	Om::Sources::ContainerFrontSource<
		ThisItem,
		ThisContainer
	> & theSecond
) {
	theFirst.Swap( theSecond );
}

#endif
