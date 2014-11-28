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

#ifndef Om_Language_Environment_

	#define Om_Language_Environment_ \
	Om::Language::Environment

	#include "om/language/translator.hpp"

namespace Om {

	namespace Language {

		// MARK: - Om::Language::Environment

		/*!
		\brief
			An unowned Translator collection for which lookups are done for each Translator, in reverse order, until a match is found.
		*/
		class Environment:
		public Translator {

		public: // MARK: public (non-static)

			Environment();

			virtual void GiveElements(Consumer &) const;

			virtual bool IsEmpty() const;

			/*!
			\brief
				Pushes an unowned Translator reference.

			If the given Translator is already the last reference in the Environment, there is no change.
			*/
			void Push(Translator const &);

			virtual bool Translate(
				Evaluation &,
				Operator const &
			) const;

		private: // MARK: private (static)

			/*!
			\brief
				A vector of non-owner Translator pointers.

			When looking up an Operator, the back Translator is used first. This requires the reverse iteration functionality provided by std::vector.
			*/
			typedef std::vector<Translator const *> TranslatorVector;

		private: // MARK: private (non-static)

			TranslatorVector thisTranslatorVector;

		};

	}

}

	#include "om/language/environment.cpp"

#endif
