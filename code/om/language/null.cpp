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

#ifndef Om_Language_Null_

	#include "om/language/null.hpp"

#else

	#include "om/language/reader.hpp"
	#include "om/source/empty_source.hpp"

// MARK: - Om::Language::Null

	#define Type_ \
	Om::Language::Null

// MARK: public (static)

inline Type_ & Type_::Get() {
	static Null theNull;
	return theNull;
}

inline char const * Type_::GetName() {
	return Om_Language_Null_GetName_();
}

// MARK: public (non-static)

inline Type_::Null() {}

inline Type_::Null(
	Om::Source::Source<CodePoint const> & theCodePointSource
) {
	if (theCodePointSource) {
		theCodePointSource.Pop();
	}
}

inline Type_ & Type_::operator =(Null const &) {
	return *this;
}

inline Om::Language::Program & Type_::operator *() {
	return *this;
}

inline Om::Language::Program const & Type_::operator *() const {
	return *this;
}

inline void Type_::Clear() {}

inline bool Type_::Equals(Element const & theElement) const {
	return theElement.IsEmpty();
}

inline bool Type_::Equals(Program const & theProgram) const {
	return theProgram.IsEmpty();
}

inline std::auto_ptr<
	Om::Source::Source<Om::Language::Element>
> Type_::GetElementRange() {
	return std::auto_ptr<
		Om::Source::Source<Element>
	>(
		new Om::Source::EmptySource<Element>
	);
}

inline std::auto_ptr<
	Om::Source::Source<Om::Language::Element const>
> Type_::GetElementRange() const {
	return std::auto_ptr<
		Om::Source::Source<Element const>
	>(
		new Om::Source::EmptySource<Element const>
	);
}

inline void Type_::GiveElements(Consumer &) {}

inline void Type_::GiveElements(Consumer &) const {}

inline bool Type_::IsEmpty() const {
	return true;
}

inline bool Type_::Merge(Operator &) {
	return true;
}

inline bool Type_::Merge(Operator const &) {
	return true;
}

inline bool Type_::Merge(Separator &) {
	return true;
}

inline bool Type_::Merge(Separator const &) {
	return true;
}

inline void Type_::ParseElements(Reader & theReader) {
	for (
		;
		theReader;
		theReader.Pop()
	) {}
}

inline void Type_::ParseQuotedElements(Reader & theReader) {
	for (
		;
		theReader;
		theReader.Pop()
	) {}
}

inline void Type_::Swap(Null &) {}

inline void Type_::TakeElements(Producer &) {}

inline void Type_::TakeElements(Producer const &) {}

template <typename TheOperand>
inline void Type_::TakeOperand(TheOperand &) {}

template <typename TheOperator>
inline void Type_::TakeOperator(TheOperator &) {}

template <typename TheProducer>
inline void Type_::TakeQuotedProducer(TheProducer &) {}

template <typename TheSeparator>
inline void Type_::TakeSeparator(TheSeparator &) {}

	#undef Type_

// MARK: - boost::

template <>
inline void boost::swap(
	Om::Language::Null & theFirst,
	Om::Language::Null & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
