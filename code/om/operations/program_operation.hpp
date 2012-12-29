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
#if !defined( Om_Operations_ProgramOperation_ )
	#define Om_Operations_ProgramOperation_ Om::Operations::ProgramOperation

	#include "om/default_operation.hpp"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::ProgramOperation
		/*!
		\brief
			An Operation that normalizes a Program to a specific type.
		*/
		template< typename ThisProgram >
		struct ProgramOperation
		:
		DefaultOperation< ProgramOperation< ThisProgram > >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheProgramOperation >
			static void GiveElements( TheProgramOperation &, Queue & );

		public: // MARK: public (non-static)

			virtual bool ReadQuotedElements( Evaluation &, Parser & );

			template< typename TheOperand >
			bool TakeOperand( Evaluation &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluation &, TheQueue & );
		};
	}
}

	#include "om/operations/program_operation.cpp"
#endif