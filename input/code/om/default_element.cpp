/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_DefaultElement_

	#include "om/default_element.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(DefaultElementTest)

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#include "om/sources/singleton_source.hpp"

// MARK: - Om::DefaultElement

	#define Template_ \
	template < \
		typename ThisImplementation, \
		typename ThisInterface \
	>

	#define Type_ \
	Om::DefaultElement< \
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
	Om::Source<Om::Element>
> Type_::GetElementRange() {
	return std::auto_ptr<
		Source<Element>
	>(
		new Sources::SingletonSource<Element>(*this)
	);
}

Template_
inline std::auto_ptr<
	Om::Source<Om::Element const>
> Type_::GetElementRange() const {
	return std::auto_ptr<
		Source<Element const>
	>(
		new Sources::SingletonSource<Element const>(*this)
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
