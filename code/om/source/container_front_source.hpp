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

#ifndef Om_Source_ContainerFrontSource_

	#define Om_Source_ContainerFrontSource_ \
	Om::Source::ContainerFrontSource

	#include "om/source/default_source.hpp"

namespace Om {

	namespace Source {

		// MARK: - Om::Source::ContainerFrontSource

		/*!
		\brief
			A Source adapter for a container; pulls items from the front.
		*/
		template <
			typename ThisItem,
			typename ThisContainer
		>
		class ContainerFrontSource:
		public DefaultSource<
			ThisItem,
			ContainerFrontSource<
				ThisItem,
				ThisContainer
			>
		> {

		public: // MARK: public (non-static)

			explicit ContainerFrontSource(ThisContainer &);

			ContainerFrontSource & operator =(ContainerFrontSource);

			virtual bool operator !() const;

			virtual ThisItem & operator *() const;

			using DefaultSource<
				ThisItem,
				ContainerFrontSource<
					ThisItem,
					ThisContainer
				>
			>::Equals;

			bool Equals(ContainerFrontSource const &) const;

			virtual void Pop();

			void Swap(ContainerFrontSource &);

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
			ContainerFrontSource<
				TheItem,
				TheContainer
			> const &,
			ContainerFrontSource<
				TheItem,
				TheContainer
			> const &
		);

		template <
			typename TheItem,
			typename TheContainer
		>
		bool operator !=(
			ContainerFrontSource<
				TheItem,
				TheContainer
			> const &,
			ContainerFrontSource<
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
		Om::Source::ContainerFrontSource<
			TheItem,
			TheContainer
		> &,
		Om::Source::ContainerFrontSource<
			TheItem,
			TheContainer
		> &
	);

}

	#include "om/source/container_front_source.cpp"

#endif
