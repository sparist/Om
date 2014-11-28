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

#ifndef Om_Language_Producer_

	#define Om_Language_Producer_ \
	Om::Language::Producer

	#ifndef Om_Macro_Precompilation_

		#include <memory>

	#endif

namespace Om {

	namespace Language {

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

}

	#include "om/language/producer.cpp"

#endif
