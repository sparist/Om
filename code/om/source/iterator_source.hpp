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

#ifndef Om_Source_IteratorSource_

	#define Om_Source_IteratorSource_ \
	Om::Source::IteratorSource

	#include "om/source/default_source.hpp"

namespace Om {

	namespace Source {

		// MARK: - Om::Source::IteratorSource

		/*!
		\brief
			A Source adapter for a sentinal-terminated input iterator.
		\tparam ThisItem
			The item type, which must implement the \c ! operator such that it only returns true for the sentinal.
		\tparam ThisIterator
			The iterator type.
		*/
		template <
			typename ThisItem,
			typename ThisIterator
		>
		class IteratorSource:
		public DefaultSource<
			ThisItem,
			IteratorSource<
				ThisItem,
				ThisIterator
			>
		> {

		public: // MARK: public (non-static)

			/*!
			\param theIterator
				The input iterator, dereferencable to a valid item.
			*/
			explicit IteratorSource(ThisIterator const theIterator);

			IteratorSource & operator =(IteratorSource);

			virtual bool operator !() const;

			virtual ThisItem & operator *() const;

			using DefaultSource<
				ThisItem,
				IteratorSource<
					ThisItem,
					ThisIterator
				>
			>::Equals;

			bool Equals(IteratorSource const &) const;

			virtual void Pop();

			void Swap(IteratorSource &);

		private: // MARK: private (non-static)

			/*!
			\brief
				The input iterator.
			*/
			ThisIterator thisIterator;

		};

		// MARK: - Om::Source::

		template <
			typename TheItem,
			typename TheIterator
		>
		bool operator ==(
			IteratorSource<
				TheItem,
				TheIterator
			> const &,
			IteratorSource<
				TheItem,
				TheIterator
			> const &
		);

		template <
			typename TheItem,
			typename TheIterator
		>
		bool operator !=(
			IteratorSource<
				TheItem,
				TheIterator
			> const &,
			IteratorSource<
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
		Om::Source::IteratorSource<
			TheItem,
			TheIterator
		> &,
		Om::Source::IteratorSource<
			TheItem,
			TheIterator
		> &
	);

}

	#include "om/source/iterator_source.cpp"

#endif
