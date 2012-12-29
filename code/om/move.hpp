/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
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
#if !defined( Om_Move_ )
	#define Om_Move_ Om::Move

	#include "external.hpp"

// MARK: - Om
namespace Om
{
	/*!
	\return
		A polymorphic move of the object.
	*/
	template< typename TheMoveable >
	std::auto_ptr< TheMoveable > Move( TheMoveable & );
}

	#include "om/move.cpp"
#endif