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
#if !defined( Om_Environment_ )
	#define Om_Environment_ Om::Environment

	#include "om/translator.hpp"

namespace Om
{

	// MARK: - Om::Environment
	/*!
	\brief
		A Translator that falls through to a System lookup.
	
	Applies a System lookup if Translator lookup fails (or System lookup is
	explicit by an Operator without an Operand definition).
	*/
	struct Environment
	:
	Translator
	{
	public: // MARK: public (non-static)

		Environment();

		Environment( Translator const & );

		Environment & operator =( Translator const & );

		/*!
		\brief
			Evaluates input from the #CodePoint Source and pushes it to the
			#CodePoint Sink.
		*/
		template< typename TheCodePointSource, typename TheCodePointSink >
		void Evaluate( TheCodePointSource &, TheCodePointSink & );

		/*!
		\brief
			A convenience overload that evaluates input from the string and
			returns the output string.
		\param theCodeUnitIterator
			A non-null pointer to a null-terminated code unit array.
		\return
			A string containing the output.

		This form is implemented in terms of the other form.
		*/
		std::string Evaluate( char const theCodeUnitIterator[] );

		/*!
		\return
			Returns the same values as Translator#Translate() except 1
			(Operator found, with no definition mapped), which is impossible.
		*/
		virtual int Translate( Expansion &, Operator const & ) const;
	};
}

	#include "om/environment.cpp"
#endif
