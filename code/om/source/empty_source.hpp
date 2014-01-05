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

#ifndef Om_Source_EmptySource_

	#define Om_Source_EmptySource_ \
	Om::Source::EmptySource

	#include "om/source/default_source.hpp"

namespace Om {

	namespace Source {

		// MARK: - Om::Source::EmptySource

		/*!
		\brief
			An empty Source.
		*/
		template <typename ThisItem>
		class EmptySource:
		public DefaultSource<
			ThisItem,
			EmptySource<ThisItem>
		> {

		public: // MARK: public (static)

			static EmptySource & Get();

		public: // MARK: public (non-static)

			EmptySource();

			EmptySource & operator =(EmptySource);

			virtual bool operator !() const;

			virtual ThisItem & operator *() const;

			using DefaultSource<
				ThisItem,
				EmptySource<ThisItem>
			>::Equals;

			bool Equals(EmptySource const &) const;

			virtual void Pop();

			void Swap(EmptySource &);

		};

		// MARK: - Om::Source::

		template <typename TheItem>
		bool operator ==(
			EmptySource<TheItem> const &,
			EmptySource<TheItem> const &
		);

		template <typename TheItem>
		bool operator !=(
			EmptySource<TheItem> const &,
			EmptySource<TheItem> const &
		);

	}

}

namespace boost {

	// MARK: - boost::

	template <typename TheItem>
	void swap(
		Om::Source::EmptySource<TheItem> &,
		Om::Source::EmptySource<TheItem> &
	);

}

	#include "om/source/empty_source.cpp"

#endif
