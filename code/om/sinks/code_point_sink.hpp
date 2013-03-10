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

#ifndef Om_Sinks_CodePointSink_

	#define Om_Sinks_CodePointSink_ \
	Om::Sinks::CodePointSink

	#include "om/code_point.hpp"
	#include "om/sinks/default_sink.hpp"

namespace Om {

	namespace Sinks {

		// MARK: - Om::Sinks::CodePointSink
		/*!
		\brief
			A #CodePoint Sink that pushes each code unit to the iterator.
		*/
		template <typename ThisCodeUnitIterator>
		class CodePointSink:
		public DefaultSink<
			CodePoint const,
			CodePointSink<ThisCodeUnitIterator>
		> {
		public: // MARK: public (non-static)

			explicit CodePointSink(ThisCodeUnitIterator);

			CodePointSink & operator =(CodePointSink);

			virtual void Push(CodePoint const &);

			void Swap(CodePointSink &);

		private: // MARK: private (non-static)

			/*!
			\brief
				The output code unit iterator.
			*/
			ThisCodeUnitIterator thisCodeUnitIterator;

		};

	}

}

// MARK: - boost
namespace boost {

	template <typename ThisCodeUnitIterator>
	void swap(
		Om::Sinks::CodePointSink<ThisCodeUnitIterator> &,
		Om::Sinks::CodePointSink<ThisCodeUnitIterator> &
	);

}

	#include "om/sinks/code_point_sink.cpp"

#endif
