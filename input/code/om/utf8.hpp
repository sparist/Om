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

#ifndef Om_Utf8_

	#define Om_Utf8_ \
	Om::Utf8

	#ifndef Om_Macros_Precompilation_

		#include "boost/locale/utf.hpp"

	#endif

namespace Om {

	/*!
	\brief
		The UTF-8 traits type.
	*/
	typedef boost::locale::utf::utf_traits<char> Utf8;

}

#endif
