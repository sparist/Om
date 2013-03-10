/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Owner_

	#define Om_Owner_ \
	Om::Owner

	#include "om/taker.hpp"

	#ifndef Om_Macros_Precompilation_

		#include <memory>
		#include "boost/intrusive_ptr.hpp"

	#endif

namespace Om {

	// MARK: - Om::Owner
	/*!
	\brief
		A polymorphic object with value semantics.

	This class can be considered a "fat pointer" that holds the pointee, such that copying the pointer also copies the pointee (lazily).
	*/
	template <typename ThisValue>
	class Owner:
	public Taker<
		Owner<ThisValue>
	> {
	public: // MARK: public (static)

		/*!
		\brief
			The implementation of the Safe Boolean idiom.
		*/
		typedef void (Owner::* Boolean)() const;

	public: // MARK: public (non-static)

		Owner();

		Owner(Owner const &);

		template <typename TheValue>
		explicit Owner(
			std::auto_ptr<TheValue>
		);

		/*!
		\post
			Any references to the contained value, obtained via dereference, are invalidated.
		*/
		Owner & operator =(Owner);

		/*!
		\pre
			Not empty.
		\return
			The value. Do not retain this reference.
		*/
		ThisValue & operator *();

		/*!
		\overload
		*/
		ThisValue const & operator *() const;

		ThisValue * operator ->();

		ThisValue const * operator ->() const;

		/*!
		\return
			True if empty.
		*/
		bool operator !() const;

		/*!
		\brief
			Implements the "safe boolean" idiom.
		*/
		operator Boolean() const;

		/*!
		\post
			Any references to the contained value, obtained via dereference, are invalidated.
		*/
		void Clear();

		ThisValue * GetValue();

		ThisValue const * GetValue() const;

		/*!
		\return
			True if empty.
		*/
		bool IsEmpty() const;

		/*!
		\post
			Any references to the contained value, obtained via dereference, are invalidated.
		*/
		template <typename TheValue>
		void SetValue(
			std::auto_ptr<TheValue>
		);

		/*!
		\post
			Any references to the contained value, obtained via dereference, are invalidated.
		*/
		void Swap(Owner &);

	private: // MARK: private (non-static)

		void UncomparableBoolean() const;

		/*!
		\brief
			The pointer to the contained, lazily-copied value.
		*/
		boost::intrusive_ptr<ThisValue> thisValue;

		/*!
		\brief
			True if the contained value was exposed for modification.
		*/
		bool thisWasExposed;

	};

}

// MARK: - boost
namespace boost {

	template <typename ThisValue>
	void swap(
		Om::Owner<ThisValue> &,
		Om::Owner<ThisValue> &
	);

}

	#include "om/owner.cpp"

#endif
