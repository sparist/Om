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

#ifndef Om_Queue_

	#define Om_Queue_ \
	Om::Queue

	#ifndef Om_Macros_Precompilation_

		#include <memory>

	#endif

namespace Om {

	//! \cond
	class Operand;

	class Operator;

	class Parser;

	class Program;

	class Separator;
	//! \endcond

	// MARK: - Om::Queue

	/*!
	\brief
		A first-in, first-out Element processor.

	A Queue can take \ref Element "Elements" from another Queue, process them however the implementation decides, and give the resulting \ref Element "Elements" to another Queue.
	
	The contents of the Queue should not be assumed to reside in memory.
	*/
	class Queue {

	public: // MARK: public (non-static)

		virtual ~Queue() = 0;

		virtual void Clear() = 0;

		/*!
		\brief
			Gives each contained Element to the argument.
		\post
			<code>IsEmpty() == true</code>
		\remarks
			Giving every Element is more efficient than giving a subset and managing incremental state, which is never necessary.
		*/
		virtual void GiveElements(Queue &) = 0;

		/*!
		\brief
			\overload
		*/
		virtual void GiveElements(Queue &) const = 0;

		/*!
		\brief
			Returns a new Program populated with the contents of this.
		*/
		virtual std::auto_ptr<Program> GiveProgram() = 0;

		/*!
		\brief
			\overload
		*/
		virtual std::auto_ptr<Program> GiveProgram() const = 0;

		/*!
		\return
			True if there is no Element.
		*/
		virtual bool IsEmpty() const = 0;

		virtual void ReadElements(Parser &) = 0;

		virtual void ReadQuotedElements(Parser &) = 0;

		/*!
		\brief
			Takes a non-empty Element, which gets copied or swapped.
		\pre
			The Element argument is non-empty.

		It is up to the implementation to decide how to process an Element. Each Element is processed eagerly, meaning that two Operators received consecutively may be proceessed differently than the receipt of one Operator comprised of a concatenation of both.
		*/
		virtual void TakeElement(Operand &) = 0;

		/*!
		\brief
			\overload
		*/
		virtual void TakeElement(Operand const &) = 0;

		/*!
		\brief
			\overload
		*/
		virtual void TakeElement(Operator &) = 0;

		/*!
		\brief
			\overload
		*/
		virtual void TakeElement(Operator const &) = 0;

		/*!
		\brief
			\overload
		*/
		virtual void TakeElement(Separator &) = 0;

		/*!
		\brief
			\overload
		*/
		virtual void TakeElement(Separator const &) = 0;

		/*!
		\brief
			Takes each Element of the argument.
		*/
		virtual void TakeElements(Queue &) = 0;

		/*!
		\brief
			\overload
		*/
		virtual void TakeElements(Queue const &) = 0;

		/*!
		\brief
			Constructs and takes an Operand, which takes each Element from the argument Queue.
		*/
		virtual void TakeQuotedElements(Queue &) = 0;

		/*!
		\brief
			\overload
		*/
		virtual void TakeQuotedElements(Queue const &) = 0;

	private: // MARK: private (non-static)

		Queue & operator =(Queue const &);

	};

}

	#include "om/queue.cpp"

#endif
