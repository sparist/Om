/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Definition_

	#define Om_Definition_ \
	Om::Definition

namespace Om {

	// MARK: - Om::Definition
	/*!
	\brief
		An inserter of an Operation into the static System instance.

	This is safe to construct before main, but the order of construction is implementation-defined; if there is more than one Operation with the same Operator, the choice of which to apply first will be implementation-defined.
	*/
	template <typename ThisOperation>
	class Definition {
	public: // MARK: public (non-static)

		/*!
		\brief
			Inserts the Operation into the System.

		If there is already an Operation mapped to the same Operator, it will be removed.
		*/
		Definition();

	};

}

	#include "om/definition.cpp"

#endif
