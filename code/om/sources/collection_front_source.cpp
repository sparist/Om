/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Sources_CollectionFrontSource_ )

// MARK: Om::Sources::CollectionFrontSource

	#define Template_ \
	template< \
		typename ThisItem, \
		typename ThisIterator \
	>

	#define Type_ \
	Om::Sources::CollectionFrontSource< \
		ThisItem, \
		ThisIterator \
	>

// MARK: public (non-static)

Template_
template< typename TheCollection >
inline Type_::CollectionFrontSource( TheCollection & theCollection ):
IteratorPairSource<
	ThisItem,
	ThisIterator
>(
	theCollection.begin(),
	theCollection.end()
) {}

	#undef Type_
	#undef Template_

#else

	#include "om/sources/collection_front_source.hpp"

#endif
