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

#if !defined( Om_Symbols_OperandSymbol_ )

	#define Om_Symbols_OperandSymbol_ \
	Om::Symbols::OperandSymbol

	#include "om/macros.hpp"

	/*!
	\brief
		Generates switch cases for each Om::Symbols::OperandSymbol.
	*/
	#define Om_Symbols_OperandSymbol_GetCases_() \
	case Symbols::theStartOperandSymbol: \
	case Symbols::theEndOperandSymbol

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Symbols::theStartOperandSymbol.
	*/
	#define Om_Symbols_OperandSymbol_GetStartHex_() \
	7B

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Symbols::theEndOperandSymbol.
	*/
	#define Om_Symbols_OperandSymbol_GetEndHex_() \
	7D

	/*!
	\brief
		A string literal representation of Om::Symbols::theStartOperandSymbol.
	*/
	#define Om_Symbols_OperandSymbol_GetStartString_() \
	Om_Macros_GetString_( Om_Symbols_OperandSymbol_GetStartHex_() )

	/*!
	\brief
		A string literal representation of Om::Symbols::theEndOperandSymbol.
	*/
	#define Om_Symbols_OperandSymbol_GetEndString_() \
	Om_Macros_GetString_( Om_Symbols_OperandSymbol_GetEndHex_() )

namespace Om {
	namespace Symbols {

		/*!
		\brief
			An Operand symbol.
		*/
		enum OperandSymbol {
			theStartOperandSymbol = Om_Macros_GetNumber_( Om_Symbols_OperandSymbol_GetStartHex_() ),

			theEndOperandSymbol = Om_Macros_GetNumber_( Om_Symbols_OperandSymbol_GetEndHex_() )
		};
	}
}

#endif
