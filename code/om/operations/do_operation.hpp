/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
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

\defgroup do_operation do
	\ingroup operations
	\brief
		Converts an \ref operand to a quoted \ref operator, then
		\ref dequote_operation "dequotes".
	\par Input
		<tt>{hello, world!}</tt>
	\par Output
		<tt>hello,` world!</tt>
	\par Implementation
		Om::Operations::DoOperation
*/
#if !defined( Om_Operations_DoOperation_ )
	#define Om_Operations_DoOperation_ Om::Operations::DoOperation

	#include "om/definition.hpp"

	#define Om_Operations_DoOperation_GetName_() "do"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::DoOperation
		/*!
		\brief
			The \ref do_operation Operation implementation.
		*/
		struct DoOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );
		};

		namespace
		{
			static Definition< DoOperation > const theDoDefinition;
		}
	}
}

	#include "om/operations/do_operation.cpp"
#endif
