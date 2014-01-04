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

#ifndef Om_Source_CodePointStringBackSource_

	#define Om_Source_CodePointStringBackSource_ \
	Om::Source::CodePointStringBackSource

	#include "om/source/default_source.hpp"

	#ifndef Om_Macro_Precompilation_

		#include <string>

	#endif

namespace Om {

	namespace Source {

		// MARK: - Om::Source::CodePointStringBackSource

		/*!
		\brief
			A Source of #CodePoint strings from the back of a string.
		\note
			Const methods are not thread-safe due to a non-mutexed mutable member.
		\note
			Dereferencing exposes a reference to the member string cache of the current segment. Modifying the string will not modify the source data.
		*/
		template <typename ThisStringIterator>
		class CodePointStringBackSource:
		public DefaultSource<
			std::string,
			CodePointStringBackSource<ThisStringIterator>
		> {

		public: // MARK: public (non-static)

			/*!
			\param theStringStart
				The string start.
			\param theStringEnd
				The string end.
			*/
			CodePointStringBackSource(
				ThisStringIterator theStringStart,
				ThisStringIterator const theStringEnd
			);

			CodePointStringBackSource & operator =(CodePointStringBackSource);

			virtual bool operator !() const;

			virtual std::string & operator *() const;

			using DefaultSource<
				std::string,
				CodePointStringBackSource<ThisStringIterator>
			>::Equals;

			bool Equals(CodePointStringBackSource const &) const;

			virtual void Pop();

			void Swap(CodePointStringBackSource &);

		private: // MARK: private (non-static)

			/*!
			\brief
				Populates the #CodePoint string with each code unit of the next #CodePoint.
			*/
			void Update();

			ThisStringIterator thisStringIterator;

			/*!
			\brief
				The current #CodePoint string iterator.
			*/
			ThisStringIterator thisCodePointIterator;

			/*!
			\brief
				The current #CodePoint string end.
			*/
			ThisStringIterator thisCodePointEnd;

			/*!
			\brief
				The current #CodePoint string.
			*/
			mutable std::string thisCodePoint;

		};

		// MARK: - Om::Source::

		template <typename TheStringIterator>
		bool operator ==(
			CodePointStringBackSource<TheStringIterator> const &,
			CodePointStringBackSource<TheStringIterator> const &
		);

		template <typename TheStringIterator>
		bool operator !=(
			CodePointStringBackSource<TheStringIterator> const &,
			CodePointStringBackSource<TheStringIterator> const &
		);

	}

}

namespace boost {

	// MARK: - boost::

	template <typename TheStringIterator>
	void swap(
		Om::Source::CodePointStringBackSource<TheStringIterator> &,
		Om::Source::CodePointStringBackSource<TheStringIterator> &
	);

}

	#include "om/source/code_point_string_back_source.cpp"

#endif
