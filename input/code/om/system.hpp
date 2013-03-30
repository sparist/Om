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

#ifndef Om_System_

	#define Om_System_ \
	Om::System

	#include "om/translator.hpp"

	#ifndef Om_Macros_Precompilation_

		#include <map>

	#endif

namespace Om {

	//! \cond
	class Evaluation;

	class Lexicon;

	class Operator;
	//! \endcond

	// MARK: - Om::System

	/*!
	\brief
		Translates an Operator to an Operation.

	There is a single System instance, returned by the static Get() method.
	*/
	class System:

	public Translator {

	public: // MARK: public (static)

		template <typename ThisOperation>
		class Definition;

		/*!
		\return
			The static instance.
		*/
		static System & Get();

	public: // MARK: public (non-static)

		/*!
		\return
			The Lexicon representation of the System.
		*/
		Lexicon const & GetLexicon() const;

		virtual void GiveElements(Consumer &) const;

		/*!
		\brief
			Initializes the System.
		\param theLocaleCodeUnitIterator
			The null-terminated locale string (e.g. en_US.UTF-8). The locale must use UTF-8 encoding.

		Initializes the global locale to en_US.UTF-8 (using boost::locale) and asserts that all name keys in the System are NFD-normalized. This must be called in main, prior to any Program evaluation.
		*/
		void Initialize(
			char const theLocaleCodeUnitIterator[]
		);

		virtual bool IsEmpty() const;

		/*!
		\brief
			If there is an Operation mapped to the Operator, its implementation is given to the Evaluation.
		\return
			False if there is no Operation mapped to the Operator.
		*/
		virtual bool Translate(
			Evaluation &,
			Operator const &
		) const;

	private: // MARK: private (static)

		/*!
		\brief
			Maps the name to a function that gives the Operation with this name to the Evaluation.
		*/
		typedef std::map<
			std::string,
			void (*)(Evaluation &)
		> Map;

	private: // MARK: private (non-static)

		System();

		System(System const &);

		System const & operator =(System const &);

		Map thisMap;

	};

	// MARK: - Om::System::Definition

	/*!
	\brief
		An inserter of an Operation into the static System instance.

	This is safe to construct before main, but the order of construction is implementation-defined; if there is more than one Operation with the same Operator, the choice of which to apply first will be implementation-defined.
	*/
	template <typename ThisOperation>
	class System::Definition {

	public: // MARK: public (non-static)

		/*!
		\brief
			Inserts the Operation into the System.

		If there is already an Operation mapped to the same Operator, it will be removed.
		*/
		Definition();

	};

}

	#include "om/system.cpp"

#endif
