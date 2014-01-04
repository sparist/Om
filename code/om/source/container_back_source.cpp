/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Source_ContainerBackSource_

	#include "om/source/container_back_source.hpp"

#else

// MARK: - Om::Source::ContainerBackSource

	#define Template_ \
	template < \
		typename ThisItem, \
		typename ThisContainer \
	>

	#define Type_ \
	Om::Source::ContainerBackSource< \
		ThisItem, \
		ThisContainer \
	>

// MARK: public (non-static)

Template_
inline Type_::ContainerBackSource(ThisContainer & theContainer):
thisContainer(theContainer) {}

Template_
inline Type_ & Type_::operator =(ContainerBackSource theContainerBackSource) {
	this->Swap(theContainerBackSource);
	return *this;
}

Template_
inline bool Type_::operator !() const {
	return this->thisContainer.empty();
}

Template_
inline ThisItem & Type_::operator *() const {
	assert(
		!this->thisContainer.empty()
	);
	return this->thisContainer.back();
}

Template_
inline bool Type_::Equals(ContainerBackSource const & theContainerBackSource) const {
	return (
		&this->thisContainer == &theContainerBackSource.thisContainer ||
		(
			this->thisContainer.empty() &&
			theContainerBackSource.thisContainer.empty()
		)
	);
}

Template_
inline void Type_::Pop() {
	assert(
		!this->thisContainer.empty()
	);
	this->thisContainer.pop_back();
}

Template_
inline void Type_::Swap(ContainerBackSource & theContainerBackSource) {
	boost::swap(
		this->thisContainer,
		theContainerBackSource.thisContainer
	);
}

	#undef Type_
	#undef Template_

// MARK: - Om::Source::

	#define Template_ \
	template < \
		typename TheItem, \
		typename TheContainer \
	>

	#define Type_ \
	Om::Source::ContainerBackSource< \
		TheItem, \
		TheContainer \
	>

Template_
inline bool Om::Source::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return theFirst.Equals(theSecond);
}

Template_
inline bool Om::Source::operator !=(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return !theFirst.Equals(theSecond);
}

// MARK: - boost::

Template_
inline void boost::swap(
	Type_ & theFirst,
	Type_ & theSecond
) {
	theFirst.Swap(theSecond);
}

	#undef Type_
	#undef Template_

#endif
