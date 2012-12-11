/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
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
#if !defined( Om_System_ )
	#define Om_System_ Om::System

	#include "external.hpp"

namespace Om
{
	//! \cond
	struct Expansion;

	struct Operator;
	//! \endcond

	// MARK: - Om::System
	/*!
	\brief
		Translates an Operator to an Operation.

	There is a single System instance, returned by the static Get() method.
	*/
	struct System
	{
		template< typename ThisOperation >
		friend struct Definition;

	public: // MARK: public (static)

		/*!
		\return
			The static instance.
		*/
		static System & Get();

	public: // MARK: public (non-static)

		/*!
		\brief
			Initializes the System.
		\param theLocaleCodeUnitIterator
			The null-terminated locale string (e.g. en_US.UTF-8).  The locale
			must use UTF-8 encoding.

		Initializes the global locale to en_US.UTF-8 (using boost#locale) and
		asserts that all name keys in the System are NFD-normalized.
		This must be called in main, prior to any Program evaluation.
		*/
		void Initialize( char const theLocaleCodeUnitIterator[] );

		/*!
		\brief
			If there is an Operation mapped to the Operator, its implementation
			is given to the Expansion.
		\return
			False if there is no Operation mapped to the Operator.
		*/
		bool Translate( Expansion &, Operator const & ) const;

	private: // MARK: private (static)

		/*!
		\brief
			Maps the name to a function that gives the Operation with this name
			to the Expansion.
		*/
		typedef std::map< std::string, void ( * )( Expansion & ) > Map;

	private: // MARK: private (non-static)

		System();

		System( System const & );

		System const & operator =( System const & );

		Map thisMap;
	};
}

	#include "om/system.cpp"
#endif
