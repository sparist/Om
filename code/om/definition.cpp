/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Definition_ )

	#include "om/system.hpp"

// MARK: Om::Definition

	#define Template_ \
	template< typename ThisOperation >

	#define Type_ \
	Om::Definition< ThisOperation >

// MARK: public (non-static)

Template_
inline Type_::Definition()
{
	System::Get().thisMap[ ThisOperation::GetName() ] = &ThisOperation::Give;
}

	#undef Type_
	#undef Template_

#else

	#include "om/definition.hpp"

#endif
