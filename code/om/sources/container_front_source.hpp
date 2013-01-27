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

#if !defined( Om_Sources_ContainerFrontSource_ )

	#define Om_Sources_ContainerFrontSource_ \
	Om::Sources::ContainerFrontSource

	#include "om/sources/default_source.hpp"

namespace Om
{
	namespace Sources
	{
		// MARK: - Om::Sources::ContainerFrontSource
		/*!
		\brief
			A Source adapter for a container; pulls items from the front.
		*/
		template<
			typename ThisItem,
			typename ThisContainer
		>
		struct ContainerFrontSource
		:
		DefaultSource<
			ThisItem,
			ContainerFrontSource<
				ThisItem,
				ThisContainer
			>
		>
		{
		public: // MARK: public (non-static)

			explicit ContainerFrontSource( ThisContainer & );

			ContainerFrontSource & operator =( ContainerFrontSource );

			bool operator ==( ContainerFrontSource const & ) const;

			virtual bool operator !() const;

			virtual ThisItem & operator *() const;

			virtual void Pop();

			void Swap( ContainerFrontSource & );

		private: // MARK: private (non-static)

			//! The container to pull from.
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
		Om::Sources::ContainerFrontSource<
			ThisItem,
			ThisContainer
		> &,
		Om::Sources::ContainerFrontSource<
			ThisItem,
			ThisContainer
		> &
	);
}

	#include "om/sources/container_front_source.cpp"

#endif
