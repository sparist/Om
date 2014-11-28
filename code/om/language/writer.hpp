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
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Language_Writer_

	#define Om_Language_Writer_ \
	Om::Language::Writer

	#include "om/code_point.hpp"
	#include "om/language/default_consumer.hpp"

namespace Om {

	//! \cond
	namespace Sink {

		template <typename ThisItem>
		class Sink;

	}
	//! \endcond

	namespace Language {

		// MARK: - Om::Language::Writer

		/*!
		\brief
			A Consumer that pushes each Element to a #CodePoint Sink upon receipt.
		\todo
			Restore default ThisInterface argument when <a href="https://bugzilla.gnome.org/show_bug.cgi?id=739863">Doxygen bug 739863</a> is fixed.
		*/
		class Writer:
		public DefaultConsumer<
			Writer,
			Consumer
		> {

		public: // MARK: public (non-static)

			explicit Writer(
				Om::Sink::Sink<CodePoint const> &
			);

			virtual void ParseElements(Reader &);

			virtual void ParseQuotedElements(Reader &);

			template <typename TheOperand>
			void TakeOperand(TheOperand &);

			template <typename TheOperator>
			void TakeOperator(TheOperator &);

			template <typename TheProducer>
			void TakeQuotedProducer(TheProducer &);

			template <typename TheSeparator>
			void TakeSeparator(TheSeparator &);

		private: // MARK: private (non-static)

			Writer(Writer const &);

			Writer const & operator =(Writer const &);

			/*!
			\brief
				The output #CodePoint Sink.
			*/
			Om::Sink::Sink<CodePoint const> & thisCodePointSink;

		};

	}

}

	#include "om/language/writer.cpp"

#endif
