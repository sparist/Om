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

#ifndef Om_DefaultAtom_

	#include "om/default_atom.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(DefaultAtomTest)

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#include "om/sources/empty_source.hpp"

	#ifndef Om_Macros_Precompilation_

		#include "boost/locale/conversion.hpp"

	#endif

// MARK: - Om::DefaultAtom

	#define Template_ \
	template <typename ThisImplementation>

	#define Type_ \
	Om::DefaultAtom<ThisImplementation>

// MARK: public (non-static)

Template_
inline Type_::~DefaultAtom() {}

Template_
inline bool Type_::operator <(DefaultAtom const & theAtom) {
	return (this->thisString < theAtom.thisString);
}

Template_
inline void Type_::Clear() {
	this->thisString.clear();
}

Template_
inline bool Type_::Equals(DefaultAtom const & theAtom) const {
	return (this->thisString == theAtom.thisString);
}

Template_
inline bool Type_::Equals(ThisImplementation const & theAtom) const {
	return this->Equals(
		static_cast<DefaultAtom const &>(theAtom)
	);
}

Template_
inline std::auto_ptr<
	Om::Source<Om::Element>
> Type_::GetElementRange() {
	if (
		this->IsEmpty()
	) {
		return std::auto_ptr<
			Source<Element>
		>(
			new Sources::EmptySource<Element>
		);
	}
	return this->DefaultElement<
		ThisImplementation,
		Atom
	>::GetElementRange();
}

Template_
inline std::auto_ptr<
	Om::Source<Om::Element const>
> Type_::GetElementRange() const {
	if (
		this->IsEmpty()
	) {
		return std::auto_ptr<
			Source<Element const>
		>(
			new Sources::EmptySource<Element const>
		);
	}
	return this->DefaultElement<
		ThisImplementation,
		Atom
	>::GetElementRange();
}

Template_
inline std::string const & Type_::GetString() const {
	return this->thisString;
}

Template_
inline bool Type_::IsEmpty() const {
	return this->thisString.empty();
}

Template_
inline bool Type_::Merge(ThisImplementation & theAtom) {
	this->TakeElement(theAtom);
	return true;
}

Template_
inline bool Type_::Merge(ThisImplementation const & theAtom) {
	this->TakeElement(theAtom);
	return true;
}

Template_
inline void Type_::Swap(ThisImplementation & theAtom) {
	this->thisString.swap(theAtom.thisString);
}

// MARK: protected (non-static)

Template_
inline Type_::DefaultAtom():
thisString() {}

Template_
inline Type_::DefaultAtom(
	char const theCodeUnitIterator[]
):
thisString(theCodeUnitIterator) {
	assert(
		theCodeUnitIterator &&
		"The argument cannot be null."
	);
	assert(
		boost::locale::normalize(
			this->thisString,
			boost::locale::norm_nfd
		) == this->thisString &&
		"The string must be NFD-normalized."
	);
}

Template_
inline Type_::DefaultAtom(char const theCodeUnit):
thisString(
	1,
	theCodeUnit
) {
	assert(
		boost::locale::normalize(
			this->thisString,
			boost::locale::norm_nfd
		) == this->thisString &&
		"The code unit must be NFD-normalized."
	);
}

	#undef Type_
	#undef Template_

// MARK: - Om::

	#define Template_ \
	template <typename TheImplementation>

	#define Type_ \
	Om::DefaultAtom<TheImplementation>

Template_
inline bool Om::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return theFirst.Equals(theSecond);
}

Template_
inline bool Om::operator !=(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return !theFirst.Equals(theSecond);
}

	#undef Type_
	#undef Template_

#endif
