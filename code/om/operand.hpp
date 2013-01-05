/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup operand Operand
	\ingroup programs
	\brief
		A \ref programs "Program" element that wraps a \ref programs "Program".
	\par Interpretation
		An \ref operand is an interpretation of a \ref programs "Program" as
		either containing a single operand element (a \ref programs "Program"
		enclosed by braces), or being empty.  All elements other than the first
		operand element are disregarded.
	\par Normalization
		A \ref programs "Program" is normalized as an \ref operand by discarding
		all elements other than the first operand element.
	\par Implementation
		Om#Operand
*/
#if !defined( Om_Operand_ )
	#define Om_Operand_ Om::Operand

	#include "om/default_element.hpp"
	#include "om/owner.hpp"

	#define Om_Operand_GetName_() "operand"

namespace Om
{
	// MARK: - Om::Operand
	/*!
	\brief
		The \ref operand implementation.

	Encloses a Program in Symbols#theStartOperandSymbol and
	Symbols#theEndOperandSymbol.  The Operand owns the embedded Program.
	*/
	struct Operand
	:
	DefaultElement< Operand >
	{
	public: // MARK: public (static)

		static char const * GetName();

	public: // MARK: public (non-static)

		Operand();

		template< typename TheProgram >
		explicit Operand( std::auto_ptr< TheProgram > );

		Operand & operator =( Operand );

		bool operator ==( Operand const & ) const;

		/*!
		\return
			A reference to the Program owned by this Operand.  Do not retain
			this reference.
		*/
		virtual Program & operator *();

		/*!
		\overload
		*/
		virtual Program const & operator *() const;

		virtual void Clear();

		/*!
		\return
			A reference to the Program owned by this Operand, or null if none.
			Do not retain this reference.
		*/
		Program * GetProgram();

		/*!
		\overload
		*/
		Program const * GetProgram() const;

		/*!
		\return
			True if this instance represents an empty Program, which is the case
			if there is no inner Program (i.e. via default construction).
		*/
		virtual bool IsEmpty() const;

		virtual void ReadElements( Parser & );

		virtual void ReadQuotedElements( Parser & );

		//! Replaces the Program owned by this Operand with the argument.
		template< typename TheProgram >
		void SetProgram( std::auto_ptr< TheProgram > );

		void Swap( Operand & );

		virtual void TakeElements( Queue & );

		virtual void TakeElements( Queue const & );

		template< typename TheOperand >
		void TakeOperand( TheOperand & );

		template< typename TheOperator >
		void TakeOperator( TheOperator & );

		template< typename TheQueue >
		void TakeQuotedQueue( TheQueue & );

		template< typename TheSeparator >
		void TakeSeparator( TheSeparator & );

	private: // MARK: private (non-static)

		Owner< Program > thisProgram;
	};
}

// MARK: - boost
namespace boost
{
	template<>
	void swap( Om::Operand &, Om::Operand & );
}

	#include "om/operand.cpp"
#endif
