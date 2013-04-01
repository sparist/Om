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

#ifndef Om_DefaultConsumer_

	#include "om/default_consumer.hpp"

#else

	#include "om/producer.hpp"

// MARK: - Om::DefaultConsumer

	#define Template_ \
	template < \
		typename ThisImplementation, \
		typename ThisInterface \
	>

	#define Type_ \
	Om::DefaultConsumer< \
		ThisImplementation, \
		ThisInterface \
	>

// MARK: public (non-static)

Template_
inline Type_::~DefaultConsumer() {}

Template_
inline void Type_::TakeElement(Operand & theOperand) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this).TakeOperand(theOperand);
}

Template_
inline void Type_::TakeElement(Operand const & theOperand) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this).TakeOperand(theOperand);
}

Template_
inline void Type_::TakeElement(Operator & theOperator) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this).TakeOperator(theOperator);
}

Template_
inline void Type_::TakeElement(Operator const & theOperator) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this).TakeOperator(theOperator);
}

Template_
inline void Type_::TakeElement(Separator & theSeparator) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this).TakeSeparator(theSeparator);
}

Template_
inline void Type_::TakeElement(Separator const & theSeparator) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this).TakeSeparator(theSeparator);
}

Template_
inline void Type_::TakeElements(Producer & theProducer) {
	theProducer.GiveElements(*this);
}

Template_
inline void Type_::TakeElements(Producer const & theProducer) {
	theProducer.GiveElements(*this);
}

Template_
inline void Type_::TakeQuotedElements(Producer & theProducer) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this).TakeQuotedProducer(theProducer);
}

Template_
inline void Type_::TakeQuotedElements(Producer const & theProducer) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this).TakeQuotedProducer(theProducer);
}

	#undef Type_
	#undef Template_

#endif
