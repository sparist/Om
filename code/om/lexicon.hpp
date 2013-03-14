/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Lexicon_

	#define Om_Lexicon_ \
	Om::Lexicon

	#include "om/list.hpp"
	#include "om/pair.hpp"
	#include "om/sources/default_source.hpp"
	#include "om/translator.hpp"

	#ifndef Om_Macros_Precompilation_

		#include "boost/ptr_container/ptr_map.hpp"

	#endif

	#define Om_Lexicon_GetName_() \
	"lexicon"

namespace Om {

	//! \cond
	class Evaluation;
	//! \endcond

	// MARK: - Om::Lexicon

	/*!
	\brief
		The \ref om__lexicon__ Program implementation.
	*/
	class Lexicon:
	public DefaultProgram<Lexicon>,
	public Translator {

	public: // MARK: public (static)

		//! \cond
		class ElementRange;
		//! \endcond

		static char const * GetName();

	public: // MARK: public (non-static)

		Lexicon();

		Lexicon(Lexicon const &);

		Lexicon & operator =(Lexicon);

		void BackGivePair(Queue &);

		virtual void Clear();

		/*!
		\return
			The Pair containing to the Operator, or empty if none.
		*/
		Pair const & Find(Operator const &) const;

		void FrontGivePair(Queue &);

		virtual std::auto_ptr<
			Source<Element const>
		> GetElementRange() const;

		virtual void GiveElements(Queue &);

		virtual void GiveElements(Queue &) const;

		virtual bool IsEmpty() const;

		virtual void ReadElements(Parser &);

		virtual void ReadQuotedElements(Parser &);

		void Swap(Lexicon &);

		template <typename TheOperand>
		void TakeOperand(TheOperand &);

		template <typename TheOperator>
		void TakeOperator(TheOperator &);

		template <typename TheQueue>
		void TakeQuotedQueue(TheQueue &);

		template <typename TheSeparator>
		void TakeSeparator(TheSeparator &);

		virtual bool Translate(
			Evaluation &,
			Operator const &
		) const;

	private: // MARK: private (static)

		typedef List<Pair> List;

		typedef boost::ptr_map<
			std::string,
			List::Node
		> Map;

		/*!
		\brief
			Gives each Element in the Lexicon.
		\param theFirstNode
			The first Node in the Lexicon, or null if none.
		\param theQueue
			The Queue to give them to.
		*/
		template <typename TheNode>
		static void GiveElements(
			TheNode * theFirstNode,
			Queue & theQueue
		);

	private: // MARK: private (non-static)

		/*!
		\brief
			Ensures that there is a last Node with an empty Operand, and with any Operator, and returns a reference to it.
		\return
			If there is no last Node, or it has an Operand, appends a new one with an empty Operator and returns a reference to it. Otherwise, returns a reference to the last Node.
		*/
		List::Node & GetOperandTaker();

		/*!
		\brief
			Ensures that there is a last Node with an empty Operand, and the given Operator, and returns a reference to it.
		\return
			If there is already a Node for this Operator, relinks it to the back and returns a reference to it. Otherwise, constructs a Node with the given Operator, appends it, and returns a reference to it.
		*/
		template <typename TheOperator>
		List::Node & GetOperandTaker(TheOperator &);

		void GivePair(
			List::NodeIndex const,
			Queue &
		);

		Map thisMap;

		List thisList;

	};

	// MARK: - Om::Lexicon::ElementRange

	/*!
	\brief
		A Lexicon Element range.
	*/
	class Lexicon::ElementRange:
	public Sources::DefaultSource<
		Element const,
		ElementRange
	> {

		friend bool operator ==(
			ElementRange const &,
			ElementRange const &
		);

	public: // MARK: public (non-static)

		ElementRange();

		explicit ElementRange(Lexicon const &);

		virtual bool operator !() const;

		virtual Element const & operator *() const;

		virtual void Pop();

	private: // MARK: private (non-static)

		/*!
		\brief
			The current Node, or null if none.
		*/
		List::Node const * thisNode;

		/*!
		\brief
			The Element offset in the current Node.
		*/
		char unsigned thisOffset;

	};

	// MARK: - Om::

	bool operator ==(
		Lexicon::ElementRange const &,
		Lexicon::ElementRange const &
	);

	bool operator !=(
		Lexicon::ElementRange const &,
		Lexicon::ElementRange const &
	);

}

namespace boost {

	// MARK: - boost::

	template <>
	void swap(
		Om::Lexicon &,
		Om::Lexicon &
	);

}

	#include "om/lexicon.cpp"

#endif
