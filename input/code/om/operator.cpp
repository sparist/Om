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

#ifndef Om_Operator_

	#include "om/operator.hpp"

	#ifdef Om_Macro_Test_

		#include "om/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(OperatorTest)

		BOOST_AUTO_TEST_CASE(BasicTest) {
			BOOST_CHECK_EQUAL(
				"{a` `{b`}}",
				System::Get().Evaluate("operator{a {b}}")
			);
		}

		BOOST_AUTO_TEST_CASE(DereferenceTest) {
			{
				Operator theMutableOperator;
				Atom & theMutableAtom = theMutableOperator;
				Program & theMutableDereference = *theMutableAtom;
				BOOST_CHECK(
					typeid(theMutableDereference) == typeid(Null)
				);
			}

			{
				Operator const theImmutableOperator;
				Atom const & theImmutableAtom = theImmutableOperator;
				Program const & theImmutableDereference = *theImmutableAtom;
				BOOST_CHECK(
					typeid(theImmutableDereference) == typeid(Null)
				);
			}
		}

		BOOST_AUTO_TEST_CASE(EqualityTest) {
			// Positive match
			BOOST_CHECK_EQUAL(
				"{{test` `{ing`}}}",
				System::Get().Evaluate("= operator{test {ing}} {test` `{ing`}}")
			);

			// Positive match
			BOOST_CHECK_EQUAL(
				"{{a`{b`}`{c`}`\nd`{e`}}}",
				System::Get().Evaluate("= operator{a{b}{c}\nd{e}} {a`{b`}`{c`}`\nd`{e`}}")
			);

			// Negative match
			BOOST_CHECK_EQUAL(
				"{}",
				System::Get().Evaluate("= operator{a{b}{c}} {a`{b`}`{d`}}")
			);

			// Empty match
			BOOST_CHECK_EQUAL(
				"{}",
				System::Get().Evaluate("= operator{} {a{b}{c}}")
			);

			// Empty match
			BOOST_CHECK_EQUAL(
				"{{}}",
				System::Get().Evaluate("= operator{} {}")
			);
		}

		BOOST_AUTO_TEST_CASE(TakeQuotedElementsTest) {
			Operator theOperator;
			{
				Literal theLiteral;
				{
					Source::CodePointSource<> theCodePointSource("a{b{c}}");
					Parser theParser(theCodePointSource);
					theLiteral.ReadElements(theParser);
				}
				theOperator.TakeQuotedProducer(theLiteral);
				assert(
					theLiteral.IsEmpty()
				);
			}
			BOOST_CHECK_EQUAL(
				"{a{b{c}}}",
				theOperator.GetString()
			);
		}

		BOOST_AUTO_TEST_CASE(NormalizationTest) {
			// Test combining character reordering under NFD.
			Operator theFirst("s\xCC\x87");
			Operator theSecond("\xCC\xA3");
			theFirst.TakeElement(theSecond);
			BOOST_CHECK_EQUAL(
				"s\xCC\xA3\xCC\x87",
				theFirst.GetString()
			);
		}

		BOOST_AUTO_TEST_CASE(ReadTest) {
			char const theCode[] = "0\n\t {1\n\t {2\n\t } 3\n\t } {4\n\t} 5\n";
			std::string theResult;
			{
				Sink::CodePointSink<
					std::back_insert_iterator<std::string>
				> theCodePointSink(
					std::back_inserter(theResult)
				);
				Writer theWriter(theCodePointSink);

				Source::CodePointSource<> theCodePointSource(theCode);
				Parser theParser(theCodePointSource);
				Operator theOperator;
				theOperator.ReadElements(theParser);
				theOperator.GiveElements(theWriter);
			}
			BOOST_CHECK_EQUAL(
				(
					"0`\n"
					"`\t` `{1`\n"
					"`\t` `{2`\n"
					"`\t` `}` 3`\n"
					"`\t` `}` `{4`\n"
					"`\t`}` 5`\n"
				),
				theResult
			);
		}

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#include "om/operand.hpp"
	#include "om/separator.hpp"
	#include "om/sink/code_point_sink.hpp"
	#include "om/source/code_point_source.hpp"
	#include "om/source/code_point_string_back_source.hpp"
	#include "om/source/code_point_string_front_source.hpp"
	#include "om/writer.hpp"

// MARK: - Om::Operator

	#define Type_ \
	Om::Operator

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operator_GetName_();
}

// MARK: public (non-static)

inline Type_::Operator() {}

inline Type_::Operator(std::string const & theString) {
	boost::locale::normalize(
		theString,
		boost::locale::norm_nfd
	).swap(this->thisString);
}

inline Type_::Operator(
	char const theCodeUnitIterator[]
) {
	boost::locale::normalize(
		theCodeUnitIterator,
		boost::locale::norm_nfd
	).swap(this->thisString);
}

inline Type_::Operator(
	Source::Source<CodePoint const> & theCodePointSource
) {
	std::string theString;
	for (
		std::back_insert_iterator<std::string> theInserter(theString);
		theCodePointSource;
		theCodePointSource.Pop()
	) {
		switch (*theCodePointSource) {
		Om_Symbol_OperandSymbol_GetCases_():
			// Fall through.
		Om_Symbol_SeparatorSymbol_GetCases_():
			break;
		case Symbol::theEncodeOperatorSymbol:
			theCodePointSource.Pop();
			if (!theCodePointSource) {
				theString.push_back(Symbol::theEndOperandSymbol);
				break;
			}
			// Fall through.
		default:
			Utf8::encode(
				*theCodePointSource,
				theInserter
			);
			continue;
		}
		break;
	}
	boost::locale::normalize(
		theString,
		boost::locale::norm_nfd
	).swap(this->thisString);
}

inline Type_::Operator(Symbol::OperandSymbol const theOperandSymbol) :
DefaultAtom<Operator>(
	static_cast<char>(theOperandSymbol)
)
{}

inline Type_::Operator(Symbol::OperatorSymbol const theOperatorSymbol) :
DefaultAtom<Operator>(
	static_cast<char>(theOperatorSymbol)
)
{}

inline Type_::Operator(Symbol::SeparatorSymbol const theSeparatorSymbol) :
DefaultAtom<Operator>(
	static_cast<char>(theSeparatorSymbol)
)
{}

inline Type_ & Type_::operator =(Operator theOperator) {
	this->Swap(theOperator);
	return *this;
}

inline void Type_::BackGiveCodePoint(Consumer & theConsumer) {
	if (
		!this->thisString.empty()
	) {
		Operator theOperator;
		{
			std::string & theString = theOperator.thisString;
			{
				Source::CodePointStringBackSource<std::string::const_iterator> theCodePointStringRange(
					this->thisString.begin(),
					this->thisString.end()
				);
				assert(theCodePointStringRange);
				theCodePointStringRange->swap(theString);
			}
			assert(
				!theString.empty()
			);
			this->thisString.erase(
				this->thisString.size() - theString.size()
			);
		}
		theConsumer.TakeElement(theOperator);
	}
}

template <boost::locale::boundary::boundary_type theSegment>
inline void Type_::BackGiveSegment(Consumer & theConsumer) {
	if (
		!this->thisString.empty()
	) {
		Operator theOperator;
		{
			std::string & theString = theOperator.thisString;
			{
				typedef boost::locale::boundary::segment_index<std::string::const_iterator> SegmentCollection;

				typedef SegmentCollection::const_iterator SegmentIterator;

				SegmentCollection const theSegmentCollection(
					static_cast<boost::locale::boundary::boundary_type>(theSegment),
					this->thisString.begin(),
					this->thisString.end()
				);

				SegmentIterator theSegmentIterator(
					theSegmentCollection.end()
				);
				assert(
					theSegmentCollection.begin() != theSegmentIterator
				);
				--theSegmentIterator;
				theSegmentIterator->str().swap(theString);
			}
			assert(
				!theString.empty()
			);
			this->thisString.erase(
				this->thisString.size() - theString.size()
			);
		}
		theConsumer.TakeElement(theOperator);
	}
}

template <typename TheConsumer>
inline void Type_::Decode(TheConsumer & theConsumer) const {
	Source::CodePointSource<std::string::const_iterator> theCodePointSource(
		this->thisString.begin(),
		this->thisString.end()
	);
	Parser theParser(theCodePointSource);
	theConsumer.ReadElements(theParser);
}

template <typename TheProducer>
inline void Type_::Encode(TheProducer & theProducer) {
	this->thisString.clear();
	Sink::CodePointSink<
		std::back_insert_iterator<std::string>
	> theCodePointSink(
		std::back_inserter(this->thisString)
	);
	Writer theWriter(theCodePointSink);
	theProducer.GiveElements(theWriter);
}

inline void Type_::FrontGiveCodePoint(Consumer & theConsumer) {
	if (
		!this->thisString.empty()
	) {
		Operator theOperator;
		{
			std::string & theString = theOperator.thisString;
			{
				Source::CodePointStringFrontSource<std::string::const_iterator> theCodePointStringRange(
					this->thisString.begin(),
					this->thisString.end()
				);
				assert(theCodePointStringRange);
				theCodePointStringRange->swap(theString);
			}
			assert(
				!theString.empty()
			);
			this->thisString.erase(
				0,
				theString.size()
			);
		}
		theConsumer.TakeElement(theOperator);
	}
}

template <boost::locale::boundary::boundary_type theSegment>
inline void Type_::FrontGiveSegment(Consumer & theConsumer) {
	if (
		!this->thisString.empty()
	) {
		Operator theOperator;
		{
			std::string & theString = theOperator.thisString;
			{
				typedef boost::locale::boundary::segment_index<std::string::const_iterator> SegmentCollection;

				SegmentCollection const theSegmentCollection(
					static_cast<boost::locale::boundary::boundary_type>(theSegment),
					this->thisString.begin(),
					this->thisString.end()
				);

				SegmentCollection::const_iterator const theSegmentIterator(
					theSegmentCollection.begin()
				);
				assert(
					theSegmentCollection.end() != theSegmentIterator
				);
				theSegmentIterator->str().swap(theString);
			}
			assert(
				!theString.empty()
			);
			this->thisString.erase(
				0,
				theString.size()
			);
		}
		theConsumer.TakeElement(theOperator);
	}
}

inline void Type_::Normalize() {
	boost::locale::normalize(
		this->thisString,
		boost::locale::norm_nfkd
	).swap(this->thisString);
}

inline void Type_::ReadElements(Parser & theParser) {
	while (theParser) {
		switch (*theParser) {
		case Symbol::theEndOperandSymbol:
			// Fall through.
		case Symbol::theStartOperandSymbol:
			// Fall through.
		Om_Symbol_SeparatorSymbol_GetCases_():
			this->thisString.push_back(
				static_cast<char>(*theParser)
			);
			theParser.Pop();
			continue;
		}
		Operator theOperator(theParser);
		this->TakeOperator(theOperator);
	}
}

inline void Type_::ReadQuotedElements(Parser & theParser) {
	this->thisString.push_back(Symbol::theStartOperandSymbol);
	this->ReadElements(theParser);
	this->thisString.push_back(Symbol::theEndOperandSymbol);
}

template <typename TheOperand>
inline void Type_::TakeOperand(TheOperand & theOperand) {
	assert(
		!theOperand.IsEmpty()
	);
	this->TakeQuotedProducer(
		*theOperand.GetProgram()
	);
}

template <typename TheOperator>
inline void Type_::TakeOperator(TheOperator & theOperator) {
	assert(
		typeid(theOperator) == typeid(*this)
	);
	assert(
		!theOperator.IsEmpty()
	);
	assert(
		boost::locale::normalize(
			theOperator.thisString,
			boost::locale::norm_nfd
		) == theOperator.thisString &&
		"Operator strings must be NFC normalized."
	);

	if (
		this->IsEmpty()
	) {
		this->Take(theOperator);
		return;
	}

	this->thisString.append(theOperator.thisString);

	// Normalization is required even when combining two NFD-normalized strings.
	// TODO: Optimize to only do an incremental normalization at the boundary.
	boost::locale::normalize(
		this->thisString,
		boost::locale::norm_nfd
	).swap(this->thisString);
}

template <typename TheProducer>
inline void Type_::TakeQuotedProducer(TheProducer & theProducer) {
	this->thisString.push_back(Symbol::theStartOperandSymbol);
	theProducer.GiveElements(*this);
	this->thisString.push_back(Symbol::theEndOperandSymbol);
}

template <typename TheSeparator>
inline void Type_::TakeSeparator(TheSeparator & theSeparator) {
	assert(
		!theSeparator.IsEmpty()
	);
	this->thisString.append(
		theSeparator.GetString()
	);
}

	#undef Type_

// MARK: - boost::

template <>
inline void boost::swap(
	Om::Operator & theFirst,
	Om::Operator & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
