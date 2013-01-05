/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if !defined( Om_Sources_StreamSource_ )
	#define Om_Sources_StreamSource_ Om::Sources::StreamSource

	#include "om/sources/default_source.hpp"

namespace Om
{
	namespace Sources
	{
		// MARK: - Om::Sources::StreamSource
		/*!
		\brief
			A Source adapter for an input stream.
		\note
			Const methods are not thread-safe due to a non-mutexed mutable
			member.
		\note
			Dereferencing exposes a reference to a cache of the current item.
			Modifying the item will not modify the source data.
		*/
		template< typename ThisItem = char >
		struct StreamSource
		:
		DefaultSource< ThisItem const, StreamSource< ThisItem > >
		{
		public: // MARK: public (non-static)

			StreamSource();

			explicit StreamSource( std::istream & );

			StreamSource & operator =( StreamSource );

			bool operator ==( StreamSource const & ) const;

			virtual bool operator !() const;

			virtual ThisItem const & operator *() const;

			virtual void Pop();

			void Swap( StreamSource & );

		private: // MARK: private (static)

			typedef std::istreambuf_iterator< ThisItem > StreamIterator;

		private: // MARK: private (non-static)

			StreamIterator thisStreamIterator;

			//! The current item.
			mutable boost::optional< ThisItem > thisItem;
		};
	}
}

// MARK: - boost
namespace boost
{
	template< typename ThisItem >
	void swap(
		Om::Sources::StreamSource< ThisItem > &,
		Om::Sources::StreamSource< ThisItem > &
	);
}

	#include "om/sources/stream_source.cpp"
#endif
