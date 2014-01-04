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

#ifndef Om_Sink_CodePointSink_

	#define Om_Sink_CodePointSink_ \
	Om::Sink::CodePointSink

	#include "om/code_point.hpp"
	#include "om/sink/default_sink.hpp"

namespace Om {

	namespace Sink {

		// MARK: - Om::Sink::CodePointSink

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

namespace boost {

	// MARK: - boost::

	template <typename TheCodeUnitIterator>
	void swap(
		Om::Sink::CodePointSink<TheCodeUnitIterator> &,
		Om::Sink::CodePointSink<TheCodeUnitIterator> &
	);

}

	#include "om/sink/code_point_sink.cpp"

#endif
