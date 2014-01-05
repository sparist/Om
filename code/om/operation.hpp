/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup om__operation__ Operation
	\brief
		A function that processes 0 or more \ref om__operand__ "Operands" as data for computation.
	\par Implementation
		Each \ref om__operation__ is a concrete type in the Om::Operation namespace.
*/

#ifndef Om_Operation_

	#define Om_Operation_ \
	Om::Operation

namespace Om {

	/*!
	\brief
		A namespace for all \ref om__operation__ implementations.

	Each operation implementation requires the following:
	-	A <tt>static char const * GetName()</tt> function that returns a null-terminated, NFD-normalized UTF-8 string to be used as a corresponding Operator name.
	-	A <tt>static void Give(</tt><em>Evaluation</em><tt>)</tt> function, which gives the implementation of the operation to the Evaluation.

	Including the header for an operation will cause the operation to be added to the System automatically.

	Operations that consume at least one Operand must live in memory while waiting for the Operand. These operations are derived from Operation::IncompleteOperation.
	*/
	namespace Operation {}

}

#endif
