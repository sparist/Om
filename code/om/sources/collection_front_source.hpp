/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Sources_CollectionFrontSource_ )

	#define Om_Sources_CollectionFrontSource_ \
	Om::Sources::CollectionFrontSource

	#include "om/sources/iterator_pair_source.hpp"

namespace Om {
	namespace Sources {

		// MARK: - Om::Sources::CollectionFrontSource
		/*!
		\brief
			A range over a collection, starting from the front.
		*/
		template<
			typename ThisItem,
			typename ThisIterator
		>
		struct CollectionFrontSource:
		public IteratorPairSource<
			ThisItem,
			ThisIterator
		> {
		public: // MARK: public (non-static)

			template< typename TheCollection >
			explicit CollectionFrontSource( TheCollection & );
		};
	}
}

	#include "om/sources/collection_front_source.cpp"

#endif
