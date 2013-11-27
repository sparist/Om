/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Source_Source_

	#define Om_Source_Source_ \
	Om::Source::Source

namespace Om {

	namespace Source {

		// MARK: - Om::Source::Source

		/*!
		\brief
			Any object that items can be pulled from.
		*/
		template <typename ThisItem>
		class Source {

		public: // MARK: public (static)

			/*!
			\brief
				The implementation of the Safe Boolean idiom.
			*/
			typedef void (Source::* Boolean)() const;

		public: // MARK: public (non-static)

			virtual ~Source() = 0;

			virtual ThisItem & operator *() const = 0;

			ThisItem * operator ->() const;

			/*!
			\return
				True if empty.
			*/
			virtual bool operator !() const = 0;

			/*!
			\brief
				Implements the Safe Boolean idiom.
			*/
			operator Boolean() const;

			/*!
			\return
				True when representing equivalent pointer-style iterators.
			*/
			virtual bool Equals(Source const &) const = 0;

			/*!
			\brief
				Pops the current item.
			\pre
				Not empty.
			*/
			virtual void Pop() = 0;

		private: // MARK: private (non-static)

			Source & operator =(Source const &);

			void UncomparableBoolean() const;

		};

	}

	// MARK: - Om::

	template <typename TheItem>
	bool operator ==(
		Source::Source<TheItem> const &,
		Source::Source<TheItem> const &
	);

	template <typename TheItem>
	bool operator !=(
		Source::Source<TheItem> const &,
		Source::Source<TheItem> const &
	);

}

	#include "om/source/source.cpp"

#endif
