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

\defgroup separator Separator
	\ingroup programs
	\brief
		An atomic \ref programs "Program" element that serves to separate other
		elements.
	\par Implementation
		Om#Separator
*/
#if !defined( Om_Separator_ )
	#define Om_Separator_ Om::Separator

	#include "om/default_atom.hpp"
	#include "om/symbols/separator_symbol.hpp"

	#define Om_Separator_GetName_() "separator"

namespace Om
{
	// MARK: - Om::Separator
	/*!
	\brief
		The \ref separator implementation.

	An Atom defined by a string containing only Symbols#SeparatorSymbol
	characters.

	As a Queue, the Separator filters out all top-level Element instances except
	Separator.
	*/
	struct Separator
	:
	DefaultAtom< Separator >
	{
	public: // MARK: public (static)

		/*!
		\return
			A Separator comprised of a single Symbols#theLineSeparatorSymbol.
		*/
		static Separator const & GetLineSeparator();

		static char const * GetName();

	public: // MARK: public (non-static)

		Separator();

		explicit Separator( Source< CodePoint const > & );

		/*!
		\param theSeparatorSymbol
			The Symbols#SeparatorSymbol to copy directly into the Separator.
		*/
		explicit Separator( Symbols::SeparatorSymbol const theSeparatorSymbol );

		Separator & operator =( Separator );

		virtual void ReadElements( Parser & );

		virtual void ReadQuotedElements( Parser & );

		template< typename TheOperand >
		void TakeOperand( TheOperand & );

		template< typename TheOperator >
		void TakeOperator( TheOperator & );

		template< typename TheQueue >
		void TakeQuotedQueue( TheQueue & );

		template< typename TheSeparator >
		void TakeSeparator( TheSeparator & );

		void TakeSeparatorSymbol( Symbols::SeparatorSymbol const );
	};
}

// MARK: - boost
namespace boost
{
	template<>
	void swap( Om::Separator &, Om::Separator & );
}

	#include "om/separator.cpp"
#endif
