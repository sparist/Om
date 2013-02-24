/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Queue_ )

	#include "om/queue.hpp"

	#if defined( Om_Macros_Test_ )

		#if !defined( Om_Macros_Precompilation_ )

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE( QueueTest )
	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#if !defined( Om_Macros_Precompilation_ )

		#include <cassert>
		#include <stdexcept>

	#endif

// MARK: - Om::Queue

	#define Type_ \
	Om::Queue

// MARK: public (non-static)

inline Type_::~Queue() {}

inline bool Type_::operator ==( Program const & ) const {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

template< typename TheProgram >
inline bool Type_::operator !=( TheProgram const & theProgram ) const {
	return(
		!( theProgram == *this )
	);
}

inline void Type_::Clear() {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::GiveElements( Queue & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::GiveElements( Queue & ) const {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline std::auto_ptr< Om::Program > Type_::GiveProgram() {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline std::auto_ptr< Om::Program > Type_::GiveProgram() const {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline bool Type_::IsEmpty() const {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::ReadElements( Parser & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::ReadQuotedElements( Parser & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::TakeElement( Operand & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::TakeElement( Operand const & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::TakeElement( Operator & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::TakeElement( Operator const & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::TakeElement( Separator & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::TakeElement( Separator const & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::TakeElements( Queue & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::TakeElements( Queue const & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::TakeQuotedElements( Queue & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

inline void Type_::TakeQuotedElements( Queue const & ) {
	assert( 0 );
	throw(
		std::logic_error( "Pure virtual function called." )
	);
}

	#undef Type_

#endif
