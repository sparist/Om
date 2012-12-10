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

\defgroup copy_operation copy
	\ingroup operations
	\brief
		Copies an \ref operand.
	\par Input
		<tt>{A}</tt>
	\par Output
		<tt>{A}{A}</tt>
	\par Implementation
		Om#Operations#CopyOperation
*/
#if !defined( Om_Operations_CopyOperation_ )
	#define Om_Operations_CopyOperation_ Om::Operations::CopyOperation

	#include "om/default_evaluation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_CopyOperation_GetName_() "copy"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::CopyOperation
		/*!
		\brief
			The \ref copy_operation Operation implementation.
		*/
		struct CopyOperation
		:
		DefaultEvaluation< CopyOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheCopyOperation >
			static void GiveElements( TheCopyOperation &, Queue & );

		public: // MARK: public (non-static)

			template< typename TheOperand >
			bool TakeOperand( Expansion &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Expansion &, TheQueue & );
		};

		namespace
		{
			static Definition< CopyOperation > const theCopyDefinition;
		}
	}
}

	#include "om/operations/copy_operation.cpp"
#endif
