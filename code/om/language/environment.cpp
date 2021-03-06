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

#ifndef Om_Language_Environment_

	#include "om/language/environment.hpp"

#else

// MARK: - Om::Language::Environment

	#define Type_ \
	Om::Language::Environment

// MARK: public (non-static)

inline Type_::Environment():
thisTranslatorVector() {}

inline void Type_::GiveElements(Consumer & theConsumer) const {
	if (
		!this->IsEmpty()
	) {
		typedef TranslatorVector::const_iterator Iterator;
		Iterator const theEnd = this->thisTranslatorVector.end();
		for (
			Iterator theCurrent = this->thisTranslatorVector.begin();
			;
			theConsumer.TakeElement(
				Separator::GetLineSeparator()
			)
		) {
			assert(*theCurrent);
			Translator const & theTranslator = **theCurrent;
			assert(
				!theTranslator.IsEmpty()
			);
			theTranslator.GiveElements(theConsumer);
			if (theEnd == ++theCurrent) {
				return;
			}
		}
	}
}

inline bool Type_::IsEmpty() const {
	return this->thisTranslatorVector.empty();
}

inline void Type_::Push(Translator const & theTranslator) {
	Translator const * theTranslatorPointer = &theTranslator;
	for (
		std::stack<Translator const *> theStack;
		;
		theStack.pop()
	) {
		assert(theTranslatorPointer);

		if (
			Environment const * const theEnvironment = dynamic_cast<Environment const *>(theTranslatorPointer)
		) {
			typedef TranslatorVector::const_reverse_iterator Iterator;
			Iterator const theEnd = theEnvironment->thisTranslatorVector.rend();
			for (
				Iterator theCurrent = theEnvironment->thisTranslatorVector.rbegin();
				theEnd != theCurrent;
				++theCurrent
			) {
				assert(
					*theCurrent &&
					!(*theCurrent)->IsEmpty()
				);
				theStack.push(*theCurrent);
			}
		} else if (
			this->IsEmpty() ||
			this->thisTranslatorVector.back() != theTranslatorPointer
		) {
			this->thisTranslatorVector.push_back(theTranslatorPointer);
		}

		if (
			theStack.empty()
		) {
			return;
		}

		theTranslatorPointer = theStack.top();
	}
}

inline bool Type_::Translate(
	Evaluation & theEvaluation,
	Operator const & theOperator
) const {
	typedef TranslatorVector::const_reverse_iterator Iterator;
	Iterator const theEnd = this->thisTranslatorVector.rend();
	for (
		Iterator theCurrent = this->thisTranslatorVector.rbegin();
		theEnd != theCurrent;
		++theCurrent
	) {
		if (
			(*theCurrent)->Translate(
				theEvaluation,
				theOperator
			)
		) {
			return true;
		}
	}
	return false;
}

	#undef Type_

#endif
