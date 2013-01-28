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

#if defined( Om_Sources_ContainerBackSource_ )

// MARK: Om::Sources::ContainerBackSource

	#define Template_ \
	template< \
		typename ThisItem, \
		typename ThisContainer \
	>

	#define Type_ \
	Om::Sources::ContainerBackSource< \
		ThisItem, \
		ThisContainer \
	>

// MARK: public (non-static)

Template_
inline Type_::ContainerBackSource( ThisContainer & theContainer ):
thisContainer( theContainer )
{
}

Template_
inline Type_ & Type_::operator =( ContainerBackSource theContainerBackSource )
{
	this->Swap( theContainerBackSource );
	return( *this );
}

Template_
inline bool Type_::operator ==( ContainerBackSource const & theSource ) const
{
	return(
		&this->thisContainer == &theSource.thisContainer or
		(
			this->thisContainer.empty() and
			theSource.thisContainer.empty()
		)
	);
}

Template_
inline bool Type_::operator !() const
{
	return( this->thisContainer.empty() );
}

Template_
inline ThisItem & Type_::operator *() const
{
	assert( !this->thisContainer.empty() );
	return( this->thisContainer.back() );
}

Template_
inline void Type_::Pop()
{
	assert( !this->thisContainer.empty() );
	this->thisContainer.pop_back();
}

Template_
inline void Type_::Swap( ContainerBackSource & theContainerBackSource )
{
	boost::swap(
		this->thisContainer,
		theContainerBackSource.thisContainer
	);
}

// MARK: -
// MARK: boost

template<
	typename ThisItem,
	typename ThisContainer
>
inline void boost::swap(
	Om::Sources::ContainerBackSource<
		ThisItem,
		ThisContainer
	> & theFirst,
	Om::Sources::ContainerBackSource<
		ThisItem,
		ThisContainer
	> & theSecond
)
{
	theFirst.Swap( theSecond );
}

	#undef Type_
	#undef Template_

#else

	#include "om/sources/container_back_source.hpp"

#endif
