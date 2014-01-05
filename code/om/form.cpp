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

#ifndef Om_Form_

	#include "om/form.hpp"

#else

// MARK: - Om::Form

	#define Type_ \
	Om::Form

// MARK: public (non-static)

inline Type_::Form():
thisOperator(),
thisOperandDeque() {}

inline bool Type_::BackGiveTerm(Consumer & theConsumer) {
	if (
		this->thisOperandDeque.empty()
	) {
		assert(
			!this->thisOperator.IsEmpty()
		);
		this->thisOperator.GiveElements(theConsumer);
		assert(
			this->thisOperator.IsEmpty()
		);
		return true;
	}
	this->thisOperandDeque.back().GiveElements(theConsumer);
	this->thisOperandDeque.pop_back();
	return this->IsEmpty();
}

inline bool Type_::BackPopTerm() {
	if (
		this->thisOperandDeque.empty()
	) {
		assert(
			!this->thisOperator.IsEmpty()
		);
		Operator().Swap(this->thisOperator);
		return true;
	}
	this->thisOperandDeque.pop_back();
	return this->IsEmpty();
}

template <typename TheOperand>
inline void Type_::BackTakeOperand(TheOperand & theOperand) {
	this->thisOperandDeque.push_back(
		Operand()
	);
	this->thisOperandDeque.back().Take(theOperand);
}

template <typename TheProducer>
inline void Type_::BackTakeQuotedProducer(TheProducer & theProducer) {
	this->thisOperandDeque.push_back(
		Operand()
	);
	this->thisOperandDeque.back().SetProgram(
		theProducer.GiveProgram()
	);
}

inline bool Type_::FrontGiveTerm(Consumer & theConsumer) {
	if (
		this->thisOperator.IsEmpty()
	) {
		assert(
			!this->thisOperandDeque.empty()
		);
		this->thisOperandDeque.front().GiveElements(theConsumer);
		this->thisOperandDeque.pop_front();
	} else {
		this->thisOperator.GiveElements(theConsumer);
		assert(
			this->thisOperator.IsEmpty()
		);
	}
	return this->thisOperandDeque.empty();
}

inline bool Type_::FrontPopTerm() {
	if (
		this->thisOperator.IsEmpty()
	) {
		assert(
			!this->thisOperandDeque.empty()
		);
		this->thisOperandDeque.pop_front();
	} else {
		Operator().Swap(this->thisOperator);
		assert(
			this->thisOperator.IsEmpty()
		);
	}
	return this->thisOperandDeque.empty();
}

template <typename TheOperand>
inline void Type_::FrontTakeOperand(TheOperand & theOperand) {
	this->thisOperandDeque.push_front(
		Operand()
	);
	this->thisOperandDeque.front().Take(theOperand);
}

template <typename TheProducer>
inline void Type_::FrontTakeQuotedProducer(TheProducer & theProducer) {
	this->thisOperandDeque.push_front(
		Operand()
	);
	this->thisOperandDeque.front().SetProgram(
		theProducer.GiveProgram()
	);
}

inline Om::Operator const & Type_::GetOperator() const {
	return this->thisOperator;
}

inline void Type_::GiveElements(Consumer & theConsumer) {
	this->GiveElements<OperandDeque::iterator>(
		*this,
		theConsumer
	);
	this->thisOperandDeque.clear();
}

inline void Type_::GiveElements(Consumer & theConsumer) const {
	this->GiveElements<OperandDeque::const_iterator>(
		*this,
		theConsumer
	);
}

inline bool Type_::IsEmpty() const {
	return (
		this->thisOperator.IsEmpty() &&
		this->thisOperandDeque.empty()
	);
}

inline void Type_::Swap(Form & theForm) {
	this->thisOperator.Swap(theForm.thisOperator);
	this->thisOperandDeque.swap(theForm.thisOperandDeque);
}

template <typename TheOperator>
inline void Type_::TakeOperator(TheOperator & theOperator) {
	assert(
		!theOperator.IsEmpty()
	);
	this->thisOperator.Take(theOperator);
}

// MARK: private (static)

template <
	typename TheOperandIterator,
	typename TheForm
>
inline void Type_::GiveElements(
	TheForm & theForm,
	Consumer & theConsumer
) {
	assert(
		!theForm.IsEmpty()
	);
	if (
		!theForm.thisOperator.IsEmpty()
	) {
		theConsumer.TakeElement(theForm.thisOperator);
	}
	TheOperandIterator const theEnd = theForm.thisOperandDeque.end();
	for (
		TheOperandIterator theCurrent = theForm.thisOperandDeque.begin();
		theEnd != theCurrent;
		++theCurrent
	) {
		theConsumer.TakeElement(*theCurrent);
	}
}

	#undef Type_

// MARK: - Om::Form::ElementRange

	#define Type_ \
	Om::Form::ElementRange

// MARK: public (non-static)

inline Type_::ElementRange(Form const & theForm):
thisOperandIterator(
	theForm.thisOperandDeque.begin()
),
thisOperandEnd(
	theForm.thisOperandDeque.end()
),
thisElement(&theForm.thisOperator) {
	if (
		theForm.thisOperator.IsEmpty()
	) {
		assert(this->thisOperandEnd != this->thisOperandIterator);
		this->thisElement = &*this->thisOperandIterator++;
	}
}

inline bool Type_::operator !() const {
	return !this->thisElement;
}

inline Om::Element const & Type_::operator *() const {
	assert(this->thisElement);
	return *this->thisElement;
}

inline bool Type_::Equals(ElementRange const & theElementRange) const {
	return this->thisElement == theElementRange.thisElement;
}

inline void Type_::End() {
	this->thisElement = 0;
}

inline void Type_::Pop() {
	assert(this->thisElement);
	this->thisElement = (
		this->thisOperandEnd == this->thisOperandIterator ?
		0 :
		&*this->thisOperandIterator++
	);
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

// MARK: - Om::Form::OperandRange

	#define Type_ \
	Om::Form::OperandRange

// MARK: public (non-static)

inline Type_<Om::Operand>::OperandRange(Form & theForm):
Om::Source::CollectionFrontSource<
	Operand,
	OperandDeque::iterator
>(theForm.thisOperandDeque) {}

inline Type_<Om::Operand const>::OperandRange(Form const & theForm):
Om::Source::CollectionFrontSource<
	Operand const,
	OperandDeque::const_iterator
>(theForm.thisOperandDeque) {}

	#undef Type_

// MARK: - boost::

template <>
inline void boost::swap(
	Om::Form & theFirst,
	Om::Form & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
