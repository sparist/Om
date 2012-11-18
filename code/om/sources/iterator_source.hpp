/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if !defined( Om_Sources_IteratorSource_ )
	#define Om_Sources_IteratorSource_ Om::Sources::IteratorSource

	#include "om/sources/default_source.hpp"

namespace Om
{
	namespace Sources
	{
		// MARK: - Om::Sources::IteratorSource
		/*!
		\brief
			A Source adapter for a sentinal-terminated input iterator.
		\tparam ThisItem
			The item type, which must implement the \c ! operator such that it
			only returns true for the sentinal.
		\tparam ThisIterator
			The iterator type.
		*/
		template< typename ThisItem, typename ThisIterator >
		struct IteratorSource
		:
		DefaultSource< ThisItem, IteratorSource< ThisItem, ThisIterator > >
		{
		public: // MARK: public (non-static)

			/*!
			\param theIterator
				The input iterator, dereferencable to a valid item.
			*/
			explicit IteratorSource( ThisIterator const theIterator );

			IteratorSource & operator =( IteratorSource );

			bool operator ==( IteratorSource const & ) const;

			virtual bool operator !() const;

			virtual ThisItem & operator *() const;

			virtual void Pop();

			void Swap( IteratorSource & );

		private: // MARK: private (non-static)

			//! The input iterator.
			ThisIterator thisIterator;
		};
	}
}

// MARK: - boost
namespace boost
{
	template< typename ThisItem, typename ThisIterator >
	void swap(
		Om::Sources::IteratorSource< ThisItem, ThisIterator > &,
		Om::Sources::IteratorSource< ThisItem, ThisIterator > &
	);
}

	#include "om/sources/iterator_source.cpp"
#endif
