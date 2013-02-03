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

#if !defined( Om_Shareable_ )

	#define Om_Shareable_ \
	Om::Shareable

	#include "external.hpp"

namespace Om {
	// MARK: - Om::Shareable
	/*!
	\brief
		A pointee for boost::intrusive_ptr.

	This type can be used as a template argument for boost::intrusive_ptr.  Shared ownership is implemented via owner counting.
	*/
	template< typename ThisOwnerCount = size_t >
	class Shareable {
		/*!
		\cond internal_symbols
		\exception std::overflow_error
			On overflow.
		\note
			Called by the boost::intrusive_ptr constructors.
		*/
		template< typename TheOwnerCount >
		friend void intrusive_ptr_add_ref(
			Shareable< TheOwnerCount > * const
		);

		/*!
		\note
			Called by the boost::intrusive_ptr destructor.
		*/
		template< typename TheOwnerCount >
		friend void intrusive_ptr_release(
			Shareable< TheOwnerCount > * const
		);
		/*!
		\endcond
		*/

	public: // MARK: public (non-static)

		virtual ~Shareable() = 0;

		ThisOwnerCount GetOwnerCount() const;

	protected: // MARK: protected (non-static)

		Shareable();

		Shareable( Shareable const & );

		Shareable & operator =( Shareable const & );

	private: // MARK: private (non-static)

		void DecrementOwnerCount();

		void IncrementOwnerCount();

		/*!
		\brief
			The number of owners of this object.

		Automatic instances have a owner count of 0.  If the owner count is incremented from 0, it is owned by a boost::intrusive_ptr and is deleted when decremented back to zero.
		*/
		ThisOwnerCount thisOwnerCount;
	};
}

// MARK: - Om
namespace Om {
	//! \cond internal_symbols
	template< typename TheOwnerCount >
	void intrusive_ptr_add_ref(
		Shareable< TheOwnerCount > * const
	);

	template< typename TheOwnerCount >
	void intrusive_ptr_release(
		Shareable< TheOwnerCount > * const
	);
	//! \endcond
}

	#include "om/shareable.cpp"

#endif
