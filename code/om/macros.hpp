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

#if !defined( Om_Macros_ )

	/*!
	\brief
		Defines a "namespace" for all global macros, aside from include guards.

	All global preprocessor definitions (excluding include guards) should use this namespace to avoid clashes, regardless of where they are physically defined.
	*/
	#define Om_Macros_ \
	Om::Macros

	//! Prepends <code>0x</code>.
	#define Om_Macros_PrependZeroX_( theArgument ) \
	0x ##theArgument

	//! Prepends <code>\\x</code> and converts the result to a string literal.
	#define Om_Macros_PrependSlashXAndStringize_( theArgument ) \
	BOOST_PP_STRINGIZE( \x ##theArgument )

	//! Converts a bare hexadecimal to a numeric literal.
	#define Om_Macros_GetNumber_( theHex ) \
	Om_Macros_PrependZeroX_( theHex )

	//! Converts a bare hexadecimal to a string literal.
	#define Om_Macros_GetString_( theHex ) \
	Om_Macros_PrependSlashXAndStringize_( theHex )

namespace Om
{
	//! A namespace for all code used to implement global macros.
	namespace Macros
	{
	}
}

#endif
