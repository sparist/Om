/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Environment_ )

	#define Om_Environment_ \
	Om::Environment

	#include "om/translator.hpp"

namespace Om
{
	// MARK: - Om::Environment
	/*!
	\brief
		An unowned Translator collection for which lookups are done for each Translator, in reverse order, until a match is found.
	*/
	struct Environment
	:
	Translator
	{
	public: // MARK: public (non-static)

		Environment();

		virtual void GiveElements( Queue & ) const;

		virtual bool IsEmpty() const;

		/*!
		\brief
			Pushes an unowned Translator reference.

		If the given Translator is already the last reference in the Environment, there is no change.
		*/
		void Push( Translator const & );

		virtual bool Translate(
			Evaluation &,
			Operator const &
		) const;

	private: // MARK: private (static)

		/*!
		\brief
			A vector of non-owner Translator pointers.

		When looking up an Operator, the back Translator is used first.  This requires the reverse iteration functionality provided by std::vector.
		*/
		typedef std::vector< Translator const * > TranslatorVector;

	private: // MARK: private (non-static)

		TranslatorVector thisTranslatorVector;
	};
}

	#include "om/environment.cpp"

#endif
