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

#ifndef Om_Sink_Sink_

	#define Om_Sink_Sink_ \
	Om::Sink::Sink

namespace Om {

	namespace Sink {

		// MARK: - Om::Sink::Sink

		/*!
		\brief
			Any object that items can be pushed to.
		*/
		template <typename ThisItem>
		class Sink {

		public: // MARK: public (non-static)

			virtual ~Sink() = 0;

			/*!
			\brief
				Pushes to the Sink.
			\return
				\c *this
			*/
			Sink & operator =(ThisItem &);

			/*!
			\return
				\c *this
			*/
			Sink & operator *();

			/*!
			\return
				\c this
			*/
			Sink * operator ->();

			/*!
			\brief
				Pushes an item.
			*/
			virtual void Push(ThisItem &) = 0;

		private: // MARK: private (non-static)

			Sink & operator =(Sink const &);

		};

	}

}

	#include "om/sink/sink.cpp"

#endif
