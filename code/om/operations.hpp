/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_ )

	#define Om_Operations_ \
	Om::Operations

namespace Om {

	/*!
	\brief
		A namespace for all \ref operations.

	Each \ref operations "Operation" implementation requires the following:
	-	A <tt>static char const * GetName()</tt> function that returns a null-terminated, NFD-normalized UTF-8 string to be used as a corresponding Operator name.
	-	A <tt>static void Give( </tt><em>Evaluation</em><tt> )</tt> function, which gives the implementation of the \ref operations Operation to the Evaluation.

	Including the header for an \ref operations "Operation" will cause the \ref operations "Operation" to be added to the System automatically.

	\ref operations that consume at least one Operand must live in memory while waiting for the Operand.  These \ref operations are derived from Operation.
	*/
	namespace Operations {}
}

#endif
