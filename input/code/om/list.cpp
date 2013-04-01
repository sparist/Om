/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_List_

	#include "om/list.hpp"

#else

// MARK: - Om::List

	#define Template_ \
	template <typename ThisValue>

	#define Type_ \
	Om::List<ThisValue>

// MARK: public (non-static)

Template_
inline Type_::List():
thisNodeArray() {
	this->Clear();
}

Template_
inline void Type_::Clear() {
	this->thisNodeArray[theFrontNodeIndex] = 0;
	this->thisNodeArray[theBackNodeIndex] = 0;
}

Template_
inline typename Type_::Node * Type_::GetNode(NodeIndex const theNodeIndex) {
	return this->thisNodeArray[theNodeIndex];
}

Template_
inline typename Type_::Node const * Type_::GetNode(NodeIndex const theNodeIndex) const {
	return this->thisNodeArray[theNodeIndex];
}

Template_
inline bool Type_::IsEmpty() const {
	assert(
		!this->thisNodeArray[theFrontNodeIndex] == !this->thisNodeArray[theBackNodeIndex]
	);
	return !this->thisNodeArray[theFrontNodeIndex];
}

Template_
inline void Type_::LinkNode(
	NodeIndex const theNodeIndex,
	Node & theNode
) {
	Node * const theLinkedNode = this->thisNodeArray[theNodeIndex];
	theNode.thisNodeArray[theNodeIndex] = 0;
	theNode.thisNodeArray[!theNodeIndex] = theLinkedNode;
	if (theLinkedNode) {
		theLinkedNode->thisNodeArray[theNodeIndex] = &theNode;
	} else {
		assert(
			!this->thisNodeArray[!theNodeIndex]
		);
		this->thisNodeArray[!theNodeIndex] = &theNode;
	}
	this->thisNodeArray[theNodeIndex] = &theNode;
}

Template_
inline void Type_::RelinkNode(
	NodeIndex const theNodeIndex,
	Node & theNode
) {
	if (
		Node * const theNearNode = theNode.thisNodeArray[theNodeIndex]
	) {
		Node * const theFarNode = theNode.thisNodeArray[!theNodeIndex];
		theNearNode->thisNodeArray[!theNodeIndex] = theFarNode;
		if (theFarNode) {
			theFarNode->thisNodeArray[theNodeIndex] = theNearNode;
		} else {
			assert(
				this->thisNodeArray[!theNodeIndex] == &theNode
			);
			this->thisNodeArray[!theNodeIndex] = theNearNode;
		}

		this->LinkNode(
			theNodeIndex,
			theNode
		);
	}
}

Template_
inline void Type_::Swap(List & theList) {
	boost::swap(
		this->thisNodeArray[theFrontNodeIndex],
		theList.thisNodeArray[theFrontNodeIndex]
	);
	boost::swap(
		this->thisNodeArray[theBackNodeIndex],
		theList.thisNodeArray[theBackNodeIndex]
	);
}

Template_
inline typename Type_::Node * Type_::UnlinkNode(NodeIndex const theNodeIndex) {
	if (
		Node * const theNode = this->thisNodeArray[theNodeIndex]
	) {
		assert(
			this->thisNodeArray[!theNodeIndex] &&
			!theNode->thisNodeArray[theNodeIndex]
		);

		Node * const theFarNode = theNode->thisNodeArray[!theNodeIndex];
		if (theFarNode) {
			theFarNode->thisNodeArray[theNodeIndex] = 0;
		} else {
			assert(
				this->thisNodeArray[!theNodeIndex] == theNode
			);
			this->thisNodeArray[!theNodeIndex] = 0;
		}
		this->thisNodeArray[theNodeIndex] = theFarNode;

		return theNode;
	}
	return 0;
}

	#undef Type_
	#undef Template_

// MARK: - Om::List::Node

	#define Template_ \
	template <typename ThisValue>

	#define Type_ \
	Om::List<ThisValue>::Node

// MARK: public (non-static)

Template_
inline Type_::Node():
thisNodeArray(),
thisValue() {
	this->thisNodeArray[theFrontNodeIndex] = 0;
	this->thisNodeArray[theBackNodeIndex] = 0;
}

Template_
inline typename Type_ * Type_::GetNode(NodeIndex const theNodeIndex) {
	return this->thisNodeArray[theNodeIndex];
}

Template_
inline typename Type_ const * Type_::GetNode(NodeIndex const theNodeIndex) const {
	return this->thisNodeArray[theNodeIndex];
}

Template_
inline ThisValue & Type_::GetValue() {
	return this->thisValue;
}

Template_
inline ThisValue const & Type_::GetValue() const {
	return this->thisValue;
}

	#undef Type_
	#undef Template_

#endif
