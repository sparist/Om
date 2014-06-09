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
	\author
		Jason Erb
*/

#ifndef Om_Consumer_

	#include "om/consumer.hpp"

#else

	#include "om/reader.hpp"

	#ifndef Om_Macro_Precompilation_

		#include <cassert>
		#include <stdexcept>

	#endif

// MARK: - Om::Consumer

	#define Type_ \
	Om::Consumer

// MARK: public (non-static)

inline Type_::~Consumer() {}

template<
	typename TheOperator,
	typename TheSeparator
>
inline void Type_::Parse(Reader & theReader) {
	while (theReader) {
		assert(Symbol::theEndOperandSymbol != *theReader);
		switch (*theReader) {
		case Symbol::theStartOperandSymbol:
			theReader.Pop();
			{
				// Ensure that this does not resolve to the copy constructor.
				Om::Source::Source<CodePoint const> & theCodePointSource = theReader;

				Reader theOperandReader(theCodePointSource);
				this->ParseQuotedElements(theOperandReader);
			}
			if (!theReader) {
				return;
			}
			assert(Symbol::theEndOperandSymbol == *theReader);
			theReader.Pop();
			continue;
		Om_Symbol_SeparatorSymbol_GetCases_():
			{
				TheSeparator theSeparator(theReader);
				this->TakeElement(theSeparator);
			}
			continue;
		default:
			{
				TheOperator theOperator(theReader);
				this->TakeElement(theOperator);
			}
			// Fall through.
		}
	}
}

inline void Type_::ParseElements(Reader &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::ParseQuotedElements(Reader &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Operand &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Null &) {}

inline void Type_::TakeElement(Null const &) {}

inline void Type_::TakeElement(Operand const &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Operator &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Operator const &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Separator &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElement(Separator const &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElements(Producer &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeElements(Producer const &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeQuotedElements(Producer &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline void Type_::TakeQuotedElements(Producer const &) {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

	#undef Type_

#endif
