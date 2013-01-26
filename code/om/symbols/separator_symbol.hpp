/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Symbols_SeparatorSymbol_ )

	#define Om_Symbols_SeparatorSymbol_ \
	Om::Symbols::SeparatorSymbol

	#include "om/macros.hpp"

	//! Generates switch cases for each Om::Symbols::SeparatorSymbol.
	#define Om_Symbols_SeparatorSymbol_GetCases_() \
	case Symbols::theSpaceSeparatorSymbol: \
	case Symbols::theLineSeparatorSymbol: \
	case Symbols::theTabSeparatorSymbol

	//! Gets the bare hexadecimal code for Om::Symbols::theSpaceSeparatorSymbol.
	#define Om_Symbols_SeparatorSymbol_GetSpaceHex_() \
	20

	//! Gets the bare hexadecimal code for Om::Symbols::theLineSeparatorSymbol.
	#define Om_Symbols_SeparatorSymbol_GetLineHex_() \
	0A

	//! Gets the bare hexadecimal code for Om::Symbols::theTabSeparatorSymbol.
	#define Om_Symbols_SeparatorSymbol_GetTabHex_() \
	09

	//! A string literal representation of Om::Symbols::theSpaceSeparatorSymbol.
	#define Om_Symbols_SeparatorSymbol_GetSpaceString_() \
	Om_Macros_GetString_( Om_Symbols_SeparatorSymbol_GetSpaceHex_() )

	//! A string literal representation of Om::Symbols::theLineSeparatorSymbol.
	#define Om_Symbols_SeparatorSymbol_GetLineString_() \
	Om_Macros_GetString_( Om_Symbols_SeparatorSymbol_GetLineHex_() )

	//! A string literal representation of Om::Symbols::theTabSeparatorSymbol.
	#define Om_Symbols_SeparatorSymbol_GetTabString_() \
	Om_Macros_GetString_( Om_Symbols_SeparatorSymbol_GetTabHex_() )

namespace Om
{
	namespace Symbols
	{
		//! A Separator symbol.
		enum SeparatorSymbol
		{
			theSpaceSeparatorSymbol = Om_Macros_GetNumber_( Om_Symbols_SeparatorSymbol_GetSpaceHex_() ),

			theLineSeparatorSymbol = Om_Macros_GetNumber_( Om_Symbols_SeparatorSymbol_GetLineHex_() ),

			theTabSeparatorSymbol = Om_Macros_GetNumber_( Om_Symbols_SeparatorSymbol_GetTabHex_() )
		};
	};
}

#endif
