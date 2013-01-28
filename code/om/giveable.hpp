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

#if !defined( Om_Giveable_ )

	#define Om_Giveable_ \
	Om::Giveable

	#include "om/copyable.hpp"
	#include "om/moveable.hpp"

namespace Om
{
	// MARK: - Om::Giveable
	/*!
	\brief
		An object that can be copied or moved via #Give.
	*/
	struct Giveable:
	Copyable,
	Moveable
	{
	public: // MARK: public (non-static)

		virtual ~Giveable() = 0;

	private: // MARK: private (non-static)

		Giveable & operator =( Giveable const & );
	};
}

	#include "om/giveable.cpp"

#endif
