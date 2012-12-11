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

\defgroup dequote_operation dequote
	\ingroup operations
	\brief
		Strips the outer braces from an \ref operand.
	\par Input
		<tt>{A}</tt>
	\par Output
		<tt>A</tt>
	\par Implementation
		Om#Operations#DequoteOperation
*/
#if !defined( Om_Operations_DequoteOperation_ )
	#define Om_Operations_DequoteOperation_ Om::Operations::DequoteOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_DequoteOperation_GetName_() "dequote"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::DequoteOperation
		/*!
		\brief
			The \ref dequote_operation Operation implementation.
		*/
		struct DequoteOperation
		:
		DefaultOperation< DequoteOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheDequoteOperation >
			static void GiveElements( TheDequoteOperation &, Queue & );

		public: // MARK: public (non-static)

			template< typename TheOperand >
			bool TakeOperand( Expansion &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Expansion &, TheQueue & );
		};

		namespace
		{
			static Definition< DequoteOperation > const theDequoteDefinition;
		}
	}
}

	#include "om/operations/dequote_operation.cpp"
#endif
