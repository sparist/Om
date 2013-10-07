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

#ifndef Om_Symbol_OperandSymbol_

	#define Om_Symbol_OperandSymbol_ \
	Om::Symbol::OperandSymbol

	#include "om/macros.hpp"

	/*!
	\brief
		Generates switch cases for each Om::Symbol::OperandSymbol.
	*/
	#define Om_Symbol_OperandSymbol_GetCases_() \
	case Symbol::theStartOperandSymbol: \
	case Symbol::theEndOperandSymbol

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Symbol::theStartOperandSymbol.
	*/
	#define Om_Symbol_OperandSymbol_GetStartHex_() \
	7B

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Symbol::theEndOperandSymbol.
	*/
	#define Om_Symbol_OperandSymbol_GetEndHex_() \
	7D

	/*!
	\brief
		A string literal representation of Om::Symbol::theStartOperandSymbol.
	*/
	#define Om_Symbol_OperandSymbol_GetStartString_() \
	Om_Macro_GetString_( \
		Om_Symbol_OperandSymbol_GetStartHex_() \
	)

	/*!
	\brief
		A string literal representation of Om::Symbol::theEndOperandSymbol.
	*/
	#define Om_Symbol_OperandSymbol_GetEndString_() \
	Om_Macro_GetString_( \
		Om_Symbol_OperandSymbol_GetEndHex_() \
	)

namespace Om {

	namespace Symbol {

		/*!
		\brief
			An Operand symbol.
		*/
		enum OperandSymbol {

			theStartOperandSymbol = Om_Macro_GetNumber_(
				Om_Symbol_OperandSymbol_GetStartHex_()
			),

			theEndOperandSymbol = Om_Macro_GetNumber_(
				Om_Symbol_OperandSymbol_GetEndHex_()
			)

		};

	}

}

#endif
