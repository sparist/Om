/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operator_ )

	#define Om_Operator_ \
	Om::Operator

	#include "om/default_atom.hpp"
	#include "om/symbols/operand_symbol.hpp"
	#include "om/symbols/operator_symbol.hpp"
	#include "om/symbols/separator_symbol.hpp"

	#if !defined( Om_Macros_Precompilation_ )

		#include "boost/locale/boundary.hpp"

	#endif

	#define Om_Operator_GetName_() \
	"operator"

namespace Om {

	// MARK: - Om::Operator
	/*!
	\brief
		The \ref om__operator__ implementation.

	As a Queue, the Operator appends each taken Element verbatim.
	*/
	class Operator:
	public DefaultAtom< Operator > {
	public: // MARK: public (static)

		static char const * GetName();

	public: // MARK: public (non-static)

		Operator();

		/*!
		\brief
			Normalizes the string and copies directly into the Operator.
		*/
		explicit Operator( std::string const & );

		/*!
		\param theCodeUnitIterator
			A non-null pointer to the null-terminated code unit array to normalize and copy directly into the Operator.
		*/
		explicit Operator(
			char const theCodeUnitIterator[]
		);

		explicit Operator(
			Source< CodePoint const > &
		);

		explicit Operator( Symbols::OperandSymbol const );

		explicit Operator( Symbols::OperatorSymbol const );

		explicit Operator( Symbols::SeparatorSymbol const );

		Operator & operator =( Operator );

		/*!
		\brief
			Gives the last ::CodePoint as an Atom.
		*/
		void BackGiveCodePoint( Queue & );

		/*!
		\brief
			Gives the last segment of the given type to the Queue.
		*/
		template< boost::locale::boundary::boundary_type theSegment >
		void BackGiveSegment( Queue & );

		/*!
		\brief
			Decodes this Operator and gives each resulting Element to the argument.
		*/
		template< typename TheQueue >
		void Decode( TheQueue & ) const;

		/*!
		\brief
			Encodes the elements and replaces the contents of this Operator with the result.
		*/
		template< typename TheQueue >
		void Encode( TheQueue & );

		/*!
		\brief
			Gives the first ::CodePoint as an Atom.
		*/
		void FrontGiveCodePoint( Queue & );

		/*!
		\brief
			Gives the first segment of the given type to the Queue.
		*/
		template< boost::locale::boundary::boundary_type theSegment >
		void FrontGiveSegment( Queue & );

		/*!
		\brief
			Applies Unicode compatibility normalization.
		*/
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
namespace boost {

	template<>
	void swap(
		Om::Operator &,
		Om::Operator &
	);

}

	#include "om/operator.cpp"

#endif
