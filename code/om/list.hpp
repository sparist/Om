/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_List_

	#define Om_List_ \
	Om::List

	#ifndef Om_Macro_Precompilation_

		#include "boost/array.hpp"

	#endif

namespace Om {

	// MARK: - Om::List

	/*!
	\brief
		A doubly-linked list in which nodes are unowned.
	*/
	template <typename ThisValue>
	class List {

	public: // MARK: public (static)

		enum NodeIndex {
			theFrontNodeIndex,
			theBackNodeIndex
		};

		class Node;

	public: // MARK: public (non-static)

		List();

		void Clear();

		/*!
		\brief
			Gets the first or last Node.
		*/
		Node * GetNode(NodeIndex const);

		/*!
		\brief
			\overload
		*/
		Node const * GetNode(NodeIndex const) const;

		bool IsEmpty() const;

		/*!
		\brief
			Links the Node to the specified end.
		*/
		void LinkNode(
			NodeIndex const,
			Node &
		);

		/*!
		\brief
			Relinks the Node to the specified end.
		*/
		void RelinkNode(
			NodeIndex const,
			Node &
		);

		void Swap(List &);

		/*!
		\brief
			Unlinks the Node at the specified end and returns it.
		*/
		Node * UnlinkNode(NodeIndex const);

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
	template <typename ThisValue>
	class List<ThisValue>::Node {

		friend class List<ThisValue>;

	public: // MARK: public (non-static)

		Node();

		/*!
		\brief
			Gets the prior or next Node.
		*/
		Node * GetNode(NodeIndex const);

		/*!
		\brief
			\overload
		*/
		Node const * GetNode(NodeIndex const) const;

		/*!
		\brief
			Gets a reference to the stored value.
		*/
		ThisValue & GetValue();

		/*!
		\brief
			\overload
		*/
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
