/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.1
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if defined( Om_Sinks_ContainerFrontSink_ )

// MARK: Om::Sinks::ContainerFrontSink

	#define Template_ template< typename ThisItem, typename ThisContainer >

	#define Type_ Om::Sinks::ContainerFrontSink< ThisItem, ThisContainer >

// MARK: public (non-static)

Template_
inline Type_::ContainerFrontSink( ThisContainer & theContainer )
:
thisContainer( theContainer )
{
}

Template_
inline Type_ & Type_::operator =( ContainerFrontSink theContainerFrontSink )
{
	this->Swap( theContainerFrontSink );
	return( *this );
}

Template_
inline void Type_::Push( ThisItem & thisItem )
{
	this->thisContainer.push_front( thisItem );
}

Template_
inline void Type_::Swap( ContainerFrontSink & theContainerFrontSink )
{
	boost::swap(
		this->thisContainer,
		theContainerFrontSink.thisContainer
	);
	return( *this );
}

	#undef Type_
	#undef Template_

// MARK: -
// MARK: boost

template< typename ThisItem, typename ThisContainer >
inline void boost::swap(
	Om::Sinks::ContainerFrontSink< ThisItem, ThisContainer > & theFirst,
	Om::Sinks::ContainerFrontSink< ThisItem, ThisContainer > & theSecond
)
{
	theFirst.Swap( theSecond );
}

#else
	#include "om/sinks/container_front_sink.hpp"
#endif
