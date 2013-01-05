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
#if defined( Om_Program_ )

	#include "om/give.hpp"

// MARK: Om::Program

	#define Type_ Om::Program

// MARK: public (non-static)

inline Type_::~Program()
{
}

inline std::auto_ptr<
	Om::Source< Om::Element const >
> Type_::GetElementRange() const
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

inline std::auto_ptr< Om::Program > Type_::GiveProgram()
{
	return( Give( *this ) );
}

inline std::auto_ptr< Om::Program > Type_::GiveProgram() const
{
	return( Give( *this ) );
}

	#undef Type_

#else
	#include "om/program.hpp"
#endif
