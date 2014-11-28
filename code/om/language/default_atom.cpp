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

#ifndef Om_Language_DefaultAtom_

	#include "om/language/default_atom.hpp"

#else

	#include "om/source/empty_source.hpp"

	#ifndef Om_Macro_Precompilation_

		#include "boost/locale/conversion.hpp"

	#endif

// MARK: - Om::Language::DefaultAtom

	#define Template_ \
	template <typename ThisImplementation>

	#define Type_ \
	Om::Language::DefaultAtom<ThisImplementation>

// MARK: public (non-static)

Template_
inline Type_::~DefaultAtom() {}

Template_
inline bool Type_::operator <(DefaultAtom const & theAtom) {
	return this->thisString < theAtom.thisString;
}

Template_
inline void Type_::Clear() {
	this->thisString.clear();
}

Template_
inline bool Type_::Equals(DefaultAtom const & theAtom) const {
	return this->thisString == theAtom.thisString;
}

Template_
inline bool Type_::Equals(ThisImplementation const & theAtom) const {
	return this->Equals(
		static_cast<DefaultAtom const &>(theAtom)
	);
}

Template_
inline std::auto_ptr<
	Om::Source::Source<Om::Language::Element>
> Type_::GetElementRange() {
	if (
		this->IsEmpty()
	) {
		return std::auto_ptr<
			Om::Source::Source<Element>
		>(
			new Om::Source::EmptySource<Element>
		);
	}
	return this->DefaultElement<
		ThisImplementation,
		Atom
	>::GetElementRange();
}

Template_
inline std::auto_ptr<
	Om::Source::Source<Om::Language::Element const>
> Type_::GetElementRange() const {
	if (
		this->IsEmpty()
	) {
		return std::auto_ptr<
			Om::Source::Source<Element const>
		>(
			new Om::Source::EmptySource<Element const>
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

// MARK: - Om::Language::

	#define Template_ \
	template <typename TheImplementation>

	#define Type_ \
	Om::Language::DefaultAtom<TheImplementation>

Template_
inline bool Om::Language::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return theFirst.Equals(theSecond);
}

Template_
inline bool Om::Language::operator !=(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return !theFirst.Equals(theSecond);
}

	#undef Type_
	#undef Template_

#endif
