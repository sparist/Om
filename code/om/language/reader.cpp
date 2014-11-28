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

#ifndef Om_Language_Reader_

	#include "om/language/reader.hpp"

#else

	#include "om/language/symbol/operand_symbol.hpp"
	#include "om/language/symbol/operator_symbol.hpp"
	#include "om/language/symbol/separator_symbol.hpp"

// MARK: - Om::Language::Reader

	#define Type_ \
	Om::Language::Reader

// MARK: public (non-static)

inline Type_::Reader(
	Om::Source::Source<CodePoint const> & theCodePointSource
):
thisCodePointSource(theCodePointSource),
thisDepth(),
thisIsEncoded() {}

inline Om::CodePoint const & Type_::operator *() const {
	assert(
		!this->operator !()
	);
	return *this->thisCodePointSource;
}

inline bool Type_::operator !() const {
	return (
		!this->thisCodePointSource ||
		(
			!this->thisDepth &&
			!this->thisIsEncoded &&
			Symbol::theEndOperandSymbol == *this->thisCodePointSource
		)
	);
}

inline bool Type_::Equals(Reader const & theReader) const {
	assert(
		this->thisCodePointSource != theReader.thisCodePointSource ||
		this->thisDepth == theReader.thisDepth
	);
	return this->thisCodePointSource == theReader.thisCodePointSource;
}

inline void Type_::Pop() {
	assert(this->thisCodePointSource);
	switch (*this->thisCodePointSource) {
	case Symbol::theStartOperandSymbol:
		if (this->thisIsEncoded) {
			this->thisIsEncoded = false;
		} else {
			if (
				static_cast<size_t>(-1) == this->thisDepth
			) {
				throw std::overflow_error("Operand overflow.");
			}
			++this->thisDepth;
		}
		break;
	case Symbol::theEndOperandSymbol:
		if (this->thisIsEncoded) {
			this->thisIsEncoded = false;
		} else {
			assert(this->thisDepth);
			--this->thisDepth;
		}
		break;
	case Symbol::theEncodeOperatorSymbol:
		this->thisIsEncoded = !this->thisIsEncoded;
		break;
	default:
		this->thisIsEncoded = false;
		// Fall through.
	}
	this->thisCodePointSource.Pop();
}

// MARK: - Om::Language::

inline bool Om::Language::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return theFirst.Equals(theSecond);
}

inline bool Om::Language::operator !=(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return !theFirst.Equals(theSecond);
}

	#undef Type_

#endif
