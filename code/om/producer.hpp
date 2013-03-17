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

#ifndef Om_Producer_

	#define Om_Producer_ \
	Om::Producer

	#ifndef Om_Macros_Precompilation_

		#include <memory>

	#endif

namespace Om {

	//! \cond
	class Consumer;

	class Program;
	//! \endcond

	/*!
	\brief
		An Element giver; gives from the front.
	*/
	class Producer {

	public: // MARK: public (non-static)

		virtual ~Producer() = 0;

		/*!
		\brief
			Gives each contained Element to the argument.
		\post
			<code>IsEmpty() == true</code>
		\remarks
			Giving every Element is more efficient than giving a subset and managing incremental state, which is never necessary.
		*/
		virtual void GiveElements(Consumer &) = 0;

		/*!
		\brief
			\overload
		*/
		virtual void GiveElements(Consumer &) const = 0;

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

	private: // MARK: private (non-static)

		Producer & operator =(Producer const &);

	};

}

	#include "om/producer.cpp"

#endif
