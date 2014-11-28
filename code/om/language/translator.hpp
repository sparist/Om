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

#ifndef Om_Language_Translator_

	#define Om_Language_Translator_ \
	Om::Language::Translator

	#include "om/code_point.hpp"

	#ifndef Om_Macro_Precompilation_

		#include <string>

	#endif

namespace Om {

	//! \cond
	namespace Source {

		template <typename ThisItem>
		class Source;

	}

	namespace Sink {

		template <typename ThisItem>
		class Sink;

	}
	//! \endcond

	namespace Language {

		//! \cond
		class Consumer;

		class Evaluation;

		class Operator;
		//! \endcond

		// MARK: - Om::Language::Translator

		/*!
		\brief
			An Operator lookup for use by an Evaluator.
		*/
		class Translator {

		public: // MARK: public (non-static)

			/*!
			\brief
				Evaluates input from the #CodePoint Source and pushes it to the #CodePoint Sink.
			*/
			void Evaluate(
				Om::Source::Source<CodePoint const> &,
				Om::Sink::Sink<CodePoint const> &
			) const;

			/*!
			\brief
				A convenience overload that evaluates input from the string and returns the output string.
			\param theCodeUnitIterator
				A non-null pointer to a null-terminated code unit array.
			\return
				A string containing the output.

			This form is implemented in terms of the other form.
			*/
			std::string Evaluate(
				char const theCodeUnitIterator[]
			) const;

			virtual void GiveElements(Consumer &) const = 0;

			virtual bool IsEmpty() const = 0;

			/*!
			\brief
				Translates the Operator to an object that is then given to the Evaluation.
			\return
				True if the Operator was found.
			*/
			virtual bool Translate(
				Evaluation &,
				Operator const &
			) const = 0;

		};

	}

}

	#include "om/language/translator.cpp"

#endif
