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

#ifndef Om_Sources_SingletonSource_

	#define Om_Sources_SingletonSource_ \
	Om::Sources::SingletonSource

	#include "om/sources/default_source.hpp"

namespace Om {

	namespace Sources {

		// MARK: - Om::Sources::SingletonSource

		/*!
		\brief
			A single item Source.
		*/
		template <typename ThisItem>
		class SingletonSource :
		public DefaultSource<
			ThisItem,
			SingletonSource<ThisItem>
		>
		{

		public: // MARK: public (non-static)

			SingletonSource();

			/*!
			\param theItem
				The single item in the Source.
			*/
			explicit SingletonSource(ThisItem & theItem);

			SingletonSource & operator =(SingletonSource);

			virtual bool operator !() const;

			virtual ThisItem & operator *() const;

			using DefaultSource<
				ThisItem,
				SingletonSource<ThisItem>
			>::Equals;

			bool Equals(SingletonSource const &) const;

			virtual void Pop();

			void Swap(SingletonSource &);

		private: // MARK: private (non-static)

			ThisItem * thisItem;

		};

		// MARK: - Om::Sources::

		template <typename TheItem>
		bool operator ==(
			SingletonSource<TheItem> const &,
			SingletonSource<TheItem> const &
		);

		template <typename TheItem>
		bool operator !=(
			SingletonSource<TheItem> const &,
			SingletonSource<TheItem> const &
		);

	}

}

namespace boost {

	// MARK: - boost::

	template <typename TheItem>
	void swap(
		Om::Sources::SingletonSource<TheItem> &,
		Om::Sources::SingletonSource<TheItem> &
	);

}

	#include "om/sources/singleton_source.cpp"

#endif
