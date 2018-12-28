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
*/

#ifndef Om_Language_DefaultAtom_

	#define Om_Language_DefaultAtom_ \
	Om::Language::DefaultAtom

	#include "om/language/atom.hpp"
	#include "om/language/default_element.hpp"

	#ifndef Om_Macro_Precompilation_

		#include <string>

	#endif

namespace Om {

	namespace Language {

		// MARK: - Om::Language::DefaultAtom

		/*!
		\brief
			A partial implementation of Atom.
		\internal
			The fully-specified Atom namespace is required to work around a Doxygen bug that has difficulty inferring inheritance otherwise.
		*/
		template <typename ThisImplementation>
		class DefaultAtom:
		public DefaultElement<
			ThisImplementation,
			Om::Language::Atom
		> {

		public: // MARK: public (non-static)

			virtual ~DefaultAtom() = 0;

			/*!
			\brief
				Compares with a Atom; required for use as index in containers.
			\return
				True if this Atom string precedes the argument Atom string in a byte-wise ordering.
			*/
			bool operator <(DefaultAtom const &);

			virtual void Clear();

			using DefaultElement<
				ThisImplementation,
				Atom
			>::Equals;

			bool Equals(DefaultAtom const &) const;

			bool Equals(ThisImplementation const &) const;

			virtual std::auto_ptr<
				Om::Source::Source<Element>
			> GetElementRange();

			virtual std::auto_ptr<
				Om::Source::Source<Element const>
			> GetElementRange() const;

			/*!
			\return
				The string that defines this Atom.
			*/
			std::string const & GetString() const;

			/*!
			\return
				True if empty.

			An empty Atom cannot be represented in Om code, but can be handy as an efficient null representation in implementation (e.g. the result after a move).
			*/
			virtual bool IsEmpty() const;

			using DefaultElement<
				ThisImplementation,
				Atom
			>::Merge;

			/*!
			\return
				True if the Atom was merged.
			*/
			virtual bool Merge(ThisImplementation &);

			/*!
			\overload
			*/
			virtual bool Merge(ThisImplementation const &);

			void Swap(ThisImplementation &);

		protected: // MARK: protected (non-static)

			DefaultAtom();

			/*!
			\param theCodeUnitIterator
				A non-null pointer to the null-terminated code unit array to copy.
			*/
			explicit DefaultAtom(
				char const theCodeUnitIterator[]
			);

			/*!
			\param theCodeUnit
				The ASCII #CodePoint to copy.
			*/
			explicit DefaultAtom(char const theCodeUnit);

			/*!
			\brief
				The NFD-normalized string that defines the Atom.
			*/
			std::string thisString;

		private: // MARK: private (non-static)

			DefaultAtom & operator =(DefaultAtom const &);

		};

		// MARK: - Om::Language::

		template <typename TheImplementation>
		bool operator ==(
			DefaultAtom<TheImplementation> const &,
			DefaultAtom<TheImplementation> const &
		);

		template <typename TheImplementation>
		bool operator !=(
			DefaultAtom<TheImplementation> const &,
			DefaultAtom<TheImplementation> const &
		);

	}

}

	#include "om/language/default_atom.cpp"

#endif
