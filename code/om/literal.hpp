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
#if !defined( Om_Literal_ )
	#define Om_Literal_ Om::Literal

	#include "om/default_program.hpp"
	#include "om/sources/collection_front_source.hpp"

	#define Om_Literal_GetName_() "literal"

namespace Om
{
	// MARK: - Om::Literal
	/*!
	\brief
		The \ref literal Program implementation.
	*/
	struct Literal
	:
	DefaultProgram< Literal >
	{
	public: // MARK: public (static)

		//! \cond
		template< typename ThisLiteral >
		struct ElementRange;
		//! \endcond

		static char const * GetName();

	public: // MARK: public (non-static)

		virtual ~Literal();

		Literal();

		Literal & operator =( Literal );

		template< typename TheElement >
		void BackGive( Queue & );

		void BackGiveElement( Queue & );

		virtual void Clear();

		template< typename TheElement >
		void FrontGive( Queue & );

		void FrontGiveElement( Queue & );

		std::auto_ptr< Source< Element > > GetElementRange();

		virtual std::auto_ptr<
			Source< Element const >
		> GetElementRange() const;

		virtual void GiveElements( Queue & );

		virtual void GiveElements( Queue & ) const;

		virtual bool IsEmpty() const;

		virtual void ReadElements( Parser & );

		virtual void ReadQuotedElements( Parser & );

		void Swap( Literal & );

		template< typename TheOperand >
		void TakeOperand( TheOperand & );

		template< typename TheOperator >
		void TakeOperator( TheOperator & );

		template< typename TheQueue >
		void TakeQuotedQueue( TheQueue & );

		template< typename TheSeparator >
		void TakeSeparator( TheSeparator & );

	private: // MARK: private (static)

		typedef boost::ptr_deque< Element > ElementDeque;

		/*!
		\param theQueue
			The taker.
		\param theCurrent
			The current Element iterator.
		\param theEnd
			The end Element iterator.
		*/
		template< typename TheElementIterator >
		static void GiveElements(
			Queue & theQueue,
			TheElementIterator theCurrent,
			TheElementIterator const theEnd
		);

	private: // MARK: private (non-static)

		template< typename TheAtom >
		void TakeAtom( TheAtom & );

		ElementDeque thisElementDeque;
	};

	// MARK: - Om::Literal::ElementRange< Literal >
	/*!
	\brief
		A mutable Element range.
	*/
	template<>
	struct Literal::ElementRange< Literal >
	:
	Sources::CollectionFrontSource< Element, ElementDeque::iterator >
	{
	public: // MARK: public (non-static)

		explicit ElementRange( Literal & );
	};

	// MARK: - Om::Literal::ElementRange< Literal const >
	/*!
	\brief
		An immutable Element range.
	*/
	template<>
	struct Literal::ElementRange< Literal const >
	:
	Sources::CollectionFrontSource<
		Element const,
		ElementDeque::const_iterator
	>
	{
	public: // MARK: public (non-static)

		explicit ElementRange( Literal const & );
	};
}

// MARK: - boost
namespace boost
{
	template<>
	void swap( Om::Literal &, Om::Literal & );
}

	#include "om/literal.cpp"
#endif
