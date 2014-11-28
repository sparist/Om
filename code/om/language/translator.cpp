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

#ifndef Om_Language_Translator_

	#include "om/language/translator.hpp"

#else

	#include "om/language/writer.hpp"
	#include "om/language/evaluator.hpp"

// MARK: - Om::Language::Translator

	#define Type_ \
	Om::Language::Translator

// MARK: public (non-static)

inline void Type_::Evaluate(
	Om::Source::Source<CodePoint const> & theCodePointSource,
	Om::Sink::Sink<CodePoint const> & theCodePointSink
) const {
	Writer theWriter(theCodePointSink);
	Reader theReader(theCodePointSource);
	Evaluator(
		theWriter,
		*this
	).ParseElements(theReader);
}

inline std::string Type_::Evaluate(
	char const theCodeUnitIterator[]
) const {
	assert(theCodeUnitIterator);
	std::string theString;
	{
		Om::Source::CodePointSource<> theCodePointSource(theCodeUnitIterator);
		Om::Sink::CodePointSink<
			std::back_insert_iterator<std::string>
		> theCodePointSink(
			std::back_inserter(theString)
		);
		this->Evaluate(
			theCodePointSource,
			theCodePointSink
		);
	}
	return theString;
}

inline void Type_::GiveElements(Consumer & theConsumer) const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline bool Type_::IsEmpty() const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

inline bool Type_::Translate(
	Evaluation &,
	Operator const &
) const {
	assert(0);
	throw std::logic_error("Pure virtual function called.");
}

	#undef Type_

#endif
