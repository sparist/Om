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
#if defined( Om_Element_ )

// MARK: Om

inline Om::Element * Om::new_clone( Element const & theElement )
{
	return( Copy( theElement ).release() );
}

// MARK: -
// MARK: Om::Element

	#define Type_ Om::Element

// MARK: public (non-static)

inline Type_::~Element()
{
}

inline bool Type_::operator ==( Element const & ) const
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

inline Om::Program & Type_::operator *()
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

inline Om::Program const & Type_::operator *() const
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

inline Om::Program * Type_::operator ->()
{
	return( &**this );
}

inline Om::Program const * Type_::operator ->() const
{
	return( &**this );
}

inline std::auto_ptr< Om::Source< Om::Element > > Type_::GetElementRange()
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

inline bool Type_::Merge( Operator & )
{
	return( false );
}

inline bool Type_::Merge( Operator const & )
{
	return( false );
}

inline bool Type_::Merge( Separator & )
{
	return( false );
}

inline bool Type_::Merge( Separator const & )
{
	return( false );
}

	#undef Type_

#else
	#include "om/element.hpp"
#endif
