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

#ifndef Om_Source_CodePointSource_

	#define Om_Source_CodePointSource_ \
	Om::Source::CodePointSource

	#include "om/code_point.hpp"
	#include "om/source/iterator_source.hpp"

namespace Om {

	namespace Source {

		// MARK: - Om::Source::CodePointSource

		/*!
		\brief
			A #CodePoint Source that reads each code unit from the iterator.
		*/
		template <typename ThisCodeUnitIterator = char const *>
		class CodePointSource:
		public DefaultSource<
			CodePoint const,
			CodePointSource<ThisCodeUnitIterator>
		> {

		public: // MARK: public (non-static)

			/*!
			\param theInputStart
				The input code unit start iterator.
			\param theInputEnd
				The input code unit end iterator.
			*/
			CodePointSource(
				ThisCodeUnitIterator theInputStart,
				ThisCodeUnitIterator const theInputEnd
			);

			CodePointSource & operator =(CodePointSource);

			virtual bool operator !() const;

			virtual CodePoint const & operator *() const;

			using DefaultSource<
				CodePoint const,
				CodePointSource<ThisCodeUnitIterator>
			>::Equals;

			bool Equals(CodePointSource const &) const;

			virtual void Pop();

			void Swap(CodePointSource &);

		private: // MARK: private (non-static)

			/*!
			\brief
				The input code unit start iterator.
			*/
			ThisCodeUnitIterator thisInputIterator;

			/*!
			\brief
				The input code unit end iterator.
			*/
			ThisCodeUnitIterator thisInputEnd;

			/*!
			\brief
				The current #CodePoint.
			*/
			CodePoint thisCodePoint;

		};

		// MARK: - Om::Source::CodePointSource<char const *>

		/*!
		\brief
			A specialization for null-terminated code unit array.
		*/
		template <>
		class CodePointSource<char const *>:
		public CodePointSource<
			IteratorSource<
				char const,
				char const *
			>
		> {

		public: // MARK: public (non-static)

			/*!
			\param theCodeUnitIterator
				A non-null pointer to a null-terminated code unit array.
			*/
			explicit CodePointSource(
				char const theCodeUnitIterator[]
			);

		private: // MARK: private (static)

			/*!
			\brief
				A convenience typedef of the underlying IteratorSource.
			*/
			typedef IteratorSource<
				char const,
				char const *
			> CodeUnitSource;

		};

		// MARK: - Om::Source::

		template <typename TheCodeUnitIterator>
		bool operator ==(
			CodePointSource<TheCodeUnitIterator> const &,
			CodePointSource<TheCodeUnitIterator> const &
		);

		template <typename TheCodeUnitIterator>
		bool operator !=(
			CodePointSource<TheCodeUnitIterator> const &,
			CodePointSource<TheCodeUnitIterator> const &
		);

	}

}

namespace boost {

	// MARK: - boost::

	template <typename TheCodeUnitIterator>
	void swap(
		Om::Source::CodePointSource<TheCodeUnitIterator> &,
		Om::Source::CodePointSource<TheCodeUnitIterator> &
	);

}

	#include "om/source/code_point_source.cpp"

#endif
