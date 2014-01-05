/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Taker_

	#define Om_Taker_ \
	Om::Taker

namespace Om {

	// MARK: - Om::Taker

	/*!
	\brief
		An object that can take (copy or swap) another of the same type.
	*/
	template <typename ThisImplementation>
	class Taker {

	public: // MARK: public (non-static)

		virtual ~Taker() = 0;

		/*!
		\brief
			Swaps.
		*/
		void Take(ThisImplementation &);

		/*!
		\brief
			Assigns.
		*/
		void Take(ThisImplementation const &);

	private: // MARK: private (non-static)

		Taker & operator =(Taker const &);

	};

}

	#include "om/taker.cpp"

#endif
