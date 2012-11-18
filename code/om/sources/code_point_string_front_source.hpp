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
#if !defined( Om_Sources_CodePointStringFrontSource_ )
	#define Om_Sources_CodePointStringFrontSource_ \
	Om::Sources::CodePointStringFrontSource

	#include "om/sources/default_source.hpp"

namespace Om
{
	namespace Sources
	{
		// MARK: - Om::Sources::CodePointStringFrontSource
		/*!
		\brief
			A Source of #CodePoint strings from the front of a string.
		\note
			Const methods are not thread-safe due to a non-mutexed mutable
			member.
		\note
			Dereferencing exposes a reference to the member string cache of the
			current segment.  Modifying the string will not modify the source
			data.
		*/
		template< typename ThisStringIterator >
		struct CodePointStringFrontSource
		:
		DefaultSource<
			std::string,
			CodePointStringFrontSource< ThisStringIterator >
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

			CodePointStringFrontSource & operator =( CodePointStringFrontSource );

			bool operator ==( CodePointStringFrontSource const & ) const;

			virtual bool operator !() const;

			virtual std::string & operator *() const;

			virtual void Pop();

			void Swap( CodePointStringFrontSource & );

		private: // MARK: private (non-static)

			/*!
			\brief
				Populates the #CodePoint string with each code unit of the next
				#CodePoint.
			*/
			void Update();

			ThisStringIterator thisStringIterator;

			ThisStringIterator thisStringEnd;

			//! The current #CodePoint string; empty if invalid.
			mutable std::string thisCodePoint;
		};
	}
}

// MARK: - boost
namespace boost
{
	template< typename ThisStringIterator >
	void swap(
		Om::Sources::CodePointStringFrontSource< ThisStringIterator > &,
		Om::Sources::CodePointStringFrontSource< ThisStringIterator > &
	);
}

	#include "om/sources/code_point_string_front_source.cpp"
#endif
