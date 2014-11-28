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

\defgroup om__null__ Null
	\ingroup om__program__
	\brief
		The null \ref om__program__.
	\par Interpretation
		A \ref om__program__ is interpreted as \ref om__null__ by treating all elements as insignificant.
	\par Normalization
		A \ref om__program__ is normalized as \ref om__null__ by discarding all elements.
	\par Implementation
		Om::Language::Null
*/

#ifndef Om_Language_Null_

	#define Om_Language_Null_ \
	Om::Language::Null

	#include "om/code_point.hpp"
	#include "om/language/default_element.hpp"

	#ifndef Om_Macro_Precompilation_

		#include "boost/swap.hpp"

	#endif

	#define Om_Language_Null_GetName_() \
	"null"

namespace Om {

	namespace Language {

		// MARK: - Om::Language::Null

		/*!
		\brief
			The \ref om__null__ Element implementation.
		\todo
			Restore default ThisInterface argument when <a href="https://bugzilla.gnome.org/show_bug.cgi?id=739863">Doxygen bug 739863</a> is fixed.
		*/
		class Null:
		public DefaultElement<
			Null,
			Element
		> {

		public: // MARK: public (static)

			/*!
			\return
				The static Null. This can be a mutable reference because Null is immutable regardless.
			*/
			static Null & Get();

			static char const * GetName();

		public: // MARK: public (non-static)

			Null();

			/*!
			\brief
				Swallows the next CodePoint in the Source.
			*/
			explicit Null(
				Om::Source::Source<CodePoint const> &
			);

			Null & operator =(Null const &);

			virtual Program & operator *();

			virtual Program const & operator *() const;

			virtual void Clear();

			virtual bool Equals(Element const &) const;

			virtual bool Equals(Program const &) const;

			virtual std::auto_ptr<
				Om::Source::Source<Element>
			> GetElementRange();

			virtual std::auto_ptr<
				Om::Source::Source<Element const>
			> GetElementRange() const;

			virtual void GiveElements(Consumer &);

			virtual void GiveElements(Consumer &) const;

			virtual bool IsEmpty() const;

			virtual bool Merge(Operator &);

			virtual bool Merge(Operator const &);

			virtual bool Merge(Separator &);

			virtual bool Merge(Separator const &);

			virtual void ParseElements(Reader &);

			virtual void ParseQuotedElements(Reader &);

			virtual void Swap(Null &);

			virtual void TakeElements(Producer &);

			virtual void TakeElements(Producer const &);

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
		Om::Language::Null &,
		Om::Language::Null &
	);

}

	#include "om/language/null.cpp"

#endif
