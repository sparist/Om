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

#ifndef Om_Sources_CodePointStringBackSource_

	#define Om_Sources_CodePointStringBackSource_ \
	Om::Sources::CodePointStringBackSource

	#include "om/sources/default_source.hpp"

namespace Om {

	namespace Sources {

		// MARK: - Om::Sources::CodePointStringBackSource

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

			bool operator ==(CodePointStringBackSource const &) const;

			virtual bool operator !() const;

			virtual std::string & operator *() const;

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

	}

}

namespace boost {

	// MARK: - boost::

	template <typename ThisStringIterator>
	void swap(
		Om::Sources::CodePointStringBackSource<ThisStringIterator> &,
		Om::Sources::CodePointStringBackSource<ThisStringIterator> &
	);

}

	#include "om/sources/code_point_string_back_source.cpp"

#endif
