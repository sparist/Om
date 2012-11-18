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
#if defined( Om_Operations_InjectOperation_ )

// MARK: Om::Operations::InjectOperation

	#define Type_ Om::Operations::InjectOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_InjectOperation_GetName_() );
}

template< typename TheInjectOperation >
inline void Type_::GiveElements(
	TheInjectOperation & theInjectOperation,
	Queue & theQueue
)
{
	theQueue.TakeElement( GetOperator() );
	if( theInjectOperation.thisScope ){
		theQueue.TakeQuotedElements( theInjectOperation.thisInjector );
		if( !theInjectOperation.thisScope->IsEmpty() ){
			Expression theOutput;
			theOutput.Take( theInjectOperation.thisOutput );
			theInjectOperation.thisScope->GiveElements( theOutput );
			theQueue.TakeQuotedElements( theOutput );
		}
	}
}

// MARK: public (non-static)

inline Type_::InjectOperation()
:
thisInjector(),
thisOutput(),
thisScope()
{
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluator & theEvaluator,
	TheQueue & theQueue
)
{
	if( this->thisScope ){
		if( this->thisScope->IsEmpty() ){
			theQueue.GiveElements( *this->thisScope );
		} else{
			{
				Expression const & theInjector = this->thisInjector;
				theInjector.GiveElements( *this->thisScope );
			}
			this->thisScope->TakeQuotedQueue( theQueue );
		}
		if( this->thisScope->IsEmpty() ){
			theEvaluator.TakeQuotedQueue( this->thisOutput );
			return( true );
		}
	} else{
		this->thisScope = boost::in_place(
			boost::ref( this->thisOutput ),
			boost::ref( theEvaluator.GetTranslator() )
		);
		this->thisInjector.TakeElements( theQueue );
	}
	return( false );
}

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluator & theEvaluator,
	TheOperand & theOperand
)
{
	return(
		this->TakeQuotedQueue( theEvaluator, theOperand.GetChildProgram() )
	);
}

	#undef Type_

#else
	#include "om/operations/inject_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( InjectOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					(
						"{"
							"{"
								"a{{A}}\n"
								"b{{B}}\n"
								"c{{C}}"
							"}"
						"}{D}{E}"
					),
					Environment().Evaluate(
						"inject {quote} {fill {a b{{B}} c}} {A} {C} {D} {E}"
					)
				);

				CHECK_EQUAL(
					(
						"{"
							"{"
								"a{A}\n"
								"b{B}\n"
								"c{A}\n"
								"d{C}"
							"}{C}"
						"}{D}{E}"
					),
					Environment().Evaluate(
						"inject {copy} {fill {a b{B} c d}} {A} {C} {D} {E}"
					)
				);

				CHECK_EQUAL(
					(
						"inject{drop}{"
							"fill{"
								"a\n"
								"b{B}\n"
								"c\n"
								"d"
							"}"
						"}"
					),
					Environment().Evaluate(
						"inject {drop} {fill {a b{B} c d}} {A} {C} {D} {E}"
					)
				);
			}

			TEST( EmptyInjector )
			{
				CHECK_EQUAL(
					(
						"{"
							"{"
								"a{A}\n"
								"b{B}\n"
								"c{C}"
							"}"
						"}{D}{E}"
					),
					Environment().Evaluate(
						"inject {} {fill {a b{B} c}} {A} {C} {D} {E}"
					)
				);
			}

			TEST( EmptyOperation )
			{
				CHECK_EQUAL(
					"{}{A}{C}{D}{E}",
					Environment().Evaluate(
						"inject {quote} {} {A} {C} {D} {E}"
					)
				);
			}

			TEST( FlushWithNoOperands )
			{
				CHECK_EQUAL(
					"inject",
					Environment().Evaluate( "inject }" )
				);
			}

			TEST( FlushWithOneOperand )
			{
				CHECK_EQUAL(
					"inject{quote}",
					Environment().Evaluate( "inject {quote} }" )
				);
			}

			TEST( FlushWithTwoOperands )
			{
				CHECK_EQUAL(
					"inject{quote}{copy}",
					Environment().Evaluate( "inject {quote} {copy} }" )
				);
			}

			TEST( FlushWithMoreThanTwoOperands )
			{
				CHECK_EQUAL(
					(
						"inject{quote}{"
							"fill{"
								"a{A}\n"
								"b{B}\n"
								"c"
							"}"
						"}"
					),
					Environment().Evaluate(
						"inject {quote} {fill {a b c} {A} {B} }"
					)
				);
			}
		}
	}
}

	#endif

#endif
