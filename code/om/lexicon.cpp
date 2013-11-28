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

#ifndef Om_Lexicon_

	#include "om/lexicon.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(LexiconTest)

		BOOST_AUTO_TEST_CASE(BasicTest) {
			BOOST_CHECK_EQUAL(
				(
					"{a{A}\n"
					"b{B}}"
				),
				System::Get().Evaluate("lexicon {a {A} b {B}}")
			);

			BOOST_CHECK_EQUAL(
				(
					"{b\n"
					"a}"
				),
				System::Get().Evaluate("->[lexicon]{b} lexicon{a}")
			);
		}

		BOOST_AUTO_TEST_CASE(CopyTest) {
			BOOST_CHECK_EQUAL(
				"{{a}}{a}",
				System::Get().Evaluate("quote copy lexicon{a}")
			);

			BOOST_CHECK_EQUAL(
				"{b\n"
				"a}{a}",
				System::Get().Evaluate("->[lexicon]{b} copy lexicon{a}")
			);

			BOOST_CHECK_EQUAL(
				(
					"{b\n"
					"a}{a}"
				),
				System::Get().Evaluate("->[lexicon]{b}copy{a}")
			);

			BOOST_CHECK_EQUAL(
				(
					"{b\n"
					"a}{a}"
				),
				System::Get().Evaluate("->[lexicon]{b}copy lexicon{a}")
			);

			BOOST_CHECK_EQUAL(
				(
					"{a\n"
					"b}{a}"
				),
				System::Get().Evaluate("[lexicon]<-{b}copy lexicon{a}")
			);

			BOOST_CHECK_EQUAL(
				(
					"{a{A}\n"
					"b{B}\n"
					"c{C}}{"
					"a{A}\n"
					"b{B}}"
				),
				System::Get().Evaluate(
					"[lexicon]<- {{C}} [lexicon]<- {c} "
					"copy lexicon {a {A} b {B}}"
				)
			);
		}

		BOOST_AUTO_TEST_CASE(EqualityTest) {
			// Positive match
			BOOST_CHECK_EQUAL(
				(
					"{{a{b}\n"
					"c{d}}}"
				),
				System::Get().Evaluate(
					"= lexicon{a{b}c{d}} {"
					"a{b}\n"
					"c{d}"
					"}"
				)
			);

			// Positive match
			BOOST_CHECK_EQUAL(
				"{{a{b}}}",
				System::Get().Evaluate("= lexicon{a{b}} {a{b}}")
			);

			// Positive match
			BOOST_CHECK_EQUAL(
				"{{{b}}}",
				System::Get().Evaluate("= lexicon{{b}} {{b}}")
			);

			// Negative match
			BOOST_CHECK_EQUAL(
				"{}",
				System::Get().Evaluate("= lexicon{a{b}} {a{c}}")
			);

			// Empty match
			BOOST_CHECK_EQUAL(
				"{}",
				System::Get().Evaluate("= lexicon{} {a{b}}")
			);

			// Empty match
			BOOST_CHECK_EQUAL(
				"{{}}",
				System::Get().Evaluate("= lexicon{} {}")
			);
		}

		BOOST_AUTO_TEST_CASE(ReadTest) {
			char const theCode[] = "0\n\t {1\n\t {2\n\t } 3\n\t } 4\n\t";
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
				Lexicon theLexicon;
				theLexicon.ReadElements(theParser);
				theLexicon.GiveElements(theWriter);
			}
			BOOST_CHECK_EQUAL(
				(
					"0{1\n\t {2\n\t } 3\n\t }\n"
					"4"
				),
				theResult
			);
		}

		BOOST_AUTO_TEST_CASE(NormalizationTest) {
			BOOST_CHECK_EQUAL(
				(
					"{B{2}\n"
					"C\n"
					"A{4}\n"
					"D\n"
					"E{5}}"
				),
				System::Get().Evaluate("lexicon{A{1} B{2} A{3} C A{4} D E{5}}")
			);

			BOOST_CHECK_EQUAL(
				(
					"{A{2}\n"
					"{3}}"
				),
				System::Get().Evaluate("lexicon{{1}A{2}{3}}")
			);

			BOOST_CHECK_EQUAL(
				(
					"{A{1}\n"
					"B\n"
					"C{3}\n"
					"{4}}"
				),
				System::Get().Evaluate("lexicon{ A{1}{2} B C{3}{4} }")
			);

			BOOST_CHECK_EQUAL(
				(
					"{{2}\n"
					"A{3}}"
				),
				System::Get().Evaluate("->[lexicon]{ A{1}{2} }{ A{3} }")
			);

			BOOST_CHECK_EQUAL(
				(
					"{{3}\n"
					"A{1}}"
				),
				System::Get().Evaluate("[lexicon]<-{ A{1} }{ A{2}{3} }")
			);
		}

		BOOST_AUTO_TEST_CASE(TakeQuotedProducerTest) {

			class Local {

			public:

				static void Check(Lexicon const & theLexicon) {
					Separator const & theLineSeparator = Separator::GetLineSeparator();
					Operand theOperand(
						Give(theLineSeparator)
					);

					Lexicon::ElementRange theElementRange(theLexicon);
					Lexicon::ElementRange theOtherElementRange(theLexicon);
					BOOST_CHECK(theElementRange);
					BOOST_CHECK(theElementRange == theOtherElementRange);
					Element const & theElement = *theElementRange;
					BOOST_CHECK(theOperand == theElement);
					theElementRange.Pop();
					theOtherElementRange.Pop();
					BOOST_CHECK(!theElementRange);
					BOOST_CHECK(theElementRange == theOtherElementRange);
				}

			};

			Lexicon theLexicon;
			Separator const & theLineSeparator = Separator::GetLineSeparator();
			theLexicon.TakeQuotedProducer(theLineSeparator);

			Lexicon theCopiedLexicon;
			theCopiedLexicon = theLexicon;
			BOOST_CHECK(theLexicon == theCopiedLexicon);

			Local::Check(theLexicon);
			Local::Check(theCopiedLexicon);
		}

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#include "om/evaluation.hpp"
	#include "om/literal.hpp"
	#include "om/system.hpp"

// MARK: - Om::Lexicon

	#define Type_ \
	Om::Lexicon

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Lexicon_GetName_();
}

// MARK: public (non-static)

inline Type_::Lexicon() :
thisMap(),
thisPairList() {}

inline Type_::Lexicon(Lexicon const & theLexicon) :
DefaultProgram<Lexicon>(theLexicon),
thisMap(),
thisPairList() {
	for (
		PairList::Node const * theNode = theLexicon.thisPairList.GetNode(PairList::theFrontNodeIndex);
		theNode;
		theNode = theNode->GetNode(PairList::theBackNodeIndex)
	) {
		std::auto_ptr<PairList::Node> theNewNode(
			new PairList::Node(*theNode)
		);
		assert(
			theNewNode.get()
		);

		this->thisPairList.LinkNode(
			PairList::theBackNodeIndex,
			*theNewNode
		);

		this->thisMap.insert(
			theNode->GetValue().GetOperator().GetString(),
			theNewNode
		);
	}
}

inline Type_ & Type_::operator =(Lexicon theLexicon) {
	this->Swap(theLexicon);
	return *this;
}

inline void Type_::BackGivePair(Consumer & theConsumer) {
	this->GivePair(
		PairList::theBackNodeIndex,
		theConsumer
	);
}

inline void Type_::Clear() {
	this->thisPairList.Clear();
	this->thisMap.clear();
}

inline Om::Pair const & Type_::Find(Operator const & theOperator) const {
	typedef Map::const_iterator Iterator;
	Iterator theIterator(
		this->thisMap.find(
			theOperator.GetString()
		)
	);
	if (
		this->thisMap.end() == theIterator
	) {
		return Pair::GetEmpty();
	}
	return theIterator->second->GetValue();
}

inline void Type_::FrontGivePair(Consumer & theConsumer) {
	this->GivePair(
		PairList::theFrontNodeIndex,
		theConsumer
	);
}

inline std::auto_ptr<
	Om::Source::Source<Om::Element const>
> Type_::GetElementRange() const {
	return std::auto_ptr<
		Source::Source<Element const>
	>(
		new ElementRange(*this)
	);
}

inline void Type_::GiveElements(Consumer & theConsumer) {
	this->GiveElements(
		this->thisPairList.GetNode(PairList::theFrontNodeIndex),
		theConsumer
	);
	this->Clear();
}

inline void Type_::GiveElements(Consumer & theConsumer) const {
	this->GiveElements(
		this->thisPairList.GetNode(PairList::theFrontNodeIndex),
		theConsumer
	);
}

inline bool Type_::IsEmpty() const {
	assert(
		!this->thisMap.empty() ||
		this->thisPairList.IsEmpty()
	);
	return this->thisMap.empty();
}

inline void Type_::ReadElements(Parser & theParser) {
	theParser.Parse<
		Operator,
		Null
	>(*this);
}

inline void Type_::ReadQuotedElements(Parser & theParser) {
	Literal theLiteral;
	theLiteral.ReadElements(theParser);
	this->TakeQuotedProducer(theLiteral);
}

inline void Type_::Swap(Lexicon & theLexicon) {
	this->thisMap.swap(theLexicon.thisMap);
	this->thisPairList.Swap(theLexicon.thisPairList);
}

template <typename TheOperand>
inline void Type_::TakeOperand(TheOperand & theOperand) {
	assert(
		!theOperand.IsEmpty()
	);
	this->GetOperandTaker().GetValue().TakeOperand(theOperand);
}

template <typename TheOperator>
inline void Type_::TakeOperator(TheOperator & theOperator) {
	assert(
		!theOperator.IsEmpty()
	);
	this->GetOperandTaker(theOperator);
}

template <typename TheProducer>
inline void Type_::TakeQuotedProducer(TheProducer & theProducer) {
	this->GetOperandTaker().GetValue().TakeQuotedProducer(theProducer);
}

template <typename TheSeparator>
inline void Type_::TakeSeparator(TheSeparator &) {}

inline bool Type_::Translate(
	Evaluation & theEvaluation,
	Operator const & theOperator
) const {
	Pair const & thePair = this->Find(theOperator);
	if (
		thePair.IsEmpty()
	) {
		return false;
	}

	Operand const & theOperand = thePair.GetOperand();
	if (
		theOperand.IsEmpty()
	) {
		assert(
			thePair.GetOperator() == theOperator
		);
		return System::Get().Translate(
			theEvaluation,
			theOperator
		);
	}

	theEvaluation.TakeProducer(
		*theOperand.GetProgram()
	);
	return true;
}

// MARK: private (static)

template <typename TheNode>
inline void Type_::GiveElements(
	TheNode * theNode,
	Consumer & theConsumer
) {
	if (theNode) {
		for (
			;
			;
			theConsumer.TakeElement(
				Separator::GetLineSeparator()
			)
		) {
			assert(
				theNode &&
				!theNode->GetValue().IsEmpty()
			);
			theNode->GetValue().GiveElements(theConsumer);
			theNode = theNode->GetNode(PairList::theBackNodeIndex);
			if (!theNode) {
				break;
			}
		}
	}
}

// MARK: private (non-static)

inline Type_::PairList::Node & Type_::GetOperandTaker() {
	PairList::Node * const theNode = this->thisPairList.GetNode(PairList::theBackNodeIndex);
	if (
		!theNode ||
		!theNode->GetValue().GetOperand().IsEmpty()
	) {
		Operator const theOperator;
		return this->GetOperandTaker(theOperator);
	}
	return *theNode;
}

template <typename TheOperator>
inline Type_::PairList::Node & Type_::GetOperandTaker(TheOperator & theOperator) {
	std::string const & theString = theOperator.GetString();
	typename Map::iterator const theIterator = this->thisMap.find(theString);
	if (
		this->thisMap.end() == theIterator
	) {
		PairList::Node * theNode;
		{
			std::auto_ptr<PairList::Node> theNewNode(new PairList::Node);
			theNode = theNewNode.get();
			this->thisMap.insert(
				theString,
				theNewNode
			);
		}
		assert(theNode);

		theNode->GetValue().TakeOperator(theOperator); // May swap.
		assert(
			theNode->GetValue().GetOperand().IsEmpty()
		);

		this->thisPairList.LinkNode(
			PairList::theBackNodeIndex,
			*theNode
		);

		return *theNode;
	}
	{
		PairList::Node & theNode = *theIterator->second;

		theNode.GetValue().ClearOperand();

		this->thisPairList.RelinkNode(
			PairList::theBackNodeIndex,
			theNode
		);

		return theNode;
	}
}

inline void Type_::GivePair(
	PairList::NodeIndex const theNodeIndex,
	Consumer & theConsumer
) {
	if (
		PairList::Node const * const theNode = this->thisPairList.UnlinkNode(theNodeIndex)
	) {
		Map::iterator const theIterator = this->thisMap.find(
			theNode->GetValue().GetOperator().GetString()
		);
		assert(
			this->thisMap.end() != theIterator
		);

		Map::auto_type theOldNode = this->thisMap.release(theIterator);
		assert(theOldNode);
		theOldNode->GetValue().GiveElements(theConsumer);
	}
}

// MARK: - boost::

template <>
inline void boost::swap(
	Type_ & theFirst,
	Type_ & theSecond
) {
	theFirst.Swap(theSecond);
}

	#undef Type_

// MARK: - Om::Lexicon::ElementRange

	#define Type_ \
	Om::Lexicon::ElementRange

// MARK: public (non-static)

inline Type_::ElementRange() :
thisNode(),
thisOffset() {}

inline Type_::ElementRange(Lexicon const & theLexicon) :
thisNode(
	theLexicon.thisPairList.GetNode(PairList::theFrontNodeIndex)
),
thisOffset(
	this->thisNode &&
	thisNode->GetValue().GetOperator().IsEmpty()
) {}

inline bool Type_::operator !() const {
	return !this->thisNode;
}

inline Om::Element const & Type_::operator *() const {
	assert(this->thisNode);
	switch (this->thisOffset) {
	case 0:
		assert(
			!this->thisNode->GetValue().GetOperator().IsEmpty()
		);
		return this->thisNode->GetValue().GetOperator();
	case 1:
		assert(
			!this->thisNode->GetValue().GetOperand().IsEmpty()
		);
		return this->thisNode->GetValue().GetOperand();
	default:
		return Separator::GetLineSeparator();
	}
}

inline bool Type_::Equals(ElementRange const & theElementRange) const {
	return (
		this->thisNode == theElementRange.thisNode &&
		this->thisOffset == theElementRange.thisOffset
	);
}

inline void Type_::Pop() {
	assert(
		this->thisNode &&
		!this->thisNode->GetValue().IsEmpty()
	);
	switch (this->thisOffset) {
	case 0:
		if (
			!this->thisNode->GetValue().GetOperand().IsEmpty()
		) {
			this->thisOffset = 1;
			return;
		}
		// Fall through.
	case 1:
		this->thisNode = this->thisNode->GetNode(PairList::theBackNodeIndex);
		this->thisOffset = 2;
		return;
	default:
		this->thisOffset = this->thisNode->GetValue().GetOperator().IsEmpty();
		// Fall through.
	}
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
