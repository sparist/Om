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

\defgroup lexicon Lexicon
	\ingroup programs
	\brief
		A \ref programs "Program" optimized for fast mapping of \ref operator to
		\ref operand.
	\par Interpretation
		A \ref lexicon is an interpretation of a \ref programs "Program" as a
		sequence of \ref operator/\ref operand pairs with the following meaning:
		-	An \ref operand following an \ref operator indicates a mapping from
			the \ref operator to the \ref operand.
		-	An \ref operator without an \ref operand indicates that the
			\ref system_operation definition is to be used.
		-	An \ref operand without an \ref operator defines the mapping for the
			empty \ref operator.  When the \ref lexicon is used in an
			\ref environment_operation, this is treated as the
			"default mapping", applied when looking up an \ref operator that is
			not explicitly included in the \ref environment_operation.
		-	The last mapping wins; all others are disregarded.
	\par Normalization
		A \ref programs "Program" is normalized as a \ref lexicon as follows:
		-	Each \ref separator is removed, and replaced by a line
			\ref separator between each \ref operator/\ref operand pair.
		-	In the case of duplicate mappings for an \ref operator, earlier
			mappings are disregarded and removed from the normalized form.
	\par Implementation
		Om#Lexicon
*/
#if !defined( Om_Lexicon_ )
	#define Om_Lexicon_ Om::Lexicon

	#include "om/pair.hpp"
	#include "om/sources/default_source.hpp"
	#include "om/translator.hpp"

	#define Om_Lexicon_GetName_() "lexicon"

namespace Om
{
	//! \cond
	struct Evaluation;
	//! \endcond

	// MARK: - Om::Lexicon
	/*!
	\brief
		The \ref lexicon Program implementation.
	*/
	struct Lexicon
	:
	DefaultProgram< Lexicon >,
	Translator
	{
	public: // MARK: public (static)

		//! \cond
		struct ElementRange;
		//! \endcond

		static char const * GetName();

	public: // MARK: public (non-static)

		Lexicon();

		Lexicon( Lexicon const & );

		Lexicon & operator =( Lexicon );

		void BackGivePair( Queue & );

		virtual void Clear();

		/*!
		\return
			The Pair containing to the Operator, or empty if none.
		*/
		Pair const & Find( Operator const & ) const;

		void FrontGivePair( Queue & );

		virtual std::auto_ptr<
			Source< Element const >
		> GetElementRange() const;

		virtual void GiveElements( Queue & );

		virtual void GiveElements( Queue & ) const;

		virtual bool IsEmpty() const;

		virtual void ReadElements( Parser & );

		virtual void ReadQuotedElements( Parser & );

		void Swap( Lexicon & );

		template< typename TheOperand >
		void TakeOperand( TheOperand & );

		template< typename TheOperator >
		void TakeOperator( TheOperator & );

		template< typename TheQueue >
		void TakeQuotedQueue( TheQueue & );

		template< typename TheSeparator >
		void TakeSeparator( TheSeparator & );

		virtual bool Translate( Evaluation &, Operator const & ) const;

	private: // MARK: private (static)

		//! \cond
		struct Node;
		//! \endcond

		typedef boost::ptr_map< std::string, Node > Map;

		/*!
		\brief
			Gives each Element in the Lexicon.
		\param theFirstNode
			The first Node in the Lexicon, or null if none.
		\param theQueue
			The Queue to give them to.
		*/
		template< typename TheNode >
		static void GiveElements( TheNode * theFirstNode, Queue & theQueue );

	private: // MARK: private (non-static)

		/*!
		\return
			The first Node (whose mutability matches this), or null if none.
		*/
		Node * GetFirstNode();

		/*!
		\overload
		*/
		Node const * GetFirstNode() const;

		/*!
		\return
			The last Node (whose mutability matches this), or null if none.
		*/
		Node * GetLastNode();

		/*!
		\overload
		*/
		Node const * GetLastNode() const;

		/*!
		\brief
			Ensures that there is a last Node with an empty Operand, and with
			any Operator, and returns a reference to it.
		\return
			If there is no last Node, or it has an Operand, appends a new one
			with an empty Operator and returns a reference to it.  Otherwise,
			returns a reference to the last Node.
		*/
		Node & GetOperandTaker();

		/*!
		\brief
			Ensures that there is a last Node with an empty Operand, and the
			given Operator, and returns a reference to it.
		\return
			If there is already a Node for this Operator, relinks it to the back
			and returns a reference to it.  Otherwise, constructs a Node with
			the given Operator, appends it, and returns a reference to it.
		*/
		template< typename TheOperator >
		Node & GetOperandTaker( TheOperator & );

		Map thisMap;

		//! The first Node; null if empty.
		Node * thisFirstNode;

		//! The last Node; null if empty.
		Node * thisLastNode;
	};

	// MARK: - Om::Lexicon::ElementRange
	/*!
	\brief
		A Lexicon Element range.
	*/
	struct Lexicon::ElementRange
	:
	Sources::DefaultSource< Element const, ElementRange >
	{
	public: // MARK: public (non-static)

		ElementRange();

		explicit ElementRange( Lexicon const & );

		bool operator ==( ElementRange const & ) const;

		virtual bool operator !() const;

		virtual Element const & operator *() const;

		virtual void Pop();

	private: // MARK: private (non-static)

		//! The current Node, or null if none.
		Node const * thisNode;

		//! The Element offset in the current Node.
		char unsigned thisOffset;
	};

	// MARK: - Om::Lexicon::Node
	/*!
	\brief
		A Lexicon linked list node, extending Pair with next and prior pointers.
	*/
	struct Lexicon::Node
	:
	Pair
	{
	public: // MARK: public (static)

		/*!
		\param theFirstNode
			The first Node, or null if empty.
		\param theLastNode
			The last Node, or null if empty.
		*/
		static void UnlinkFirst( Node * & theFirstNode, Node * & theLastNode );

		/*!
		\param theFirstNode
			The first Node, or null if empty.
		\param theLastNode
			The last Node, or null if empty.
		*/
		static void UnlinkLast( Node * & theFirstNode, Node * & theLastNode );

	public: // MARK: public (non-static)

		Node();

		/*!
		\return
			The next Node, or null if none.
		*/
		Node * GetNext();

		/*!
		\overload
		*/
		Node const * GetNext() const;

		/*!
		\return
			The prior Node, or null if none.
		*/
		Node * GetPrior();

		/*!
		\overload
		*/
		Node const * GetPrior() const;

		/*!
		\brief
			Links this Node to the back.
		\param theFirstNode
			The first Node, or null if empty.
		\param theLastNode
			The last Node, or null if empty.
		*/
		void LinkToBack( Node * & theFirstNode, Node * & theLastNode );

		/*!
		\brief
			Unlinks this Node and links it to the back.
		\param theFirstNode
			The first Node, or null if empty.
		\param theLastNode
			The last Node, or null if empty.
		*/
		void RelinkToBack( Node * & theFirstNode, Node * & theLastNode );

	private: // MARK: private (non-static)

		//! The prior Node; null if first.
		Node * thisPriorNode;

		//! The next Node; null if last.
		Node * thisNextNode;
	};
}

// MARK: - boost
namespace boost
{
	template<>
	void swap( Om::Lexicon &, Om::Lexicon & );
}

	#include "om/lexicon.cpp"
#endif
