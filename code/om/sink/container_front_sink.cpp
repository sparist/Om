/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Sink_ContainerFrontSink_

	#include "om/sink/container_front_sink.hpp"

#else

// MARK: - Om::Sink::ContainerFrontSink

	#define Template_ \
	template < \
		typename ThisItem, \
		typename ThisContainer \
	>

	#define Type_ \
	Om::Sink::ContainerFrontSink< \
		ThisItem, \
		ThisContainer \
	>

// MARK: public (non-static)

Template_
inline Type_::ContainerFrontSink(ThisContainer & theContainer):
thisContainer(theContainer) {}

Template_
inline Type_ & Type_::operator =(ContainerFrontSink theContainerFrontSink) {
	this->Swap(theContainerFrontSink);
	return *this;
}

Template_
inline void Type_::Push(ThisItem & thisItem) {
	this->thisContainer.push_front(thisItem);
}

Template_
inline void Type_::Swap(ContainerFrontSink & theContainerFrontSink) {
	boost::swap(
		this->thisContainer,
		theContainerFrontSink.thisContainer
	);
}

	#undef Type_
	#undef Template_

// MARK: - boost::

template <
	typename TheItem,
	typename TheContainer
>
inline void boost::swap(
	Om::Sink::ContainerFrontSink<
		TheItem,
		TheContainer
	> & theFirst,
	Om::Sink::ContainerFrontSink<
		TheItem,
		TheContainer
	> & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
