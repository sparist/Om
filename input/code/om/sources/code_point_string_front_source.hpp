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

#ifndef Om_Sources_CodePointStringFrontSource_

	#define Om_Sources_CodePointStringFrontSource_ \
	Om::Sources::CodePointStringFrontSource

	#include "om/sources/default_source.hpp"

namespace Om {

	namespace Sources {

		// MARK: - Om::Sources::CodePointStringFrontSource

		/*!
		\brief
			A Source of #CodePoint strings from the front of a string.
		\note
			Const methods are not thread-safe due to a non-mutexed mutable member.
		\note
			Dereferencing exposes a non-const reference to the member string cache of the current segment, allowing swap as an optimization. Modifying the string will not modify the source data.
		*/
		template <typename ThisStringIterator>
		class CodePointStringFrontSource :
		public DefaultSource<
			std::string,
			CodePointStringFrontSource<ThisStringIterator>
		>
		{

		public: // MARK: public (non-static)

			/*!
			\param theStringStart
				The string start.
			\param theStringEnd
				The string end.
			*/
			CodePointStringFrontSource(
				ThisStringIterator theStringStart,
				ThisStringIterator const theStringEnd
			);

			CodePointStringFrontSource & operator =(CodePointStringFrontSource);

			virtual bool operator !() const;

			virtual std::string & operator *() const;

			using DefaultSource<
				std::string,
				CodePointStringFrontSource<ThisStringIterator>
			>::Equals;

			bool Equals(CodePointStringFrontSource const &) const;

			virtual void Pop();

			void Swap(CodePointStringFrontSource &);

		private: // MARK: private (non-static)

			/*!
			\brief
				Populates the #CodePoint string with each code unit of the next #CodePoint.
			*/
			void Update();

			ThisStringIterator thisStringIterator;

			ThisStringIterator thisStringEnd;

			/*!
				The current #CodePoint string; empty if invalid.
			*/
			mutable std::string thisCodePoint;

		};

		// MARK: - Om::Sources::

		template <typename TheStringIterator>
		bool operator ==(
			CodePointStringFrontSource<TheStringIterator> const &,
			CodePointStringFrontSource<TheStringIterator> const &
		);

		template <typename TheStringIterator>
		bool operator !=(
			CodePointStringFrontSource<TheStringIterator> const &,
			CodePointStringFrontSource<TheStringIterator> const &
		);

	}

}

namespace boost {

	// MARK: - boost::

	template <typename TheStringIterator>
	void swap(
		Om::Sources::CodePointStringFrontSource<TheStringIterator> &,
		Om::Sources::CodePointStringFrontSource<TheStringIterator> &
	);

}

	#include "om/sources/code_point_string_front_source.cpp"

#endif
