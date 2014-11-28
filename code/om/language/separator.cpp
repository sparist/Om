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

#ifndef Om_Language_Separator_

	#include "om/language/separator.hpp"

	#ifdef Om_Macro_Test_

		#include "om/language/writer.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		BOOST_AUTO_TEST_SUITE(SeparatorTest)

			BOOST_AUTO_TEST_CASE(DereferenceTest) {
				{
					Separator theMutableSeparator;
					Atom & theMutableAtom = theMutableSeparator;
					Program & theMutableDereference = *theMutableAtom;
					BOOST_CHECK(
						typeid(theMutableDereference) == typeid(Null)
					);
				}

				{
					Separator const theImmutableSeparator;
					Atom const & theImmutableAtom = theImmutableSeparator;
					Program const & theImmutableDereference = *theImmutableAtom;
					BOOST_CHECK(
						typeid(theImmutableDereference) == typeid(Null)
					);
				}
			}

			BOOST_AUTO_TEST_CASE(ReadTest) {
				char const theCode[] = "0\n\t {1\n\t {2\n\t } 3\n\t } {4\n\t} 5\n";
				std::string theResult;
				{
					Om::Sink::CodePointSink<
						std::back_insert_iterator<std::string>
					> theCodePointSink(
						std::back_inserter(theResult)
					);
					Writer theWriter(theCodePointSink);

					Om::Source::CodePointSource<> theCodePointSource(theCode);
					Reader theReader(theCodePointSource);
					Separator theSeparator;
					theSeparator.ParseElements(theReader);
					theSeparator.GiveElements(theWriter);
				}
				BOOST_CHECK_EQUAL(
					"\n\t   \n",
					theResult
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

// MARK: - Om::Language::Separator

	#define Type_ \
	Om::Language::Separator

// MARK: public (static)

inline Type_ const & Type_::GetLineSeparator() {
	static Separator const theSeparator(Symbol::theLineSeparatorSymbol);
	return theSeparator;
}

inline char const * Type_::GetName() {
	return Om_Language_Separator_GetName_();
}

// MARK: public (non-static)

inline Type_::Separator() {}

inline Type_::Separator(
	Om::Source::Source<CodePoint const> & theCodePointSource
) {
	for (
		;
		theCodePointSource;
		theCodePointSource.Pop()
	) {
		switch (*theCodePointSource) {
		default:
			return;
		Om_Language_Symbol_SeparatorSymbol_GetCases_():
			this->thisString.push_back(
				static_cast<char>(*theCodePointSource)
			);
			// Fall through.
		}
	}
}

inline Type_::Separator(Symbol::SeparatorSymbol const theSeparatorSymbol):
DefaultAtom<Separator>(
	static_cast<char>(theSeparatorSymbol)
) {
	assert(
		Symbol::theSpaceSeparatorSymbol == theSeparatorSymbol ||
		Symbol::theLineSeparatorSymbol == theSeparatorSymbol ||
		Symbol::theTabSeparatorSymbol == theSeparatorSymbol
	);
}

inline Type_ & Type_::operator =(Separator theSeparator) {
	this->Swap(theSeparator);
	return *this;
}

inline void Type_::ParseElements(Reader & theReader) {
	for (
		;
		theReader;
		theReader.Pop()
	) {
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
			continue;
		Om_Language_Symbol_SeparatorSymbol_GetCases_():
			this->thisString.push_back(
				static_cast<char>(*theReader)
			);
			// Fall through.
		}
	}
}

inline void Type_::ParseQuotedElements(Reader & theReader) {
	for (
		;
		theReader;
		theReader.Pop()
	) {}
}

template <typename TheOperand>
inline void Type_::TakeOperand(TheOperand &) {}

template <typename TheOperator>
inline void Type_::TakeOperator(TheOperator &) {}

template <typename TheProducer>
inline void Type_::TakeQuotedProducer(TheProducer &) {}

template <typename TheSeparator>
inline void Type_::TakeSeparator(TheSeparator & theSeparator) {
	assert(
		!theSeparator.IsEmpty()
	);
	this->thisString.append(theSeparator.thisString);
}

inline void Type_::TakeSeparatorSymbol(
	Symbol::SeparatorSymbol const theSymbol
) {
	this->thisString.push_back(
		static_cast<char>(theSymbol)
	);
}

	#undef Type_

// MARK: - boost::

template <>
inline void boost::swap(
	Om::Language::Separator & theFirst,
	Om::Language::Separator & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
