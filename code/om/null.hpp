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
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if !defined( Om_Null_ )
	#define Om_Null_ Om::Null

	#include "om/default_program.hpp"

	#define Om_Null_GetName_() "null"

namespace Om
{
	// MARK: - Om::Null
	/*!
	\brief
		The \ref null Program implementation.
	*/
	struct Null
	:
	DefaultProgram< Null >
	{
	public: // MARK: public (static)

		/*!
		\return
			The static Null.
			This can be a mutable reference because Null is immutable
			regardless.
		*/
		static Null & Get();

		static char const * GetName();

	public: // MARK: public (non-static)

		Null & operator =( Null const & );

		virtual bool operator ==( Program const & ) const;

		virtual void Clear();

		virtual std::auto_ptr< Source< Element > > GetElementRange();

		virtual std::auto_ptr<
			Source< Element const >
		> GetElementRange() const;

		virtual void GiveElements( Queue & );

		virtual void GiveElements( Queue & ) const;

		virtual bool IsEmpty() const;

		virtual void ReadElements( Parser & );

		virtual void ReadQuotedElements( Parser & );

		virtual void Swap( Null & );

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
	};
}

// MARK: - boost
namespace boost
{
	template<>
	void swap( Om::Null &, Om::Null & );
}

	#include "om/null.cpp"
#endif
