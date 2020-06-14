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

#ifndef Om_Language_Expression_

	#include "om/language/expression.hpp"

	#ifdef Om_Macro_Test_

		#include "om/language/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		BOOST_AUTO_TEST_SUITE(ExpressionTest)

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					(
						"{{a}{b}\n"
						"c{d}}"
					),
					System::Get().Evaluate("evaluate {{a}{b}c{d}}")
				);

				BOOST_CHECK_EQUAL(
					"{c{d}{a}{b}}",
					System::Get().Evaluate("evaluate {c{d}{a}{b}}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{a{b}{c}\n"
						"d{e}{f}}"
					),
					System::Get().Evaluate("evaluate {a{b}{c}d{e}{f}}")
				);

				BOOST_CHECK_EQUAL(
					"{c}",
					System::Get().Evaluate("evaluate {c}")
				);

				BOOST_CHECK_EQUAL(
					"{{d}}",
					System::Get().Evaluate("evaluate {{d}}")
				);

				BOOST_CHECK_EQUAL(
					"{}",
					System::Get().Evaluate("evaluate {}")
				);
			}

			BOOST_AUTO_TEST_CASE(EqualityTest) {
				// Positive match
				BOOST_CHECK_EQUAL(
					(
						"{{a{b}{c}\n"
						"d{e}}}"
					),
					System::Get().Evaluate(
						"= expression{a{b}{c}d{e}} {"
						"a{b}{c}\n"
						"d{e}"
						"}"
					)
				);

				// Positive match
				BOOST_CHECK_EQUAL(
					"{{a{b}{c}}}",
					System::Get().Evaluate("= expression{a{b}{c}} {a{b}{c}}")
				);

				// Positive match
				BOOST_CHECK_EQUAL(
					"{{a{b}}}",
					System::Get().Evaluate("= expression{a{b}} {a{b}}")
				);

				// Positive match
				BOOST_CHECK_EQUAL(
					"{{a}}",
					System::Get().Evaluate("= expression{a} {a}")
				);

				// Positive match
				BOOST_CHECK_EQUAL(
					"{{{a}}}",
					System::Get().Evaluate("= expression{{a}}{{a}}")
				);

				// Negative match
				BOOST_CHECK_EQUAL(
					"{}",
					System::Get().Evaluate("= expression{a{b}{c}} {A{B}{C}}")
				);

				// Negative match
				BOOST_CHECK_EQUAL(
					"{}",
					System::Get().Evaluate("= expression{} {a{b}{c}}")
				);

				// Positive empty match
				BOOST_CHECK_EQUAL(
					"{{}}",
					System::Get().Evaluate("= expression{} {}")
				);
			}

			BOOST_AUTO_TEST_CASE(ReadTest) {
				char const theCode[] = (
					"0\n"
					"\t {1\n"
					"\t {2\n"
					"\t } 3\n"
					"\t } {4\n"
					"\t} 5\n"
				);
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
					Expression theExpression;
					theExpression.ParseElements(theReader);
					theExpression.GiveElements(theWriter);
				}
				BOOST_CHECK_EQUAL(
					std::string(
						"0{1\n"
						"\t {2\n"
						"\t } 3\n"
						"\t }{4\n"
						"\t}\n"
						"5"
					),
					std::string(theResult)
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/language/literal.hpp"

	#ifndef Om_Macro_Precompilation_

		#include "boost/ref.hpp"
		#include "boost/utility/in_place_factory.hpp"

	#endif

// MARK: - Om::Language::Expression

	#define Type_ \
	Om::Language::Expression

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Expression_GetName_();
}

// MARK: public (non-static)

inline Type_::Expression():
thisFormDeque() {}

inline Type_ & Type_::operator =(Expression theExpression) {
	this->Swap(theExpression);
	return *this;
}

inline void Type_::BackGiveForm(Consumer & theConsumer) {
	if (
		!this->thisFormDeque.empty()
	) {
		this->thisFormDeque.back().GiveElements(theConsumer);
		this->thisFormDeque.pop_back();
	}
}

inline void Type_::BackGiveTerm(Consumer & theConsumer) {
	if (
		!this->thisFormDeque.empty()
	) {
		Form & theForm = this->thisFormDeque.back();
		if (
			theForm.BackGiveTerm(theConsumer)
		) {
			assert(
				theForm.IsEmpty()
			);
			this->thisFormDeque.pop_back();
		}
	}
}

inline void Type_::BackPopTerm() {
	assert(
		!this->thisFormDeque.empty()
	);
	Form & theForm = this->thisFormDeque.back();
	if (
		theForm.BackPopTerm()
	) {
		assert(
			theForm.IsEmpty()
		);
		this->thisFormDeque.pop_back();
	}
}

template <typename TheOperand>
inline void Type_::BackTakeOperand(TheOperand & theOperand) {
	this->GetBackTaker().BackTakeOperand(theOperand);
}

template <typename TheOperator>
inline void Type_::BackTakeOperator(TheOperator & theOperator) {
	assert(
		!theOperator.IsEmpty()
	);
	this->thisFormDeque.push_back(
		Form()
	);
	this->thisFormDeque.back().TakeOperator(theOperator);
}

template <typename TheProducer>
inline void Type_::BackTakeQuotedProducer(TheProducer & theProducer) {
	this->GetBackTaker().BackTakeQuotedProducer(theProducer);
}

inline void Type_::Clear() {
	this->thisFormDeque.clear();
}

inline void Type_::FrontGiveForm(Consumer & theConsumer) {
	if (
		!this->thisFormDeque.empty()
	) {
		this->thisFormDeque.front().GiveElements(theConsumer);
		this->thisFormDeque.pop_front();
	}
}

inline void Type_::FrontGiveTerm(Consumer & theConsumer) {
	if (
		!this->thisFormDeque.empty()
	) {
		Form & theForm = this->thisFormDeque.front();
		if (
			theForm.FrontGiveTerm(theConsumer)
		) {
			assert(
				theForm.IsEmpty()
			);
			this->thisFormDeque.pop_front();
		}
	}
}

inline void Type_::FrontPopTerm() {
	assert(
		!this->thisFormDeque.empty()
	);
	Form & theForm = this->thisFormDeque.front();
	if (
		theForm.FrontPopTerm()
	) {
		assert(
			theForm.IsEmpty()
		);
		this->thisFormDeque.pop_front();
	}
}

template <typename TheOperand>
inline void Type_::FrontTakeOperand(TheOperand & theOperand) {
	this->GetFrontTaker().FrontTakeOperand(theOperand);
}

template <typename TheOperator>
inline void Type_::FrontTakeOperator(TheOperator & theOperator) {
	assert(
		!theOperator.IsEmpty()
	);
	this->GetFrontTaker().TakeOperator(theOperator);
}

template <typename TheProducer>
inline void Type_::FrontTakeQuotedProducer(TheProducer & theProducer) {
	this->GetFrontTaker().FrontTakeQuotedProducer(theProducer);
}

inline std::auto_ptr<
	Om::Source::Source<Om::Language::Element const>
> Type_::GetElementRange() const {
	return std::auto_ptr<
		Om::Source::Source<Element const>
	>(
		new ElementRange(*this)
	);
}

inline void Type_::GiveElements(Consumer & theConsumer) {
	this->GiveElements(
		theConsumer,
		this->thisFormDeque.begin(),
		this->thisFormDeque.end()
	);
	this->Clear();
}

inline void Type_::GiveElements(Consumer & theConsumer) const {
	this->GiveElements(
		theConsumer,
		this->thisFormDeque.begin(),
		this->thisFormDeque.end()
	);
}

inline bool Type_::IsEmpty() const {
	return this->thisFormDeque.empty();
}

inline void Type_::ParseElements(Reader & theReader) {
	this->Parse<
		Operator,
		Null
	>(theReader);
}

inline void Type_::ParseQuotedElements(Reader & theReader) {
	Literal theLiteral;
	theLiteral.ParseElements(theReader);
	this->TakeQuotedProducer(theLiteral);
}

inline void Type_::Swap(Expression & theExpression) {
	this->thisFormDeque.swap(theExpression.thisFormDeque);
}

inline void Type_::TakeElements(Expression & theExpression) {
	if (
		!theExpression.IsEmpty()
	) {
		if (
			this->IsEmpty()
		) {
			this->Take(theExpression);
		} else {
			FormDeque & theFormDeque = theExpression.thisFormDeque;
			assert(
				!theFormDeque.empty()
			);

			FormDeque::iterator theCurrent = theFormDeque.begin();
			if (
				theCurrent->GetOperator().IsEmpty()
			) {
				theFormDeque.front().GiveElements(*this);
				theFormDeque.pop_front();
				if (
					theFormDeque.empty()
				) {
					return;
				}
				theCurrent = theFormDeque.begin();
			}

			FormDeque::iterator const theEnd = theFormDeque.end();
			assert(theEnd != theCurrent);
			do {
				assert(
					!theCurrent->GetOperator().IsEmpty()
				);
				this->thisFormDeque.push_back(
					Form()
				);
				this->thisFormDeque.back().Swap(*theCurrent);
			} while (theEnd != ++theCurrent);

			Expression().Swap(theExpression);
		}
	}
}

inline void Type_::TakeElements(Expression const & theExpression) {
	if (
		!theExpression.IsEmpty()
	) {
		if (
			this->IsEmpty()
		) {
			this->Take(theExpression);
		} else {
			FormDeque const & theFormDeque = theExpression.thisFormDeque;
			assert(
				!theFormDeque.empty()
			);

			FormDeque::const_iterator const theEnd = theFormDeque.end();
			FormDeque::const_iterator theCurrent = theFormDeque.begin();
			assert(theEnd != theCurrent);
			if (
				theCurrent->GetOperator().IsEmpty()
			) {
				theFormDeque.front().GiveElements(*this);
				++theCurrent;
			}
			this->thisFormDeque.insert(
				this->thisFormDeque.end(),
				theCurrent,
				theEnd
			);
		}
	}
}

inline void Type_::TakeElements(Producer & theProducer) {
	if (
		typeid(theProducer) == typeid(Expression)
	) {
		this->TakeElements(
			static_cast<Expression &>(theProducer)
		);
	} else {
		theProducer.GiveElements(*this);
	}
}

inline void Type_::TakeElements(Producer const & theProducer) {
	if (
		typeid(theProducer) == typeid(Expression const)
	) {
		this->TakeElements(
			static_cast<Expression const &>(theProducer)
		);
	} else {
		theProducer.GiveElements(*this);
	}
}

template <typename TheOperand>
inline void Type_::TakeOperand(TheOperand & theOperand) {
	assert(
		!theOperand.IsEmpty()
	);
	this->BackTakeOperand(theOperand);
}

template <typename TheOperator>
inline void Type_::TakeOperator(TheOperator & theOperator) {
	assert(
		!theOperator.IsEmpty()
	);
	this->BackTakeOperator(theOperator);
}

template <typename TheProducer>
inline void Type_::TakeQuotedProducer(TheProducer & theProducer) {
	this->BackTakeQuotedProducer(theProducer);
}

template <typename TheSeparator>
inline void Type_::TakeSeparator(TheSeparator &) {}

// MARK: private (static)

template <typename TheFormIterator>
inline void Type_::GiveElements(
	Consumer & theConsumer,
	TheFormIterator theCurrent,
	TheFormIterator const theEnd
) {
	if (theEnd != theCurrent) {
		for (
			;
			;
			theConsumer.TakeElement(
				Separator::GetLineSeparator()
			)
		) {
			assert(
				!theCurrent->IsEmpty()
			);
			theCurrent->GiveElements(theConsumer);
			if (theEnd == ++theCurrent) {
				return;
			}
		}
	}
}

// MARK: private (non-static)

inline Om::Language::Form & Type_::GetBackTaker() {
	if (
		this->thisFormDeque.empty()
	) {
		this->thisFormDeque.push_back(
			Form()
		);
	}
	return this->thisFormDeque.back();
}

inline Om::Language::Form & Type_::GetFrontTaker() {
	if (
		this->thisFormDeque.empty() ||
		!this->thisFormDeque.front().GetOperator().IsEmpty()
	) {
		this->thisFormDeque.push_front(
			Form()
		);
	}
	return this->thisFormDeque.front();
}

	#undef Type_

// MARK: - Om::Language::Expression::FormRange

	#define Type_ \
	Om::Language::Expression::FormRange

// MARK: public (non-static)

inline Type_<Om::Language::Form>::FormRange(Expression & theExpression):
Om::Source::CollectionFrontSource<
	Form,
	FormDeque::iterator
>(theExpression.thisFormDeque) {}

inline Type_<Om::Language::Form const>::FormRange(Expression const & theExpression):
Om::Source::CollectionFrontSource<
	Form const,
	FormDeque::const_iterator
>(theExpression.thisFormDeque) {}

	#undef Type_

// MARK: - Om::Language::Expression::ElementRange

	#define Type_ \
	Om::Language::Expression::ElementRange

// MARK: public (non-static)

inline Type_::ElementRange(Expression const & theExpression):
thisFormIterator(
	theExpression.thisFormDeque.begin()
),
thisFormEnd(
	theExpression.thisFormDeque.end()
),
thisFormElementRange() {
	if (this->thisFormEnd != this->thisFormIterator) {
		this->thisFormElementRange = boost::in_place(
			boost::ref(*this->thisFormIterator)
		);
		assert(*this->thisFormElementRange);
	}
}

inline bool Type_::operator !() const {
	return !this->thisFormElementRange;
}

inline Om::Language::Element const & Type_::operator *() const {
	assert(this->thisFormElementRange);
	return (
		*this->thisFormElementRange ?
		**this->thisFormElementRange :
		Separator::GetLineSeparator()
	);
}

inline bool Type_::Equals(ElementRange const & theElementRange) const {
	return (
		this->thisFormElementRange == theElementRange.thisFormElementRange &&
		this->thisFormIterator == theElementRange.thisFormIterator
	);
}

inline void Type_::End() {
	this->thisFormElementRange = boost::none;
}

inline void Type_::Pop() {
	assert(this->thisFormElementRange);
	assert(this->thisFormEnd != this->thisFormIterator);
	if (*this->thisFormElementRange) {
		this->thisFormElementRange->Pop();
		if (!*this->thisFormElementRange) {
			if (this->thisFormEnd == ++this->thisFormIterator) {
				this->End();
			}
		}
	} else {
		this->thisFormElementRange = boost::in_place(
			boost::ref(*this->thisFormIterator)
		);
		assert(*this->thisFormElementRange);
	}
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

// MARK: - boost::

template <>
inline void boost::swap(
	Om::Language::Expression & theFirst,
	Om::Language::Expression & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
