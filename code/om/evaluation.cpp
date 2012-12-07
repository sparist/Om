/*!
\file
	\brief
		Om cpp file.
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
#if defined( Om_Evaluation_ )

// MARK: Om::Evaluation

	#define Type_ Om::Evaluation

// MARK: public (non-static)

inline Type_::~Evaluation()
{
}

inline void Type_::GiveElements( Queue & )
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

inline void Type_::GiveElements( Queue & ) const
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

inline bool Type_::ReadQuotedElements( Evaluator &, Parser & )
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

inline bool Type_::TakeElement( Evaluator &, Operand & )
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

inline bool Type_::TakeElement( Evaluator &, Operand const & )
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

inline bool Type_::TakeQuotedElements( Evaluator &, Queue & )
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

inline bool Type_::TakeQuotedElements( Evaluator &, Queue const & )
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

// MARK: protected (non-static)

inline Type_::Evaluation()
{
}

	#undef Type_

#else
	#include "om/evaluation.hpp"
#endif
