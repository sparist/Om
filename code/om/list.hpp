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

#if !defined( Om_List_ )

	#define Om_List_ \
	Om::List

namespace Om {

	// MARK: - Om::List
	/*!
	\brief
		A doubly-linked list; contents are unowned.
	*/
	template< typename ThisValue >
	class List {
	public: // MARK: public (static)

		enum NodeIndex {
			theFrontNodeIndex,
			theBackNodeIndex
		};

		//! \cond
		class Node;
		//! \endcond

	public: // MARK: public (non-static)

		List();

		void Clear();

		Node * GetNode( NodeIndex const );

		Node const * GetNode( NodeIndex const ) const;

		bool IsEmpty() const;

		void LinkNode(
			NodeIndex const,
			Node &
		);

		void RelinkNode(
			NodeIndex const,
			Node &
		);

		void Swap( List & );

		Node * UnlinkNode( NodeIndex const );

	private: // MARK: private (static)

		typedef boost::array<
			Node *,
			2
		> NodeArray;

	private: // MARK: private (non-static)

		/*!
		\brief
			The first and last Node; both are null if the list is empty.
		*/
		NodeArray thisNodeArray;

	};

	// MARK: - Om::List::Node
	/*!
	\brief
		A List node.
	*/
	template< typename ThisValue >
	class List< ThisValue >::Node {

		friend class List< ThisValue >;

	public: // MARK: public (non-static)

		Node();

		Node * GetNode( NodeIndex const );

		Node const * GetNode( NodeIndex const ) const;

		ThisValue & GetValue();

		ThisValue const & GetValue() const;

	private: // MARK: private (non-static)

		/*!
		\brief
			The prior and next Node; cannot both be null.
		*/
		NodeArray thisNodeArray;

		ThisValue thisValue;

	};

}

	#include "om/list.cpp"

#endif
