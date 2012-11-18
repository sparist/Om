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

\defgroup program Program
	\brief
		A list of 0 or more \ref element "Elements" that represents a data
		value.
	\par Implementation
		Om#Program
*/
#if !defined( Om_Program_ )
	#define Om_Program_ Om::Program

	#include "om/giveable.hpp"
	#include "om/queue.hpp"
	#include "om/shareable.hpp"

namespace Om
{
	//! \cond
	struct Element;

	template< typename ThisItem >
	struct Source;
	//! \endcond

	// MARK: - Om::Program
	/*!
	\brief
		The \ref program implementation.

	A Program is a Giveable, Shareable Queue whose entire state is represented
	by an Element collection.

	Each concrete derivation must have a GetName() function that returns a null-
	terminated, NFD-normalized UTF-8 string to be used as a corresponding
	Operator name.
	*/
	struct Program
	:
	Giveable,
	Queue,
	Shareable<>
	{
	public: // MARK: public (non-static)

		virtual ~Program() = 0;

		/*!
		\return
			A non-null owner pointer to a new Element range.
		*/
		virtual std::auto_ptr<
			Source< Element const >
		> GetElementRange() const = 0;

		virtual std::auto_ptr< Program > GiveProgram();

		virtual std::auto_ptr< Program > GiveProgram() const;

	private: // MARK: private (non-static)

		Program & operator =( Program const & );
	};
}

	#include "om/program.cpp"
#endif
