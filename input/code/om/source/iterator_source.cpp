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

#ifndef Om_Source_IteratorSource_

	#include "om/source/iterator_source.hpp"

	#ifdef Om_Macros_Test_

		#include "om/sink/container_back_sink.hpp"

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(IteratorSourceTest)

		namespace {

			static void CopyWithIterators(
				char const theCodeUnitIterator[],
				std::string & theSinkString
			) {
				typedef Source::IteratorSource<
					char const,
					char const *
				> IteratorSource;
				IteratorSource theSource(theCodeUnitIterator);
				IteratorSource const theSourceEnd("");

				Sink::ContainerBackSink<
					char const,
					std::string
				> theSink(theSinkString);

				std::copy(
					theSource,
					theSourceEnd,
					theSink
				);
			}

			class Item {

			public:

				// Note: this is intentionally non-explicit.
				Item(char const theCodeUnit) :
				thisCodeUnit(theCodeUnit)
				{}

				bool operator !() const {
					return !this->thisCodeUnit;
				}

				char thisCodeUnit;

			};

		}

		BOOST_AUTO_TEST_CASE(GeneralTest) {
			typedef Item * Iterator;
			typedef Source::IteratorSource<
				Item,
				Iterator
			> IteratorSource;

			Item theSourceArray[] = {
				'0',
				'1',
				'2',
				0
			};
			IteratorSource theSource(theSourceArray);
			Item theSourceArrayEnd[] = {0};
			IteratorSource const theSourceEnd(theSourceArrayEnd);

			BOOST_CHECK(theSourceEnd != theSource);
			BOOST_CHECK_EQUAL(
				'0',
				theSource->thisCodeUnit
			);

			++theSource;
			BOOST_CHECK(theSourceEnd != theSource);
			BOOST_CHECK_EQUAL(
				'1',
				(*theSource).thisCodeUnit
			);

			IteratorSource theIterator = ++theSource;
			BOOST_CHECK(theSourceEnd != theSource);
			BOOST_CHECK_EQUAL(
				'2',
				theIterator->thisCodeUnit
			);
			BOOST_CHECK_EQUAL(
				'2',
				theSource->thisCodeUnit
			);

			theIterator->thisCodeUnit = '3';
			(*theSource).thisCodeUnit = '4';
			BOOST_CHECK_EQUAL(
				'4',
				(*theIterator).thisCodeUnit
			);
			BOOST_CHECK_EQUAL(
				'4',
				theSource->thisCodeUnit
			);
			BOOST_CHECK_EQUAL(
				'0',
				theSourceArray[0].thisCodeUnit
			);
			BOOST_CHECK_EQUAL(
				'1',
				theSourceArray[1].thisCodeUnit
			);
			BOOST_CHECK_EQUAL(
				'4',
				theSourceArray[2].thisCodeUnit
			);
			BOOST_CHECK_EQUAL(
				0,
				theSourceArray[3].thisCodeUnit
			);

			++theSource;
			BOOST_CHECK(theSourceEnd == theSource);
		}

		BOOST_AUTO_TEST_CASE(CopyMultipleItemsTest) {
			char const theSourceNullTerminatedString[] = "01";
			std::string theSinkString;
			CopyWithIterators(
				theSourceNullTerminatedString,
				theSinkString
			);

			BOOST_CHECK_EQUAL(
				theSourceNullTerminatedString,
				theSinkString
			);
		}

		BOOST_AUTO_TEST_CASE(CopySingleItemTest) {
			char const theSourceNullTerminatedString[] = "0";
			std::string theSinkString;
			CopyWithIterators(
				theSourceNullTerminatedString,
				theSinkString
			);

			BOOST_CHECK_EQUAL(
				theSourceNullTerminatedString,
				theSinkString
			);
		}

		BOOST_AUTO_TEST_CASE(CopyNoItemsTest) {
			char const theSourceNullTerminatedString[] = "";
			std::string theSinkString;
			CopyWithIterators(
				theSourceNullTerminatedString,
				theSinkString
			);

			BOOST_CHECK_EQUAL(
				theSourceNullTerminatedString,
				theSinkString
			);
		}

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

// MARK: - Om::Source::IteratorSource

	#define Template_ \
	template < \
		typename ThisItem, \
		typename ThisIterator \
	>

	#define Type_ \
	Om::Source::IteratorSource< \
		ThisItem, \
		ThisIterator \
	>

// MARK: public (non-static)

Template_
inline Type_::IteratorSource(ThisIterator const theIterator) :
thisIterator(theIterator)
{}

Template_
inline Type_ & Type_::operator =(IteratorSource theIteratorSource) {
	this->Swap(theIteratorSource);
	return *this;
}

Template_
inline bool Type_::operator !() const {
	return !*this->thisIterator;
}

Template_
inline ThisItem & Type_::operator *() const {
	assert(!!*this->thisIterator);
	return *this->thisIterator;
}

Template_
inline bool Type_::Equals(IteratorSource const & theIteratorSource) const {
	return (
		this->thisIterator == theIteratorSource.thisIterator ||
		(
			!*this->thisIterator &&
			!*theIteratorSource.thisIterator
		)
	);
}

Template_
inline void Type_::Pop() {
	assert(!!*this->thisIterator);
	++this->thisIterator;
}

Template_
inline void Type_::Swap(IteratorSource & theIteratorSource) {
	boost::swap(
		this->thisIterator,
		theIteratorSource.thisIterator
	);
}

	#undef Type_
	#undef Template_

// MARK: - Om::Source::

	#define Template_ \
	template < \
		typename TheItem, \
		typename TheIterator \
	>

	#define Type_ \
	Om::Source::IteratorSource< \
		TheItem, \
		TheIterator \
	>

Template_
inline bool Om::Source::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return theFirst.Equals(theSecond);
}

Template_
inline bool Om::Source::operator !=(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return !theFirst.Equals(theSecond);
}

// MARK: - boost::

Template_
inline void boost::swap(
	Type_ & theFirst,
	Type_ & theSecond
) {
	theFirst.Swap(theSecond);
}

	#undef Type_
	#undef Template_

#endif
