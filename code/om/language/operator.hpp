/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb

\defgroup om__operator__ Operator
	\ingroup om__program__
	\brief
		An atomic \ref om__program__ element defined by any UTF-8 string.
	\par Interpretation
		A \ref om__program__ is interpreted as an \ref om__operator__ by treating it as containing as a single atomic UTF-8 string element containing the encoded text of all elements.
	\par Normalization
		A \ref om__program__ is normalized as an \ref om__operator__ by encoding and merging all elements.
	\par Implementation
		Om::Language::Operator
*/

#ifndef Om_Language_Operator_

	#define Om_Language_Operator_ \
	Om::Language::Operator

	#include "om/language/default_atom.hpp"
	#include "om/language/symbol/operand_symbol.hpp"
	#include "om/language/symbol/operator_symbol.hpp"
	#include "om/language/symbol/separator_symbol.hpp"

	#ifndef Om_Macro_Precompilation_

		#include "boost/locale/boundary.hpp"

	#endif

	#define Om_Language_Operator_GetName_() \
	"operator"

namespace Om {

	namespace Language {

		// MARK: - Om::Language::Operator

		/*!
		\brief
			The \ref om__operator__ implementation.

		An Atom defined by any UTF-8 string.

		As a Consumer, the Operator appends each taken Element verbatim.
		*/
		class Operator:
		public DefaultAtom<Operator> {

		public: // MARK: public (static)

			static char const * GetName();

		public: // MARK: public (non-static)

			Operator();

			/*!
			\brief
				Normalizes the string and copies directly into the Operator.
			*/
			explicit Operator(std::string const &);

			/*!
			\param theCodeUnitIterator
				A non-null pointer to the null-terminated code unit array to normalize and copy directly into the Operator.
			*/
			explicit Operator(
				char const theCodeUnitIterator[]
			);

			explicit Operator(
				Om::Source::Source<CodePoint const> &
			);

			explicit Operator(Symbol::OperandSymbol const);

			explicit Operator(Symbol::OperatorSymbol const);

			explicit Operator(Symbol::SeparatorSymbol const);

			Operator & operator =(Operator);

			/*!
			\brief
				Gives the last ::CodePoint as an Atom.
			*/
			void BackGiveCodePoint(Consumer &);

			/*!
			\brief
				Gives the last segment of the given type to the Consumer.
			*/
			template <boost::locale::boundary::boundary_type theSegment>
			void BackGiveSegment(Consumer &);

			/*!
			\brief
				Decodes this Operator and gives each resulting Element to the argument.
			*/
			template <typename TheConsumer>
			void Decode(TheConsumer &) const;

			/*!
			\brief
				Encodes the elements and replaces the contents of this Operator with the result.
			*/
			template <typename TheProducer>
			void Encode(TheProducer &);

			/*!
			\brief
				Gives the first ::CodePoint as an Atom.
			*/
			void FrontGiveCodePoint(Consumer &);

			/*!
			\brief
				Gives the first segment of the given type to the Consumer.
			*/
			template <boost::locale::boundary::boundary_type theSegment>
			void FrontGiveSegment(Consumer &);

			/*!
			\brief
				Applies Unicode compatibility normalization.
			*/
			void Normalize();

			virtual void ParseElements(Reader &);

			virtual void ParseQuotedElements(Reader &);

			template <typename TheOperand>
			void TakeOperand(TheOperand &);

			template <typename TheOperator>
			void TakeOperator(TheOperator &);

			template <typename TheProducer>
			void TakeQuotedProducer(TheProducer &);

			template <typename TheSeparator>
			void TakeSeparator(TheSeparator &);

		};

	}

}

namespace boost {

	// MARK: - boost::

	template <>
	void swap(
		Om::Language::Operator &,
		Om::Language::Operator &
	);

}

	#include "om/language/operator.cpp"

#endif
