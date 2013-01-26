/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_CodePoint_ )

	#define Om_CodePoint_ \
	Om::CodePoint

	#include "external.hpp"

namespace Om
{
	//! A UTF-8 code point.
	typedef boost::locale::utf::code_point CodePoint;
}

#endif
