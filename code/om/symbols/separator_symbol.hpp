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

#ifndef Om_Symbols_SeparatorSymbol_

	#define Om_Symbols_SeparatorSymbol_ \
	Om::Symbols::SeparatorSymbol

	#include "om/macros.hpp"

	/*!
	\brief
		Generates switch cases for each Om::Symbols::SeparatorSymbol.
	*/
	#define Om_Symbols_SeparatorSymbol_GetCases_() \
	case Symbols::theSpaceSeparatorSymbol: \
	case Symbols::theLineSeparatorSymbol: \
	case Symbols::theTabSeparatorSymbol

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Symbols::theSpaceSeparatorSymbol.
	*/
	#define Om_Symbols_SeparatorSymbol_GetSpaceHex_() \
	20

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Symbols::theLineSeparatorSymbol.
	*/
	#define Om_Symbols_SeparatorSymbol_GetLineHex_() \
	0A

	/*!
	\brief
		Gets the bare hexadecimal code for Om::Symbols::theTabSeparatorSymbol.
	*/
	#define Om_Symbols_SeparatorSymbol_GetTabHex_() \
	09

	/*!
	\brief
		A string literal representation of Om::Symbols::theSpaceSeparatorSymbol.
	*/
	#define Om_Symbols_SeparatorSymbol_GetSpaceString_() \
	Om_Macros_GetString_( \
		Om_Symbols_SeparatorSymbol_GetSpaceHex_() \
	)

	/*!
	\brief
		A string literal representation of Om::Symbols::theLineSeparatorSymbol.
	*/
	#define Om_Symbols_SeparatorSymbol_GetLineString_() \
	Om_Macros_GetString_( \
		Om_Symbols_SeparatorSymbol_GetLineHex_() \
	)

	/*!
	\brief
		A string literal representation of Om::Symbols::theTabSeparatorSymbol.
	*/
	#define Om_Symbols_SeparatorSymbol_GetTabString_() \
	Om_Macros_GetString_( \
		Om_Symbols_SeparatorSymbol_GetTabHex_() \
	)

namespace Om {

	namespace Symbols {

		/*!
		\brief
			A Separator symbol.
		*/
		enum SeparatorSymbol {

			theSpaceSeparatorSymbol = Om_Macros_GetNumber_(
				Om_Symbols_SeparatorSymbol_GetSpaceHex_()
			),

			theLineSeparatorSymbol = Om_Macros_GetNumber_(
				Om_Symbols_SeparatorSymbol_GetLineHex_()
			),

			theTabSeparatorSymbol = Om_Macros_GetNumber_(
				Om_Symbols_SeparatorSymbol_GetTabHex_()
			)

		};

	}

}

#endif
