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

#ifndef Om_Language_Pair_

	#define Om_Language_Pair_ \
	Om::Language::Pair

	#include "om/language/operator.hpp"

namespace Om {

	namespace Language {

		// MARK: - Om::Language::Pair

		/*!
		\brief
			An Operator and an Operand.
		*/
		class Pair {

		public: // MARK: public (static)

			static Pair const & GetEmpty();

		public: // MARK: public (non-static)

			virtual ~Pair();

			Pair();

			void ClearOperand();

			Operand const & GetOperand() const;

			Operator const & GetOperator() const;

			void GiveElements(Consumer &);

			void GiveElements(Consumer &) const;

			bool IsEmpty() const;

			template <typename TheOperand>
			void TakeOperand(TheOperand &);

			/*!
			\brief
				Replaces the Operator.
			*/
			template <typename TheOperator>
			void TakeOperator(TheOperator &);

			template <typename TheProducer>
			void TakeQuotedProducer(TheProducer &);

		private: // MARK: private (static)

			template <typename ThePair>
			static void GiveElements(
				ThePair &,
				Consumer &
			);

		private: // MARK: private (non-static)

			Operator thisOperator;

			Operand thisOperand;

		};

	}

}

	#include "om/language/pair.cpp"

#endif
