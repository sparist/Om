/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.1
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
#if defined( Om_Give_ )

	#include "om/copy.hpp"
	#include "om/move.hpp"

// MARK: Om

template< typename TheGiveable >
inline std::auto_ptr< TheGiveable > Om::Give( TheGiveable & theGiveable )
{
	return( Move( theGiveable ) );
}

template< typename TheGiveable >
inline std::auto_ptr< TheGiveable > Om::Give(
	std::auto_ptr< TheGiveable > & theGiveable
) 
{
	return( theGiveable );
}

template< typename TheGiveable >
inline std::auto_ptr< TheGiveable > Om::Give( TheGiveable const & theGiveable )
{
	return( Copy( theGiveable ) );
}

template< typename TheGiveable >
inline std::auto_ptr< TheGiveable > Om::Give(
	std::auto_ptr< TheGiveable > const & theGiveable
)
{
	return(
		theGiveable.get() ?
		Give( *theGiveable ) :
		std::auto_ptr< TheGiveable >()
	);
}

#else
	#include "om/give.hpp"
#endif
