/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.
		All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb

\defgroup om__separator__ Separator
	\ingroup om__program__
	\brief
		An atomic \ref om__program__ element that serves to separate other elements.
	\par Interpretation
		A \ref om__program__ is interpreted as a \ref om__separator__ by treating only separator code points (line, tab, and space) as significant.
	\par Normalization
		A \ref om__program__ is normalized as a \ref om__separator__ by discarding all non-separator code points.
	\par Implementation
		Om::Separator
*/

#ifndef Om_Separator_

	#define Om_Separator_ \
	Om::Separator

	#include "om/default_atom.hpp"
	#include "om/symbol/separator_symbol.hpp"

	#define Om_Separator_GetName_() \
	"separator"

namespace Om {

	// MARK: - Om::Separator

	/*!
	\brief
		The \ref om__separator__ implementation.

	An Atom defined by a string containing only Symbol::SeparatorSymbol characters.

	As a Consumer, the Separator filters out all top-level Element instances except Separator.
	*/
	class Separator:
	public DefaultAtom<Separator> {

	public: // MARK: public (static)

		/*!
		\return
			A Separator comprised of a single Symbol::theLineSeparatorSymbol.
		*/
		static Separator const & GetLineSeparator();

		static char const * GetName();

	public: // MARK: public (non-static)

		Separator();

		explicit Separator(
			Source::Source<CodePoint const> &
		);

		/*!
		\param theSeparatorSymbol
			The Symbol::SeparatorSymbol to copy directly into the Separator.
		*/
		explicit Separator(Symbol::SeparatorSymbol const theSeparatorSymbol);

		Separator & operator =(Separator);

		virtual void ReadElements(Parser &);

		virtual void ReadQuotedElements(Parser &);

		template <typename TheOperand>
		void TakeOperand(TheOperand &);

		template <typename TheOperator>
		void TakeOperator(TheOperator &);

		template <typename TheProducer>
		void TakeQuotedProducer(TheProducer &);

		template <typename TheSeparator>
		void TakeSeparator(TheSeparator &);

		void TakeSeparatorSymbol(Symbol::SeparatorSymbol const);

	};

}

namespace boost {

	// MARK: - boost::

	template <>
	void swap(
		Om::Separator &,
		Om::Separator &
	);

}

	#include "om/separator.cpp"

#endif
