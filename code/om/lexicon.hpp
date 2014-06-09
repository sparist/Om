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

\defgroup om__lexicon__ Lexicon
	\ingroup om__program__
	\brief
		A \ref om__program__ optimized for fast mapping of \ref om__operator__ to \ref om__operand__.
	\par Interpretation
		A \ref om__program__ is interpreted as a \ref om__lexicon__ by treating it as a sequence of \ref om__operator__/\ref om__operand__ pairs that map \ref om__operator__ "Operators" to \ref om__operand__ "Operands" as follows:
		-	An \ref om__operand__ following an \ref om__operator__ indicates a mapping from the \ref om__operator__ to the \ref om__operand__.
		-	An \ref om__operator__ without an \ref om__operand__ indicates that the \ref om__operation__system_operation__ definition is to be used.
		-	An \ref om__operand__ without an \ref om__operator__ defines the mapping for the empty \ref om__operator__. When the \ref om__lexicon__ is used in an \ref om__operation__environment_operation__, this is treated as the default mapping, applied when looking up an \ref om__operator__ that is not explicitly included in the \ref om__operation__environment_operation__.
		-	The last mapping wins; all others are insignificant.
	\par Normalization
		A \ref om__program__ is normalized as a \ref om__lexicon__ as follows:
		-	Each \ref om__separator__ is removed, and a line \ref om__separator__ is inserted between each \ref om__operator__/\ref om__operand__ pair.
		-	In the case of duplicate mappings for an \ref om__operator__, earlier mappings are disregarded and removed from the normalized form.
	\par Implementation
		Om::Lexicon
*/

#ifndef Om_Lexicon_

	#define Om_Lexicon_ \
	Om::Lexicon

	#include "om/list.hpp"
	#include "om/pair.hpp"
	#include "om/source/default_source.hpp"
	#include "om/translator.hpp"

	#ifndef Om_Macro_Precompilation_

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

		class ElementRange;

		static char const * GetName();

	public: // MARK: public (non-static)

		Lexicon();

		Lexicon(Lexicon const &);

		Lexicon & operator =(Lexicon);

		void BackGivePair(Consumer &);

		virtual void Clear();

		/*!
		\return
			The Pair containing to the Operator, or empty if none.
		*/
		Pair const & Find(Operator const &) const;

		void FrontGivePair(Consumer &);

		virtual std::auto_ptr<
			Source::Source<Element const>
		> GetElementRange() const;

		virtual void GiveElements(Consumer &);

		virtual void GiveElements(Consumer &) const;

		virtual bool IsEmpty() const;

		virtual void ParseElements(Reader &);

		virtual void ParseQuotedElements(Reader &);

		void Swap(Lexicon &);

		template <typename TheOperand>
		void TakeOperand(TheOperand &);

		template <typename TheOperator>
		void TakeOperator(TheOperator &);

		template <typename TheProducer>
		void TakeQuotedProducer(TheProducer &);

		template <typename TheSeparator>
		void TakeSeparator(TheSeparator &);

		virtual bool Translate(
			Evaluation &,
			Operator const &
		) const;

	private: // MARK: private (static)

		typedef List<Pair> PairList;

		typedef boost::ptr_map<
			std::string,
			PairList::Node
		> Map;

		/*!
		\brief
			Gives each Element in the Lexicon.
		\param theFirstNode
			The first Node in the Lexicon, or null if none.
		\param theConsumer
			The Consumer to give them to.
		*/
		template <typename TheNode>
		static void GiveElements(
			TheNode * theFirstNode,
			Consumer & theConsumer
		);

	private: // MARK: private (non-static)

		/*!
		\brief
			Ensures that there is a last Node with an empty Operand, and with any Operator, and returns a reference to it.
		\return
			If there is no last Node, or it has an Operand, appends a new one with an empty Operator and returns a reference to it. Otherwise, returns a reference to the last Node.
		*/
		PairList::Node & GetOperandTaker();

		/*!
		\brief
			Ensures that there is a last Node with an empty Operand, and the given Operator, and returns a reference to it.
		\return
			If there is already a Node for this Operator, relinks it to the back and returns a reference to it. Otherwise, constructs a Node with the given Operator, appends it, and returns a reference to it.
		*/
		template <typename TheOperator>
		PairList::Node & GetOperandTaker(TheOperator &);

		void GivePair(
			PairList::NodeIndex const,
			Consumer &
		);

		Map thisMap;

		PairList thisPairList;

	};

	// MARK: - Om::Lexicon::ElementRange

	/*!
	\brief
		A Lexicon Element range.
	*/
	class Lexicon::ElementRange:
	public Source::DefaultSource<
		Element const,
		ElementRange
	> {

	public: // MARK: public (non-static)

		ElementRange();

		explicit ElementRange(Lexicon const &);

		virtual bool operator !() const;

		virtual Element const & operator *() const;

		using Om::Source::DefaultSource<
			Element const,
			ElementRange
		>::Equals;

		bool Equals(ElementRange const &) const;

		virtual void Pop();

	private: // MARK: private (non-static)

		/*!
		\brief
			The current Node, or null if none.
		*/
		PairList::Node const * thisNode;

		/*!
		\brief
			The Element offset in the current Node.
		*/
		char thisOffset;

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
