/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if defined( Om_DefaultCopyable_ )

// MARK: Om::DefaultCopyable

	#define Template_ template< \
		typename ThisImplementation, \
		typename ThisInterface \
	>

	#define Type_ Om::DefaultCopyable< ThisImplementation, ThisInterface >

// MARK: public (non-static)

Template_
inline Type_::~DefaultCopyable()
{
}

// MARK: private (non-static)

Template_
inline ThisInterface * Type_::Copy() const
{
	assert( dynamic_cast< ThisImplementation const * >( this ) );
	return(
		new ThisImplementation(
			static_cast< ThisImplementation const & >( *this )
		)
	);
}

	#undef Type_
	#undef Template_

#else
	#include "om/default_copyable.hpp"
#endif
