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

#ifndef Om_Source_SingletonSource_

	#define Om_Source_SingletonSource_ \
	Om::Source::SingletonSource

	#include "om/source/default_source.hpp"

namespace Om {

	namespace Source {

		// MARK: - Om::Source::SingletonSource

		/*!
		\brief
			A single item Source.
		*/
		template <typename ThisItem>
		class SingletonSource:
		public DefaultSource<
			ThisItem,
			SingletonSource<ThisItem>
		> {

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

		// MARK: - Om::Source::

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
		Om::Source::SingletonSource<TheItem> &,
		Om::Source::SingletonSource<TheItem> &
	);

}

	#include "om/source/singleton_source.cpp"

#endif
