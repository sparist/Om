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

#ifndef Om_Pair_

	#include "om/pair.hpp"

#else

// MARK: - Om::Pair

	#define Type_ \
	Om::Pair

// MARK: public (static)

inline Om::Pair const & Type_::GetEmpty() {
	static Pair thePair;
	return thePair;
}

// MARK: public (non-static)

inline Type_::~Pair() {}

inline Type_::Pair() :
thisOperator(),
thisOperand()
{}

inline void Type_::ClearOperand() {
	this->thisOperand.Clear();
}

inline Om::Operand const & Type_::GetOperand() const {
	return this->thisOperand;
}

inline Om::Operator const & Type_::GetOperator() const {
	return this->thisOperator;
}

inline void Type_::GiveElements(Consumer & theConsumer) {
	this->GiveElements(
		*this,
		theConsumer
	);
	this->thisOperator.Clear();
	this->thisOperand.Clear();
}

inline void Type_::GiveElements(Consumer & theConsumer) const {
	this->GiveElements(
		*this,
		theConsumer
	);
}

inline bool Type_::IsEmpty() const {
	return (
		this->thisOperator.IsEmpty() &&
		this->thisOperand.IsEmpty()
	);
}

template <typename TheOperand>
inline void Type_::TakeOperand(TheOperand & theOperand) {
	this->thisOperand.Take(theOperand);
}

template <typename TheOperator>
inline void Type_::TakeOperator(TheOperator & theOperator) {
	this->thisOperator.Take(theOperator);
}

template <typename TheProducer>
inline void Type_::TakeQuotedProducer(TheProducer & theProducer) {
	this->thisOperand.SetProgram(
		theProducer.GiveProgram()
	);
}

// MARK: private (non-static)

template <typename ThePair>
inline void Type_::GiveElements(
	ThePair & thePair,
	Consumer & theConsumer
) {
	if (
		!thePair.thisOperator.IsEmpty()
	) {
		theConsumer.TakeElement(thePair.thisOperator);
	}
	if (
		!thePair.thisOperand.IsEmpty()
	) {
		theConsumer.TakeElement(thePair.thisOperand);
	}
}

	#undef Type_

#endif
