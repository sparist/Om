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

#if !defined( Om_DefaultMoveable_ )

	#define Om_DefaultMoveable_ \
	Om::DefaultMoveable

	#include "om/moveable.hpp"

namespace Om
{
	// MARK: - Om::DefaultMoveable
	/*!
	\brief
		A partial implementation of Moveable.
	*/
	template<
		typename ThisImplementation,
		typename ThisInterface = Moveable
	>
	struct DefaultMoveable
	:
	ThisInterface
	{
		template< typename TheMoveable >
		friend std::auto_ptr< TheMoveable > Move( TheMoveable & );

	public: // MARK: public (non-static)

		virtual ~DefaultMoveable() = 0;

	private: // MARK: private (non-static)

		DefaultMoveable & operator =( DefaultMoveable const & );

		/*!
		\return
			An owner pointer to a moved object.
		*/
		virtual ThisInterface * Move();
	};
}

	#include "om/default_moveable.cpp"

#endif
