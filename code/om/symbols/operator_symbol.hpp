/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if !defined( Om_Symbols_OperatorSymbol_ )
	#define Om_Symbols_OperatorSymbol_ Om::Symbols::OperatorSymbol

	#include "om/macros.hpp"

	//! Gets the bare hexadecimal code for Om#Symbols#theEncodeOperatorSymbol.
	#define Om_Symbols_OperatorSymbol_GetEncodeHex_() 60

	//! A string literal representation of Om#Symbols#theEncodeOperatorSymbol.
	#define Om_Symbols_OperatorSymbol_GetEncodeString_() \
	Om_Macros_GetString_( Om_Symbols_OperatorSymbol_GetEncodeHex_() )

namespace Om
{
	namespace Symbols
	{
		//! An Operator symbol.
		enum OperatorSymbol
		{
			/*!
			Encodes the next #CodePoint as an Operator #CodePoint.  Redundant
			when followed by a non-symbol #CodePoint.
			*/
			theEncodeOperatorSymbol = Om_Macros_GetNumber_(
				Om_Symbols_OperatorSymbol_GetEncodeHex_()
			)
		};
	}
}

#endif
