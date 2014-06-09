/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb

\defgroup om__operand__ Operand
	\ingroup om__program__
	\brief
		A \ref om__program__ element that wraps a \ref om__program__.
	\par Interpretation
		A \ref om__program__ is interpreted as an \ref om__operand__ by treating only the first operand (a \ref om__program__ enclosed by braces) as significant.
	\par Normalization
		A \ref om__program__ is normalized as an \ref om__operand__ by discarding all elements other than the first operand element.
	\par Implementation
		Om::Operand
*/

#ifndef Om_Operand_

	#define Om_Operand_ \
	Om::Operand

	#include "om/default_element.hpp"
	#include "om/owner.hpp"

	#ifndef Om_Macro_Precompilation_

		#include "boost/swap.hpp"

	#endif

	#define Om_Operand_GetName_() \
	"operand"

namespace Om {

	// MARK: - Om::Operand

	/*!
	\brief
		The \ref om__operand__ implementation.

	A non-atomic Element that embeds another Program, which it owns.
	*/
	class Operand:
	public DefaultElement<Operand> {

	public: // MARK: public (static)

		static char const * GetName();

	public: // MARK: public (non-static)

		Operand();

		template <typename TheProgram>
		explicit Operand(
			std::auto_ptr<TheProgram>
		);

		Operand & operator =(Operand);

		/*!
		\return
			A reference to the Program owned by this Operand. Do not retain this reference.
		*/
		virtual Program & operator *();

		/*!
		\overload
		*/
		virtual Program const & operator *() const;

		virtual void Clear();

		using DefaultElement<Operand>::Equals;

		bool Equals(Operand const &) const;

		/*!
		\return
			A reference to the Program owned by this Operand, or null if none. Do not retain this reference.
		*/
		Program * GetProgram();

		/*!
		\overload
		*/
		Program const * GetProgram() const;

		/*!
		\return
			True if this instance represents an empty Program, which is the case if there is no inner Program (i.e. via default construction).
		*/
		virtual bool IsEmpty() const;

		virtual void ParseElements(Reader &);

		virtual void ParseQuotedElements(Reader &);

		/*!
		\brief
			Replaces the Program owned by this Operand with the argument.
		*/
		template <typename TheProgram>
		void SetProgram(
			std::auto_ptr<TheProgram>
		);

		void Swap(Operand &);

		virtual void TakeElements(Producer &);

		virtual void TakeElements(Producer const &);

		template <typename TheOperand>
		void TakeOperand(TheOperand &);

		template <typename TheOperator>
		void TakeOperator(TheOperator &);

		template <typename TheProducer>
		void TakeQuotedProducer(TheProducer &);

		template <typename TheSeparator>
		void TakeSeparator(TheSeparator &);

	private: // MARK: private (non-static)

		Owner<Program> thisProgram;

	};

	// MARK: - Om::

	bool operator ==(
		Operand const &,
		Operand const &
	);

	bool operator !=(
		Operand const &,
		Operand const &
	);

}

namespace boost {

	// MARK: - boost::

	template <>
	void swap(
		Om::Operand &,
		Om::Operand &
	);

}

	#include "om/operand.cpp"

#endif
