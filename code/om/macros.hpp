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

#if !defined( Om_Macros_ )

	/*!
	\brief
		Defines a "namespace" for all global macros, aside from include guards.

	All global preprocessor definitions (excluding include guards) should use this namespace to avoid clashes, regardless of where they are physically defined.
	*/
	#define Om_Macros_ \
	Om::Macros

	/*!
	\brief
		Prepends <code>0x</code>.
	*/
	#define Om_Macros_PrependZeroX_( theArgument ) \
	0x ##theArgument

	/*!
	\brief
		Prepends <code>\\x</code> and converts the result to a string literal.
	*/
	#define Om_Macros_PrependSlashXAndStringize_( theArgument ) \
	BOOST_PP_STRINGIZE( \x ##theArgument )

	/*!
	\brief
		Converts a bare hexadecimal to a numeric literal.
	*/
	#define Om_Macros_GetNumber_( theHex ) \
	Om_Macros_PrependZeroX_( theHex )

	/*!
	\brief
		Converts a bare hexadecimal to a string literal.
	*/
	#define Om_Macros_GetString_( theHex ) \
	Om_Macros_PrependSlashXAndStringize_( theHex )

namespace Om
{
	/*!
	\brief
		A namespace for all code used to implement global macros.
	*/
	namespace Macros
	{
	}
}

#endif
