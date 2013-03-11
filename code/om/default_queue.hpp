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

#ifndef Om_DefaultQueue_

	#define Om_DefaultQueue_ \
	Om::DefaultQueue

	#include "om/queue.hpp"

namespace Om {

	// MARK: - Om::DefaultQueue

	/*!
	\brief
		A partial implementation of Queue.
	*/
	template <
		typename ThisImplementation,
		typename ThisInterface = Queue
	>
	class DefaultQueue:
	public ThisInterface {

	public: // MARK: public (non-static)

		virtual ~DefaultQueue() = 0;

		virtual void TakeElement(Operand &);

		virtual void TakeElement(Operand const &);

		virtual void TakeElement(Operator &);

		virtual void TakeElement(Operator const &);

		virtual void TakeElement(Separator &);

		virtual void TakeElement(Separator const &);

		virtual void TakeElements(Queue &);

		virtual void TakeElements(Queue const &);

		virtual void TakeQuotedElements(Queue &);

		virtual void TakeQuotedElements(Queue const &);

	private: // MARK: private (non-static)

		DefaultQueue & operator =(DefaultQueue const &);

	};

}

	#include "om/default_queue.cpp"

#endif
