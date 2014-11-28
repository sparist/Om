/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Language_Symbol_OperandSymbol_

	#define Om_Language_Symbol_OperandSymbol_ \
	Om::Language::Symbol::OperandSymbol

	#include "om/macro.hpp"

	/*!
	\brief
		Generates switch cases for each Om::Language::Symbol::OperandSymbol.
	*/
	#define Om_Language_Symbol_OperandSymbol_GetCases_() \
	case Symbol::theStartOperandSymbol: \
	case Symbol::theEndOperandSymbol

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Language::Symbol::theStartOperandSymbol.
	*/
	#define Om_Language_Symbol_OperandSymbol_GetStartHex_() \
	7B

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Language::Symbol::theEndOperandSymbol.
	*/
	#define Om_Language_Symbol_OperandSymbol_GetEndHex_() \
	7D

	/*!
	\brief
		A string literal representation of Om::Language::Symbol::theStartOperandSymbol.
	*/
	#define Om_Language_Symbol_OperandSymbol_GetStartString_() \
	Om_Macro_GetString_( \
		Om_Language_Symbol_OperandSymbol_GetStartHex_() \
	)

	/*!
	\brief
		A string literal representation of Om::Language::Symbol::theEndOperandSymbol.
	*/
	#define Om_Language_Symbol_OperandSymbol_GetEndString_() \
	Om_Macro_GetString_( \
		Om_Language_Symbol_OperandSymbol_GetEndHex_() \
	)

namespace Om {

	namespace Language {

		namespace Symbol {

			/*!
			\brief
				An Operand symbol.
			*/
			enum OperandSymbol {

				theStartOperandSymbol = Om_Macro_GetNumber_(
					Om_Language_Symbol_OperandSymbol_GetStartHex_()
				),

				theEndOperandSymbol = Om_Macro_GetNumber_(
					Om_Language_Symbol_OperandSymbol_GetEndHex_()
				)

			};

		}

	}

}

#endif
