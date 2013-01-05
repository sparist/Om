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
#if defined( Om_DefaultProgram_ )

	#include "om/element.hpp"
	#include "om/source.hpp"

// MARK: Om::DefaultProgram

	#define Template_ template< \
		typename ThisImplementation, \
		typename ThisInterface \
	>

	#define Type_ Om::DefaultProgram< ThisImplementation, ThisInterface >

// MARK: public (non-static)

Template_
inline Type_::~DefaultProgram()
{
}

/*!
\note
	This must be implemented in this class, vs. Program, due to Element
	dependency.
*/
Template_
inline bool Type_::operator ==( Program const & theProgram ) const
{
	std::auto_ptr< Source< Element const > > theRange = this->GetElementRange();
	assert( theRange.get() );

	std::auto_ptr<
		Source< Element const >
	> theOtherRange = theProgram.GetElementRange();
	assert( theOtherRange.get() );

	for( ; ; theRange->Pop(), theOtherRange->Pop() ){
		bool const theRangeHasNext = *theRange;
		bool const theOtherRangeHasNext = *theOtherRange;
		if( !theRangeHasNext || !theOtherRangeHasNext ){
			return( theRangeHasNext == theOtherRangeHasNext );
		}
		if( !( **theRange == **theOtherRange ) ){ return( false ); }
	}
}

Template_
inline void Type_::TakeElements( Queue & theQueue )
{
	this->TakeQueueElements< ThisImplementation >( theQueue );
}

Template_
inline void Type_::TakeElements( Queue const & theQueue )
{
	this->TakeQueueElements< ThisImplementation const >( theQueue );
}

// MARK: private (non-static)

Template_
template< typename TheCast, typename TheQueue >
inline void Type_::TakeQueueElements( TheQueue & theQueue )
{
	assert( dynamic_cast< ThisImplementation * >( this ) );
	assert( typeid( TheCast ) == typeid( ThisImplementation ) );
	if( typeid( TheCast ) == typeid( theQueue ) && this->IsEmpty() ){
		this->Take( static_cast< TheCast & >( theQueue ) );
	} else{ theQueue.GiveElements( *this ); }
}

	#undef Type_
	#undef Template_

#else
	#include "om/default_program.hpp"
#endif
