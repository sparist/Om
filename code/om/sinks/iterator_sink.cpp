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

#ifndef Om_Sinks_IteratorSink_

	#include "om/sinks/iterator_sink.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Sinks {

		BOOST_AUTO_TEST_SUITE(IteratorSinkTest)

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

// MARK: - Om::Sinks::IteratorSink

	#define Template_ \
	template < \
		typename ThisItem, \
		typename ThisIterator \
	>

	#define Type_ \
	Om::Sinks::IteratorSink< \
		ThisItem, \
		ThisIterator \
	>

// MARK: public (non-static)

Template_
inline Type_::IteratorSink(ThisIterator theIterator):
thisIterator(theIterator) {}

Template_
inline Type_ & Type_::operator =(IteratorSink theIteratorSink) {
	this->Swap(theIteratorSink);
	return *this;
}

Template_
inline void Type_::Push(ThisItem & theItem) {
	*this->thisIterator++ = theItem;
}

Template_
inline void Type_::Swap(IteratorSink & theIteratorSink) {
	boost::swap(
		this->thisIterator,
		theIteratorSink.thisIterator
	);
	return *this;
}

	#undef Type_
	#undef Template_

// MARK: - boost

template <
	typename ThisItem,
	typename ThisIterator
>
inline void boost::swap(
	Om::Sinks::IteratorSink<
		ThisItem,
		ThisIterator
	> & theFirst,
	Om::Sinks::IteratorSink<
		ThisItem,
		ThisIterator
	> & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
