/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Taker_ )

	#define Om_Taker_ \
	Om::Taker

namespace Om
{
	// MARK: - Om::Taker
	/*!
	\brief
		An object that can take (copy or swap) another of the same type.
	*/
	template< typename ThisImplementation >
	struct Taker
	{
	public: // MARK: public (non-static)

		virtual ~Taker() = 0;

		//! Swaps.
		void Take( ThisImplementation & );

		//! Assigns.
		void Take( ThisImplementation const & );

	private: // MARK: private (non-static)

		Taker & operator =( Taker const & );
	};
}

	#include "om/taker.cpp"

#endif
