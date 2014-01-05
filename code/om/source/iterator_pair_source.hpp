/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Source_IteratorPairSource_

	#define Om_Source_IteratorPairSource_ \
	Om::Source::IteratorPairSource

	#include "om/source/default_source.hpp"

namespace Om {

	namespace Source {

		// MARK: - Om::Source::IteratorPairSource

		/*!
		\brief
			A Source adapter for a start and end input iterator pair.
		*/
		template <
			typename ThisItem,
			typename ThisIterator
		>
		class IteratorPairSource:
		public DefaultSource<
			ThisItem,
			IteratorPairSource<
				ThisItem,
				ThisIterator
			>
		> {

		public: // MARK: public (non-static)

			/*!
			\param theCurrent
				The current input iterator.
			\param theEnd
				The end input iterator.
			*/
			IteratorPairSource(
				ThisIterator theCurrent,
				ThisIterator const theEnd
			);

			IteratorPairSource & operator =(IteratorPairSource);

			virtual ThisItem & operator *() const;

			using DefaultSource<
				ThisItem,
				IteratorPairSource<
					ThisItem,
					ThisIterator
				>
			>::Equals;

			bool Equals(IteratorPairSource const &) const;

			void End();

			virtual bool operator !() const;

			virtual void Pop();

			void Swap(IteratorPairSource &);

		private: // MARK: private (non-static)

			/*!
			\brief
				The current input iterator.
			*/
			ThisIterator thisCurrent;

			/*!
			\brief
				The end input iterator.
			*/
			ThisIterator thisEnd;

		};

		// MARK: - Om::Source::

		template <
			typename TheItem,
			typename TheIterator
		>
		bool operator ==(
			IteratorPairSource<
				TheItem,
				TheIterator
			> const &,
			IteratorPairSource<
				TheItem,
				TheIterator
			> const &
		);

		template <
			typename TheItem,
			typename TheIterator
		>
		bool operator !=(
			IteratorPairSource<
				TheItem,
				TheIterator
			> const &,
			IteratorPairSource<
				TheItem,
				TheIterator
			> const &
		);

	}

}

namespace boost {

	// MARK: - boost::

	template <
		typename TheItem,
		typename TheIterator
	>
	void swap(
		Om::Source::IteratorPairSource<
			TheItem,
			TheIterator
		> &,
		Om::Source::IteratorPairSource<
			TheItem,
			TheIterator
		> &
	);

}

	#include "om/source/iterator_pair_source.cpp"

#endif
