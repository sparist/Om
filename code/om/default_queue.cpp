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

#ifndef Om_DefaultQueue_

	#include "om/default_queue.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(DefaultQueueTest)

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

// MARK: - Om::DefaultQueue

	#define Template_ \
	template < \
		typename ThisImplementation, \
		typename ThisInterface \
	>

	#define Type_ \
	Om::DefaultQueue< \
		ThisImplementation, \
		ThisInterface \
	>

// MARK: public (non-static)

Template_
inline Type_::~DefaultQueue() {}

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
inline void Type_::TakeElements(Queue & theQueue) {
	theQueue.GiveElements(*this);
}

Template_
inline void Type_::TakeElements(Queue const & theQueue) {
	theQueue.GiveElements(*this);
}

Template_
inline void Type_::TakeQuotedElements(Queue & theQueue) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this).TakeQuotedQueue(theQueue);
}

Template_
inline void Type_::TakeQuotedElements(Queue const & theQueue) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	static_cast<ThisImplementation &>(*this).TakeQuotedQueue(theQueue);
}

	#undef Type_
	#undef Template_

#endif
