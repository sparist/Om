/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if defined( Om_Copy_ )

// MARK: Om

template< typename TheCopyable >
inline std::auto_ptr< TheCopyable > Om::Copy( TheCopyable const & theCopyable )
{
	return(
		std::auto_ptr< TheCopyable >(
			static_cast< TheCopyable * >( theCopyable.Copy() )
		)
	);
}

#else
	#include "om/copy.hpp"
#endif
