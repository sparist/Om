/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if !defined( Om_Translator_ )
	#define Om_Translator_ Om::Translator

	#include "om/sinks/default_sink.hpp"
	#include "om/taker.hpp"

namespace Om
{
	//! \cond
	struct Evaluation;

	struct Lexicon;

	struct Operator;
	//! \endcond

	// MARK: - Om::Translator
	/*!
	\brief
		An Operator lookup for use by an Evaluator.

	Looks up in each Lexicon in turn, starting from the top, until the
	definition is found.
	*/
	struct Translator
	:
	Sinks::DefaultSink< Lexicon const, Translator >,
	Taker< Translator >
	{
	public: // MARK: public (non-static)

		Translator();
		
		Translator & operator =( Translator );

		//! Pushes a Lexicon reference.
		virtual void Push( Lexicon const & );

		void Swap( Translator & );

		/*!
		\brief
			Translates the Operator to an object that is then given to the
			Evaluation.
		\return
			True if the Operator was found.
		*/
		virtual bool Translate( Evaluation &, Operator const & ) const;

	private: // MARK: private (static)

		/*!
		\brief
			A vector of non-owner Lexicon pointers.

		When looking up an Operator, the back Lexicon is used first.  This
		requires the reverse iteration functionality provided by std#vector.
		*/
		typedef std::vector< Lexicon const * > LexiconVector;

	private: // MARK: private (non-static)

		LexiconVector thisLexiconVector;
	};
}

// MARK: - boost
namespace boost
{
	template<>
	void swap( Om::Translator &, Om::Translator & );
}

	#include "om/translator.cpp"
#endif
