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
*/

#ifndef Om_Symbol_OperatorSymbol_

	#define Om_Symbol_OperatorSymbol_ \
	Om::Symbol::OperatorSymbol

	#include "om/macro.hpp"

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Symbol::theEncodeOperatorSymbol.
	*/
	#define Om_Symbol_OperatorSymbol_GetEncodeHex_() \
	60

	/*!
	\brief
		A string literal representation of Om::Symbol::theEncodeOperatorSymbol.
	*/
	#define Om_Symbol_OperatorSymbol_GetEncodeString_() \
	Om_Macro_GetString_( \
		Om_Symbol_OperatorSymbol_GetEncodeHex_() \
	)

namespace Om {

	namespace Symbol {

		/*!
		\brief
			An Operator symbol.
		*/
		enum OperatorSymbol {

			/*!
			Encodes the next #CodePoint as an Operator #CodePoint. Redundant when followed by a non-symbol #CodePoint.
			*/
			theEncodeOperatorSymbol = Om_Macro_GetNumber_(
				Om_Symbol_OperatorSymbol_GetEncodeHex_()
			)

		};

	}

}

#endif
