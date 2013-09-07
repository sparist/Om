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

#ifndef Om_Sinks_IteratorSink_

	#define Om_Sinks_IteratorSink_ \
	Om::Sinks::IteratorSink

	#include "om/sinks/default_sink.hpp"

namespace Om {

	namespace Sinks {

		// MARK: - Om::Sinks::IteratorSink

		/*!
		\brief
			A Sink adapter for an output iterator.
		*/
		template <
			typename ThisItem,
			typename ThisIterator
		>
		class IteratorSink :
		public DefaultSink<
			ThisItem,
			IteratorSink<
				ThisItem,
				ThisIterator
			>
		>
		{

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
		Om::Sinks::IteratorSink<
			TheItem,
			TheIterator
		> &,
		Om::Sinks::IteratorSink<
			TheItem,
			TheIterator
		> &
	);

}

	#include "om/sinks/iterator_sink.cpp"

#endif
