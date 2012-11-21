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

\defgroup operations Operations
	\brief
		Functions that each take a \ref programs "Program" as input and produce
		a \ref programs "Program" as output.
	\par Implementation
		\ref operations are concrete types in the Om#Operations namespace.
*/
#if !defined( Om_Operations_ )
	#define Om_Operations_ Om::Operations

namespace Om
{
	/*!
	\brief
		A namespace for all \ref operations.

	Each \ref operations "Operation" implementation requires the following:
	-	A static <tt>GetName()</tt> function that returns a null-terminated,
		NFD-normalized UTF-8 string to be used as a corresponding Operator name.
	-	A static <tt>Give( Evaluator & )</tt> function that gives the associated
		\ref Evaluand "Evaluand(s)" to the Evaluator.

	Including the header for an \ref operations "Operation" will cause the
	\ref operations "Operation" to be added to the System automatically.
	*/
	namespace Operations
	{
	}
}

#endif
