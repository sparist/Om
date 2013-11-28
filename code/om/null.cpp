/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Null_

	#include "om/null.hpp"

#else

	#include "om/parser.hpp"
	#include "om/source/empty_source.hpp"

// MARK: - Om::Null

	#define Type_ \
	Om::Null

// MARK: public (static)

inline Type_ & Type_::Get() {
	static Null theNull;
	return theNull;
}

inline char const * Type_::GetName() {
	return Om_Null_GetName_();
}

// MARK: public (non-static)

inline Type_::Null() {}

inline Type_::Null(
	Source::Source<CodePoint const> & theCodePointSource
) {
	if (theCodePointSource) {
		theCodePointSource.Pop();
	}
}

inline Type_ & Type_::operator =(Null const &) {
	return *this;
}

inline Om::Program & Type_::operator *() {
	return *this;
}

inline Om::Program const & Type_::operator *() const {
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
	Om::Source::Source<Om::Element>
> Type_::GetElementRange() {
	return std::auto_ptr<
		Source::Source<Element>
	>(
		new Source::EmptySource<Element>
	);
}

inline std::auto_ptr<
	Om::Source::Source<Om::Element const>
> Type_::GetElementRange() const {
	return std::auto_ptr<
		Source::Source<Element const>
	>(
		new Source::EmptySource<Element const>
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

inline void Type_::ReadElements(Parser & theParser) {
	for (
		;
		theParser;
		theParser.Pop()
	) {}
}

inline void Type_::ReadQuotedElements(Parser & theParser) {
	for (
		;
		theParser;
		theParser.Pop()
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
	Om::Null & theFirst,
	Om::Null & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
