/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Literal_

	#include "om/literal.hpp"

	#ifdef Om_Macros_Test_

		#include "om/system.hpp"

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(LiteralTest)

		BOOST_AUTO_TEST_CASE(EqualityTest) {
			// Positive match
			BOOST_CHECK_EQUAL(
				"{{a{b}{c}\nd{e}}}",
				System::Get().Evaluate("= {a{b}{c}\nd{e}} {a{b}{c}\nd{e}}")
			);

			// Negative match
			BOOST_CHECK_EQUAL(
				"{}",
				System::Get().Evaluate("= {a{b}{c}} {a{b}{d}}")
			);

			// Empty match
			BOOST_CHECK_EQUAL(
				"{}",
				System::Get().Evaluate("= {} {a{b}{c}}")
			);

			// Empty match
			BOOST_CHECK_EQUAL(
				"{{}}",
				System::Get().Evaluate("= {} {}")
			);
		}

		BOOST_AUTO_TEST_CASE(RecursionTest) {
			size_t const theDepth = 50000;

			std::string theString;
			for (
				size_t theLevel = theDepth;
				theLevel;
				--theLevel
			) {
				theString = "{" + theString + "}";
			}

			Sources::CodePointSource<std::string::const_iterator> theCodePointSource(
				theString.begin(),
				theString.end()
			);
			Parser theParser(theCodePointSource);
			Literal theLiteral;
			theLiteral.ReadElements(theParser);

			Literal theCopy(theLiteral);
		}

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#include "om/operator.hpp"
	#include "om/separator.hpp"

	#ifndef Om_Macros_Precompilation_

		#include <stack>

	#endif

// MARK: - Om::Literal

	#define Type_ \
	Om::Literal

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Literal_GetName_();
}

// MARK: public (non-static)

inline Type_::~Literal() {
	// Flatten the ElementDeque to avoid recursive destructor calls.
	try {
		while (
			!this->thisElementDeque.empty()
		) {
			std::auto_ptr<Element> theElement(
				this->thisElementDeque.pop_front().release()
			);
			assert(
				theElement.get()
			);
			(*theElement)->GiveElements(*this);
		}
	} catch (...) {}
}

inline Type_::Literal():
thisElementDeque() {}

inline Type_ & Type_::operator =(Literal theLiteral) {
	this->Swap(theLiteral);
	return *this;
}

template <typename TheElement>
inline void Type_::BackGive(Consumer & theConsumer) {
	if (
		!this->thisElementDeque.empty() &&
		dynamic_cast<TheElement const *>(
			&this->thisElementDeque.back()
		)
	) {
		this->thisElementDeque.pop_back()->GiveElements(theConsumer);
	}
}

inline void Type_::BackGiveElement(Consumer & theConsumer) {
	if (
		!this->thisElementDeque.empty()
	) {
		this->thisElementDeque.pop_back()->GiveElements(theConsumer);
	}
}

inline void Type_::Clear() {
	this->thisElementDeque.clear();
}

template <typename TheElement>
inline void Type_::FrontGive(Consumer & theConsumer) {
	if (
		!this->thisElementDeque.empty() &&
		dynamic_cast<TheElement const *>(
			&this->thisElementDeque.front()
		)
	) {
		this->thisElementDeque.pop_front()->GiveElements(theConsumer);
	}
}

inline void Type_::FrontGiveElement(Consumer & theConsumer) {
	if (
		!this->thisElementDeque.empty()
	) {
		this->thisElementDeque.pop_front()->GiveElements(theConsumer);
	}
}

inline std::auto_ptr<
	Om::Source<Om::Element>
> Type_::GetElementRange() {
	return std::auto_ptr<
		Source<Element>
	>(
		new ElementRange<Literal>(*this)
	);
}

inline std::auto_ptr<
	Om::Source<Om::Element const>
> Type_::GetElementRange() const {
	return std::auto_ptr<
		Source<Element const>
	>(
		new ElementRange<Literal const>(*this)
	);
}

inline void Type_::GiveElements(Consumer & theConsumer) {
	this->GiveElements(
		theConsumer,
		this->thisElementDeque.begin(),
		this->thisElementDeque.end()
	);
	this->thisElementDeque.clear();
}

inline void Type_::GiveElements(Consumer & theConsumer) const {
	this->GiveElements(
		theConsumer,
		this->thisElementDeque.begin(),
		this->thisElementDeque.end()
	);
}

inline bool Type_::IsEmpty() const {
	return this->thisElementDeque.empty();
}

inline void Type_::ReadElements(Parser & theParser) {
	std::stack<Literal *> theStack;
	theStack.push(this);

	while (theParser) {
		switch (*theParser) {
		case Symbols::theEndOperandSymbol:
			assert(
				!theStack.empty() &&
				this != theStack.top()
			);
			theStack.pop();
			break;
		case Symbols::theStartOperandSymbol:
			{
				std::auto_ptr<Literal> theLiteral(new Literal);
				Literal * theLiteralPointer = theLiteral.get();
				{
					Operand theOperand(theLiteral);
					theStack.top()->TakeOperand(theOperand);
				}
				theStack.push(theLiteralPointer);
			}
			break;
		Om_Symbols_SeparatorSymbol_GetCases_():
			assert(
				!theStack.empty() &&
				theStack.top()
			);
			{
				Separator theSeparator(theParser);
				theStack.top()->TakeSeparator(theSeparator);
			}
			continue;
		default:
			assert(
				!theStack.empty() &&
				theStack.top()
			);
			{
				Operator theOperator(theParser);
				theStack.top()->TakeOperator(theOperator);
			}
			continue;
		}
		theParser.Pop();
	}
}

inline void Type_::ReadQuotedElements(Parser & theParser) {
	Literal theLiteral;
	theLiteral.ReadElements(theParser);
	this->TakeQuotedProducer(theLiteral);
}

inline void Type_::Swap(Literal & theLiteral) {
	this->thisElementDeque.swap(theLiteral.thisElementDeque);
}

template <typename TheOperand>
inline void Type_::TakeOperand(TheOperand & theOperand) {
	assert(
		!theOperand.IsEmpty()
	);
	this->thisElementDeque.push_back(
		Give(theOperand)
	);
}

template <typename TheOperator>
inline void Type_::TakeOperator(TheOperator & theOperator) {
	assert(
		!theOperator.IsEmpty()
	);
	this->TakeAtom(theOperator);
}

template <typename TheProducer>
inline void Type_::TakeQuotedProducer(TheProducer & theProducer) {
	this->thisElementDeque.push_back(
		new Operand(
			theProducer.GiveProgram()
		)
	);
}

template <typename TheSeparator>
inline void Type_::TakeSeparator(TheSeparator & theSeparator) {
	assert(
		!theSeparator.IsEmpty()
	);
	this->TakeAtom(theSeparator);
}

// MARK: private (static)

template <typename TheElementIterator>
inline void Type_::GiveElements(
	Consumer & theConsumer,
	TheElementIterator theCurrent,
	TheElementIterator const theEnd
) {
	for (
		;
		theEnd != theCurrent;
		++theCurrent
	) {
		theCurrent->GiveElements(theConsumer);
	}
}

// MARK: private (non-static)

template <typename TheAtom>
inline void Type_::TakeAtom(TheAtom & theAtom) {
	assert(
		!theAtom.IsEmpty()
	);
	if (
		this->thisElementDeque.empty() ||
		!this->thisElementDeque.back().Merge(theAtom)
	) {
		this->thisElementDeque.push_back(
			Give(theAtom)
		);
	}
}

	#undef Type_

// MARK: - Om::Literal::ElementRange

	#define Type_ \
	Om::Literal::ElementRange

// MARK: public (non-static)

inline Type_<Om::Literal>::ElementRange(Literal & theLiteral):
Sources::CollectionFrontSource<
	Element,
	ElementDeque::iterator
>(theLiteral.thisElementDeque) {}

inline Type_<Om::Literal const>::ElementRange(Literal const & theLiteral):
Sources::CollectionFrontSource<
	Element const,
	ElementDeque::const_iterator
>(theLiteral.thisElementDeque) {}

	#undef Type_

// MARK: - boost::

template <>
inline void boost::swap(
	Om::Literal & theFirst,
	Om::Literal & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
