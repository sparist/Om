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

#ifndef Om_Sinks_ContainerBackSink_

	#define Om_Sinks_ContainerBackSink_ \
	Om::Sinks::ContainerBackSink

	#include "om/sinks/default_sink.hpp"

namespace Om {

	namespace Sinks {

		// MARK: - Om::Sinks::ContainerBackSink

		/*!
		\brief
			A Sink adapter for a container; pushes items into the back.
		*/
		template <
			typename ThisItem,
			typename ThisContainer
		>
		class ContainerBackSink :
		public DefaultSink<
			ThisItem,
			ContainerBackSink<
				ThisItem,
				ThisContainer
			>
		>
		{

		public: // MARK: public (non-static)

			explicit ContainerBackSink(ThisContainer &);

			ContainerBackSink & operator =(ContainerBackSink);

			virtual void Push(ThisItem &);

			void Swap(ContainerBackSink &);

		private: // MARK: private (non-static)

			/*!
			\brief
				The container to push into.
			*/
			ThisContainer & thisContainer;

		};

	}

}

namespace boost {

	// MARK: - boost::

	template <
		typename TheItem,
		typename TheContainer
	>
	void swap(
		Om::Sinks::ContainerBackSink<
			TheItem,
			TheContainer
		> &,
		Om::Sinks::ContainerBackSink<
			TheItem,
			TheContainer
		> &
	);

}

	#include "om/sinks/container_back_sink.cpp"

#endif
