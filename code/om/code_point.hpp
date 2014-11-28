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

#ifndef Om_CodePoint_

	#define Om_CodePoint_ \
	Om::CodePoint

	#ifndef Om_Macro_Precompilation_

		#include "boost/locale/utf.hpp"

	#endif

namespace Om {

	/*!
	\brief
		A UTF-8 code point.
	*/
	typedef boost::locale::utf::code_point CodePoint;

}

#endif
