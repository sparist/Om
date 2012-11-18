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
#if !defined( Om_Sources_DefaultSource_ )
	#define Om_Sources_DefaultSource_ Om::Sources::DefaultSource

	#include "om/source.hpp"

namespace Om
{
	namespace Sources
	{
		// MARK: - Om::Sources::DefaultSource
		/*!
		\brief
			A partial implementation of Source.
		*/
		template< typename ThisItem, typename ThisImplementation >
		struct DefaultSource
		:
		Source< ThisItem >,
		std::iterator< std::input_iterator_tag, ThisItem >
		{
		public: // MARK: public (non-static)

			virtual ~DefaultSource() = 0;

			/*!
			\return
				True if equal.
			\note
				This is only required to test equality in the context of the
				pointer-like STL iterator; doesn't take end into account.
			*/
			virtual bool operator ==( Source< ThisItem > const & ) const;

			/*!
			\overload
			*/
			virtual bool operator ==( ThisImplementation const & ) const = 0;

			/*!
			\brief
				Pulls the next item from the Source.
			\pre
				The Source cannot be empty.
			\return
				A reference to the derivation.
			*/
			ThisImplementation & operator ++();

			/*!
			\brief
				\overload
			\return
				A copy of the derivation.
			*/
			ThisImplementation operator ++( int );

		private: // MARK: private (non-static)

			DefaultSource & operator =( DefaultSource const & );
		};
	}
}

	#include "om/sources/default_source.cpp"
#endif
