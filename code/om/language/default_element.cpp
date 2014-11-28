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

#ifndef Om_Language_DefaultElement_

	#include "om/language/default_element.hpp"

#else

	#include "om/source/singleton_source.hpp"

// MARK: - Om::Language::DefaultElement

	#define Template_ \
	template < \
		typename ThisImplementation, \
		typename ThisInterface \
	>

	#define Type_ \
	Om::Language::DefaultElement< \
		ThisImplementation, \
		ThisInterface \
	>

// MARK: public (non-static)

Template_
inline Type_::~DefaultElement() {}

Template_
inline bool Type_::Equals(Element const & theElement) const {
	if (
		typeid(theElement) == typeid(ThisImplementation)
	) {
		assert(
			dynamic_cast<ThisImplementation const *>(this) &&
			dynamic_cast<ThisImplementation const *>(&theElement)
		);
		return static_cast<ThisImplementation const &>(*this).Equals(
			static_cast<ThisImplementation const &>(theElement)
		);
	}
	return (
		this->IsEmpty() &&
		theElement.IsEmpty()
	);
}

Template_
inline std::auto_ptr<
	Om::Source::Source<Om::Language::Element>
> Type_::GetElementRange() {
	return std::auto_ptr<
		Om::Source::Source<Element>
	>(
		new Om::Source::SingletonSource<Element>(*this)
	);
}

Template_
inline std::auto_ptr<
	Om::Source::Source<Om::Language::Element const>
> Type_::GetElementRange() const {
	return std::auto_ptr<
		Om::Source::Source<Element const>
	>(
		new Om::Source::SingletonSource<Element const>(*this)
	);
}

Template_
inline void Type_::GiveElements(Consumer & theConsumer) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	if (
		!this->IsEmpty()
	) {
		theConsumer.TakeElement(
			static_cast<ThisImplementation &>(*this)
		);
	}
}

Template_
inline void Type_::GiveElements(Consumer & theConsumer) const {
	assert(
		dynamic_cast<ThisImplementation const *>(this)
	);
	if (
		!this->IsEmpty()
	) {
		theConsumer.TakeElement(
			static_cast<ThisImplementation const &>(*this)
		);
	}
}

	#undef Type_
	#undef Template_

#endif
