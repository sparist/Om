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

#if !defined( Om_Source_ )

	#define Om_Source_ \
	Om::Source

namespace Om
{
	// MARK: - Om::Source
	/*!
	\brief
		Any object that items can be pulled from.
	*/
	template< typename ThisItem >
	struct Source
	{
	public: // MARK: public (static)

		/*!
		\brief
			The implementation of the "safe boolean" idiom.
		*/
		typedef void ( Source::* Boolean )() const;

	public: // MARK: public (non-static)

		virtual ~Source() = 0;

		/*!
		\return
			True when representing equivalent pointer-style iterators.
		*/
		virtual bool operator ==( Source const & ) const = 0;

		/*!
		\return
			True when not representing equivalent pointer-style iterators.
		*/
		template< typename TheSource >
		bool operator !=( TheSource const & ) const;

		virtual ThisItem & operator *() const = 0;

		ThisItem * operator ->() const;

		/*!
		\return
			True if empty.
		*/
		virtual bool operator !() const = 0;

		/*!
		\brief
			Implements the "safe boolean" idiom.
		*/
		operator Boolean() const;

		/*!
		\brief
			Pops the current item.
		\pre
			Not empty.
		*/
		virtual void Pop() = 0;

	private: // MARK: private (non-static)

		Source & operator =( Source const & );

		void UncomparableBoolean() const;
	};
}

	#include "om/source.cpp"

#endif
