/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Copy_ )

	#define Om_Copy_ \
	Om::Copy

	#include "external.hpp"

namespace Om
{
	// MARK: - Om
	/*!
	\return
		A polymorphic copy of the object.
	*/
	template< typename TheCopyable >
	std::auto_ptr< TheCopyable > Copy( TheCopyable const & );
}

	#include "om/copy.cpp"

#endif
