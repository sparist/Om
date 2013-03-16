/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Sources_ContainerBackSource_

	#define Om_Sources_ContainerBackSource_ \
	Om::Sources::ContainerBackSource

	#include "om/sources/default_source.hpp"

namespace Om {

	namespace Sources {

		// MARK: - Om::Sources::ContainerBackSource

		/*!
		\brief
			A Source adapter for a container; pulls items from the back.
		*/
		template <
			typename ThisItem,
			typename ThisContainer
		>
		class ContainerBackSource:
		public DefaultSource<
			ThisItem,
			ContainerBackSource<
				ThisItem,
				ThisContainer
			>
		> {

		public: // MARK: public (non-static)

			explicit ContainerBackSource(ThisContainer &);

			ContainerBackSource & operator =(ContainerBackSource);

			virtual bool operator !() const;

			virtual ThisItem & operator *() const;

			using DefaultSource<
				ThisItem,
				ContainerBackSource<
					ThisItem,
					ThisContainer
				>
			>::Equals;

			bool Equals(ContainerBackSource const &) const;

			virtual void Pop();

			void Swap(ContainerBackSource &);

		private: // MARK: private (non-static)

			/*!
			\brief
				The container to pull from.
			*/
			ThisContainer & thisContainer;

		};

		// MARK: - Om::Sources::

		template <
			typename TheItem,
			typename TheContainer
		>
		bool operator ==(
			ContainerBackSource<
				TheItem,
				TheContainer
			> const &,
			ContainerBackSource<
				TheItem,
				TheContainer
			> const &
		);

		template <
			typename TheItem,
			typename TheContainer
		>
		bool operator !=(
			ContainerBackSource<
				TheItem,
				TheContainer
			> const &,
			ContainerBackSource<
				TheItem,
				TheContainer
			> const &
		);

	}

}

namespace boost {

	// MARK: - boost::

	template <
		typename TheItem,
		typename TheContainer
	>
	void swap(
		Om::Sources::ContainerBackSource<
			TheItem,
			TheContainer
		> &,
		Om::Sources::ContainerBackSource<
			TheItem,
			TheContainer
		> &
	);

}

	#include "om/sources/container_back_source.cpp"

#endif
