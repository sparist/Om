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

#if !defined( Om_Sinks_DefaultSink_ )

	#define Om_Sinks_DefaultSink_ \
	Om::Sinks::DefaultSink

	#include "om/sink.hpp"

namespace Om {
	namespace Sinks {

		// MARK: - Om::Sinks::DefaultSink
		/*!
		\brief
			A partial Sink implementation.
		*/
		template<
			typename ThisItem,
			typename ThisImplementation
		>
		struct DefaultSink:
		public Sink< ThisItem >,
		public std::iterator<
			std::output_iterator_tag,
			ThisItem
		> {
		public: // MARK: public (non-static)

			virtual ~DefaultSink() = 0;

			ThisImplementation & operator ++();

			ThisImplementation operator ++( int );

		private: // MARK: private (non-static)

			DefaultSink & operator =( DefaultSink const & );
		};
	}
}

	#include "om/sinks/default_sink.cpp"

#endif
