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

\defgroup operator Operator
	\ingroup programs
	\brief
		An atomic \ref programs "Program" element defined by any UTF-8 string.
	\par Implementation
		Om#Operator
*/
#if !defined( Om_Operator_ )
	#define Om_Operator_ Om::Operator

	#include "om/default_atom.hpp"
	#include "om/symbols/operand_symbol.hpp"
	#include "om/symbols/operator_symbol.hpp"
	#include "om/symbols/separator_symbol.hpp"

	#define Om_Operator_GetName_() "operator"

namespace Om
{
	// MARK: - Om::Operator
	/*!
	\brief
		The \ref operator implementation.

	As a Queue, the Operator appends each taken Element verbatim.
	*/
	struct Operator
	:
	DefaultAtom< Operator >
	{
	public: // MARK: public (static)

		static char const * GetName();

	public: // MARK: public (non-static)

		Operator();

		//! Normalizes the string and copies directly into the Operator.
		explicit Operator( std::string const & );

		/*!
		\param theCodeUnitIterator
			A non-null pointer to the null-terminated code unit array to
			normalize and copy directly into the Operator.
		*/
		explicit Operator( char const theCodeUnitIterator[] );

		explicit Operator( Source< CodePoint const > & );

		explicit Operator( Symbols::OperandSymbol const );

		explicit Operator( Symbols::OperatorSymbol const );

		explicit Operator( Symbols::SeparatorSymbol const );

		Operator & operator =( Operator );

		//! Gives the last #CodePoint as an Atom.
		void BackGiveCodePoint( Queue & );

		//! Gives the last segment of the given type to the Queue.
		template< boost::locale::boundary::boundary_type theSegment >
		void BackGiveSegment( Queue & );

		/*!
		\brief
			Decodes this Operator and gives each resulting Element to the
			argument.
		*/
		template< typename TheQueue >
		void Decode( TheQueue & ) const;

		/*!
		\brief
			Encodes the elements and replaces the contents of this Operator with
			the result.
		*/
		template< typename TheQueue >
		void Encode( TheQueue & );

		//! Gives the first #CodePoint as an Atom.
		void FrontGiveCodePoint( Queue & );

		//! Gives the first segment of the given type to the Queue.
		template< boost::locale::boundary::boundary_type theSegment >
		void FrontGiveSegment( Queue & );

		//! Applies Unicode compatibility normalization.
		void Normalize();

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
	};
}

// MARK: - boost
namespace boost
{
	template<>
	void swap( Om::Operator &, Om::Operator & );
}

	#include "om/operator.cpp"
#endif
