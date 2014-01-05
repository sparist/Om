/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Parser_

	#include "om/parser.hpp"

#else

	#include "om/consumer.hpp"
	#include "om/symbol/operand_symbol.hpp"
	#include "om/symbol/operator_symbol.hpp"
	#include "om/symbol/separator_symbol.hpp"

// MARK: - Om::Parser

	#define Type_ \
	Om::Parser

// MARK: public (non-static)

inline Type_::Parser(
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

inline bool Type_::Equals(Parser const & theParser) const {
	assert(
		this->thisCodePointSource != theParser.thisCodePointSource ||
		this->thisDepth == theParser.thisDepth
	);
	return this->thisCodePointSource == theParser.thisCodePointSource;
}

template<
	typename TheOperator,
	typename TheSeparator
>
inline void Type_::Parse(Consumer & theConsumer) {
	Parser & theParser = *this;
	while (theParser) {
		assert(Symbol::theEndOperandSymbol != *theParser);
		switch (*theParser) {
		case Symbol::theStartOperandSymbol:
			theParser.Pop();
			{
				// Ensure that this does not resolve to the copy constructor.
				Om::Source::Source<CodePoint const> & theCodePointSource = theParser;

				Parser theOperandParser(theCodePointSource);
				theConsumer.ReadQuotedElements(theOperandParser);
			}
			if (!theParser) {
				return;
			}
			assert(Symbol::theEndOperandSymbol == *theParser);
			theParser.Pop();
			continue;
		Om_Symbol_SeparatorSymbol_GetCases_():
			{
				TheSeparator theSeparator(theParser);
				theConsumer.TakeElement(theSeparator);
			}
			continue;
		default:
			{
				TheOperator theOperator(theParser);
				theConsumer.TakeElement(theOperator);
			}
			// Fall through.
		}
	}
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

// MARK: - Om::

inline bool Om::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return theFirst.Equals(theSecond);
}

inline bool Om::operator !=(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return !theFirst.Equals(theSecond);
}

	#undef Type_

#endif
