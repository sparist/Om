/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Source_ContainerBackSource_

	#define Om_Source_ContainerBackSource_ \
	Om::Source::ContainerBackSource

	#include "om/source/default_source.hpp"

namespace Om {

	namespace Source {

		// MARK: - Om::Source::ContainerBackSource

		/*!
		\brief
			A Source adapter for a container; pulls items from the back.
		*/
		template <
			typename ThisItem,
			typename ThisContainer
		>
		class ContainerBackSource :
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

		// MARK: - Om::Source::

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
		Om::Source::ContainerBackSource<
			TheItem,
			TheContainer
		> &,
		Om::Source::ContainerBackSource<
			TheItem,
			TheContainer
		> &
	);

}

	#include "om/source/container_back_source.cpp"

#endif
