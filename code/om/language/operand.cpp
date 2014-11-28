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

#ifndef Om_Language_Operand_

	#include "om/language/operand.hpp"

#else

	#include "om/language/literal.hpp"
	#include "om/language/null.hpp"

// MARK: - Om::Language::Operand

	#define Type_ \
	Om::Language::Operand

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operand_GetName_();
}

// MARK: public (non-static)

inline Type_::Operand():
thisProgram() {}

template <typename TheProgram>
inline Type_::Operand(
	std::auto_ptr<TheProgram> theProgram
):
thisProgram(theProgram) {}

inline Type_ & Type_::operator =(Operand theOperand) {
	this->Swap(theOperand);
	return *this;
}

inline Om::Language::Program & Type_::operator *() {
	return (
		this->thisProgram.IsEmpty() ?
		Null::Get() :
		*this->thisProgram
	);
}

inline Om::Language::Program const & Type_::operator *() const {
	return (
		this->thisProgram.IsEmpty() ?
		Null::Get() :
		*this->thisProgram
	);
}

inline void Type_::Clear() {
	this->thisProgram.Clear();
}

inline bool Type_::Equals(Operand const & theOperand) const {
	return (
		this->IsEmpty() ?
		theOperand.IsEmpty() :
		*this->GetProgram() == *theOperand.GetProgram()
	);
}

inline Om::Language::Program * Type_::GetProgram() {
	return this->thisProgram.GetValue();
}

inline Om::Language::Program const * Type_::GetProgram() const {
	return this->thisProgram.GetValue();
}

inline bool Type_::IsEmpty() const {
	return !this->thisProgram;
}

inline void Type_::ParseElements(Reader & theReader) {
	if (
		this->IsEmpty()
	) {
		for (
			;
			;
			theReader.Pop()
		) {
			if (!theReader) {
				return;
			}
			assert(Symbol::theEndOperandSymbol != *theReader);
			switch (*theReader) {
			default:
				continue;
			case Symbol::theStartOperandSymbol:
				theReader.Pop();
				{
					// Ensure against copy constructor call.
					Om::Source::Source<CodePoint const> & theCodePointSource = theReader;

					Reader theOperandReader(theCodePointSource);
					this->ParseQuotedElements(theOperandReader);
				}
				assert(
					!theReader ||
					Symbol::theEndOperandSymbol == *theReader
				);
				// Fall through.
			}
			break;
		}
	}

	for (
		;
		theReader;
		theReader.Pop()
	) {}
}

inline void Type_::ParseQuotedElements(Reader & theReader) {
	Literal theLiteral;
	theLiteral.ParseElements(theReader);
	this->TakeQuotedProducer(theLiteral);
}

template <typename TheProgram>
inline void Type_::SetProgram(
	std::auto_ptr<TheProgram> theProgram
) {
	this->thisProgram.SetValue(theProgram);
}

inline void Type_::Swap(Operand & theOperand) {
	this->thisProgram.Swap(theOperand.thisProgram);
}

/*!
\todo
	Restore default ThisInterface argument when <a href="https://bugzilla.gnome.org/show_bug.cgi?id=739863">Doxygen bug 739863</a> is fixed.
*/
inline void Type_::TakeElements(Producer & theProducer) {
	if (
		this->IsEmpty()
	) {
		DefaultElement<Operand, Element>::TakeElements(theProducer);
	}
}

/*!
\todo
	Restore default ThisInterface argument when <a href="https://bugzilla.gnome.org/show_bug.cgi?id=739863">Doxygen bug 739863</a> is fixed.
*/
inline void Type_::TakeElements(Producer const & theProducer) {
	if (
		this->IsEmpty()
	) {
		DefaultElement<Operand, Element>::TakeElements(theProducer);
	}
}

template <typename TheOperand>
inline void Type_::TakeOperand(TheOperand & theOperand) {
	if (
		this->IsEmpty()
	) {
		this->Take(theOperand);
	}
}

template <typename TheOperator>
inline void Type_::TakeOperator(TheOperator &) {}

template <typename TheProducer>
inline void Type_::TakeQuotedProducer(TheProducer & theProducer) {
	if (
		this->IsEmpty()
	) {
		this->SetProgram(
			theProducer.GiveProgram()
		);
	}
}

template <typename TheSeparator>
inline void Type_::TakeSeparator(TheSeparator &) {}

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

// MARK: - boost::

template <>
inline void boost::swap(
	Type_ & theFirst,
	Type_ & theSecond
) {
	theFirst.Swap(theSecond);
}

	#undef Type_

#endif
