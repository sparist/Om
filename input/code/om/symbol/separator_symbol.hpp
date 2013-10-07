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

#ifndef Om_Symbol_SeparatorSymbol_

	#define Om_Symbol_SeparatorSymbol_ \
	Om::Symbol::SeparatorSymbol

	#include "om/macros.hpp"

	/*!
	\brief
		Generates switch cases for each Om::Symbol::SeparatorSymbol.
	*/
	#define Om_Symbol_SeparatorSymbol_GetCases_() \
	case Symbol::theSpaceSeparatorSymbol: \
	case Symbol::theLineSeparatorSymbol: \
	case Symbol::theTabSeparatorSymbol

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Symbol::theSpaceSeparatorSymbol.
	*/
	#define Om_Symbol_SeparatorSymbol_GetSpaceHex_() \
	20

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Symbol::theLineSeparatorSymbol.
	*/
	#define Om_Symbol_SeparatorSymbol_GetLineHex_() \
	0A

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Symbol::theTabSeparatorSymbol.
	*/
	#define Om_Symbol_SeparatorSymbol_GetTabHex_() \
	09

	/*!
	\brief
		A string literal representation of Om::Symbol::theSpaceSeparatorSymbol.
	*/
	#define Om_Symbol_SeparatorSymbol_GetSpaceString_() \
	Om_Macro_GetString_( \
		Om_Symbol_SeparatorSymbol_GetSpaceHex_() \
	)

	/*!
	\brief
		A string literal representation of Om::Symbol::theLineSeparatorSymbol.
	*/
	#define Om_Symbol_SeparatorSymbol_GetLineString_() \
	Om_Macro_GetString_( \
		Om_Symbol_SeparatorSymbol_GetLineHex_() \
	)

	/*!
	\brief
		A string literal representation of Om::Symbol::theTabSeparatorSymbol.
	*/
	#define Om_Symbol_SeparatorSymbol_GetTabString_() \
	Om_Macro_GetString_( \
		Om_Symbol_SeparatorSymbol_GetTabHex_() \
	)

namespace Om {

	namespace Symbol {

		/*!
		\brief
			A Separator symbol.
		*/
		enum SeparatorSymbol {

			theSpaceSeparatorSymbol = Om_Macro_GetNumber_(
				Om_Symbol_SeparatorSymbol_GetSpaceHex_()
			),

			theLineSeparatorSymbol = Om_Macro_GetNumber_(
				Om_Symbol_SeparatorSymbol_GetLineHex_()
			),

			theTabSeparatorSymbol = Om_Macro_GetNumber_(
				Om_Symbol_SeparatorSymbol_GetTabHex_()
			)

		};

	}

}

#endif
