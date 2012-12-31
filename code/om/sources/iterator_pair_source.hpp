/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
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
#if !defined( Om_Sources_IteratorPairSource_ )
	#define Om_Sources_IteratorPairSource_ Om::Sources::IteratorPairSource

	#include "om/sources/default_source.hpp"

namespace Om
{
	namespace Sources
	{
		// MARK: - Om::Sources::IteratorPairSource
		/*!
		\brief
			A Source adapter for a start and end input iterator pair.
		*/
		template< typename ThisItem, typename ThisIterator >
		struct IteratorPairSource
		:
		DefaultSource< ThisItem, IteratorPairSource< ThisItem, ThisIterator > >
		{
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

			IteratorPairSource & operator =( IteratorPairSource );

			bool operator ==( IteratorPairSource const & ) const;

			virtual ThisItem & operator *() const;

			void End();

			virtual bool operator !() const;

			virtual void Pop();

			void Swap( IteratorPairSource & );

		private: // MARK: private (non-static)

			//! The current input iterator.
			ThisIterator thisCurrent;

			//! The end input iterator.
			ThisIterator thisEnd;
		};
	}
}

// MARK: - boost
namespace boost
{
	template< typename ThisItem, typename ThisIterator >
	void swap(
		Om::Sources::IteratorPairSource< ThisItem, ThisIterator > &,
		Om::Sources::IteratorPairSource< ThisItem, ThisIterator > &
	);
}

	#include "om/sources/iterator_pair_source.cpp"
#endif
