/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Sink_IteratorSink_

	#define Om_Sink_IteratorSink_ \
	Om::Sink::IteratorSink

	#include "om/sink/default_sink.hpp"

namespace Om {

	namespace Sink {

		// MARK: - Om::Sink::IteratorSink

		/*!
		\brief
			A Sink adapter for an output iterator.
		*/
		template <
			typename ThisItem,
			typename ThisIterator
		>
		class IteratorSink:
		public DefaultSink<
			ThisItem,
			IteratorSink<
				ThisItem,
				ThisIterator
			>
		> {

		public: // MARK: public (non-static)

			explicit IteratorSink(ThisIterator);

			IteratorSink & operator =(IteratorSink);

			virtual void Push(ThisItem &);

			void Swap(IteratorSink &);

		private: // MARK: private (non-static)

			/*!
			\brief
				The output iterator.
			*/
			ThisIterator thisIterator;

		};

	}

}

namespace boost {

	// MARK: - boost::

	template <
		typename TheItem,
		typename TheIterator
	>
	void swap(
		Om::Sink::IteratorSink<
			TheItem,
			TheIterator
		> &,
		Om::Sink::IteratorSink<
			TheItem,
			TheIterator
		> &
	);

}

	#include "om/sink/iterator_sink.cpp"

#endif
