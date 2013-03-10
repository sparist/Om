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

#ifndef Om_Sinks_ContainerFrontSink_

	#define Om_Sinks_ContainerFrontSink_ \
	Om::Sinks::ContainerFrontSink

	#include "om/sinks/default_sink.hpp"

namespace Om {

	namespace Sinks {

		// MARK: - Om::Sinks::ContainerFrontSink
		/*!
		\brief
			A Sink adapter for a container; pushes items into the front.
		*/
		template <
			typename ThisItem,
			typename ThisContainer
		>
		class ContainerFrontSink:
		public DefaultSink<
			ThisItem,
			ContainerFrontSink<
				ThisItem,
				ThisContainer
			>
		> {
		public: // MARK: public (non-static)

			explicit ContainerFrontSink(ThisContainer &);

			ContainerFrontSink & operator =(ContainerFrontSink);

			virtual void Push(ThisItem &);

			void Swap(ContainerFrontSink &);

		private: // MARK: private (non-static)

			/*!
			\brief
				The container to push into.
			*/
			ThisContainer & thisContainer;

		};

	}

}

// MARK: - boost
namespace boost {

	template <
		typename ThisItem,
		typename ThisContainer
	>
	void swap(
		Om::Sinks::ContainerFrontSink<
			ThisItem,
			ThisContainer
		> &,
		Om::Sinks::ContainerFrontSink<
			ThisItem,
			ThisContainer
		> &
	);

}

	#include "om/sinks/container_front_sink.cpp"

#endif
