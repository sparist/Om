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

#ifndef Om_Language_DefaultProgram_

	#include "om/language/default_program.hpp"

#else

	#include "om/language/element.hpp"
	#include "om/source/source.hpp"

	#ifndef Om_Macro_Precompilation_

		#include <typeinfo>

	#endif

// MARK: - Om::Language::DefaultProgram

	#define Template_ \
	template < \
		typename ThisImplementation, \
		typename ThisInterface \
	>

	#define Type_ \
	Om::Language::DefaultProgram< \
		ThisImplementation, \
		ThisInterface \
	>

// MARK: public (non-static)

Template_
inline Type_::~DefaultProgram() {}

/*!
\note
	This must be implemented in this class, vs. Program, due to Element dependency.
*/
Template_
inline bool Type_::Equals(Program const & theProgram) const {
	typedef Om::Source::Source<Element const> ElementSource;

	std::auto_ptr<ElementSource> theRange = this->GetElementRange();
	assert(
		theRange.get()
	);

	std::auto_ptr<ElementSource> theOtherRange = theProgram.GetElementRange();
	assert(
		theOtherRange.get()
	);

	for (
		;
		;
	) {
		bool const theRangeHasNext = *theRange;
		bool const theOtherRangeHasNext = *theOtherRange;
		if (
			!theRangeHasNext ||
			!theOtherRangeHasNext
		) {
			return theRangeHasNext == theOtherRangeHasNext;
		}
		if (**theRange != **theOtherRange) {
			return false;
		}
		theRange->Pop();
		theOtherRange->Pop();
	}
}

Template_
inline void Type_::TakeElements(Producer & theProducer) {
	this->TakeProducer<ThisImplementation>(theProducer);
}

Template_
inline void Type_::TakeElements(Producer const & theProducer) {
	this->TakeProducer<ThisImplementation const>(theProducer);
}

// MARK: private (non-static)

Template_
template <
	typename TheCast,
	typename TheProducer
>
inline void Type_::TakeProducer(TheProducer & theProducer) {
	assert(
		dynamic_cast<ThisImplementation *>(this)
	);
	assert(
		typeid(TheCast) == typeid(ThisImplementation)
	);
	if (
		typeid(TheCast) == typeid(theProducer) &&
		this->IsEmpty()
	) {
		this->Take(
			static_cast<TheCast &>(theProducer)
		);
	} else {
		theProducer.GiveElements(*this);
	}
}

	#undef Type_
	#undef Template_

#endif
