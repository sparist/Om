/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Sources_ContainerBackSource_ )

	#define Om_Sources_ContainerBackSource_ \
	Om::Sources::ContainerBackSource

	#include "om/sources/default_source.hpp"

namespace Om
{
	namespace Sources
	{
		// MARK: - Om::Sources::ContainerBackSource
		/*!
		\brief
			A Source adapter for a container; pulls items from the back.
		*/
		template<
			typename ThisItem,
			typename ThisContainer
		>
		struct ContainerBackSource
		:
		DefaultSource<
			ThisItem,
			ContainerBackSource<
				ThisItem,
				ThisContainer
			>
		>
		{
		public: // MARK: public (non-static)

			explicit ContainerBackSource( ThisContainer & );

			ContainerBackSource & operator =( ContainerBackSource );

			bool operator ==( ContainerBackSource const & ) const;

			virtual bool operator !() const;

			virtual ThisItem & operator *() const;

			virtual void Pop();

			void Swap( ContainerBackSource & );

		private: // MARK: private (non-static)

			/*!
			\brief
				The container to pull from.
			*/
			ThisContainer & thisContainer;
		};
	}
}

// MARK: - boost
namespace boost
{
	template<
		typename ThisItem,
		typename ThisContainer
	>
	void swap(
		Om::Sources::ContainerBackSource<
			ThisItem,
			ThisContainer
		> &,
		Om::Sources::ContainerBackSource<
			ThisItem,
			ThisContainer
		> &
	);
}

	#include "om/sources/container_back_source.cpp"

#endif
