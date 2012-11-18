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
#if !defined( Om_Sinks_IteratorSink_ )
	#define Om_Sinks_IteratorSink_ Om::Sinks::IteratorSink

	#include "om/sinks/default_sink.hpp"

namespace Om
{
	namespace Sinks
	{
		// MARK: - Om::Sinks::IteratorSink
		/*!
		\brief
			A Sink adapter for an output iterator.
		*/
		template< typename ThisItem, typename ThisIterator >
		struct IteratorSink
		:
		DefaultSink< ThisItem, IteratorSink< ThisItem, ThisIterator > >
		{
		public: // MARK: public (non-static)

			explicit IteratorSink( ThisIterator );

			IteratorSink & operator =( IteratorSink );

			virtual void Push( ThisItem & );

			void Swap( IteratorSink & );

		private: // MARK: private (non-static)

			//! The output iterator.
			ThisIterator thisIterator;
		};
	}
}

// MARK: - boost
namespace boost
{
	template< typename ThisItem, typename ThisIterator >
	void swap(
		Om::Sinks::IteratorSink< ThisItem, ThisIterator > &,
		Om::Sinks::IteratorSink< ThisItem, ThisIterator > &
	);
}

	#include "om/sinks/iterator_sink.cpp"
#endif
