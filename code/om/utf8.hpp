/*!
\file
	\brief
		Om hpp file.
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
#if !defined( Om_Utf8_ )
	#define Om_Utf8_ Om::Utf8

	#include "external.hpp"

namespace Om
{
	//! The UTF-8 traits type.
	typedef boost::locale::utf::utf_traits< char > Utf8;
}

#endif
