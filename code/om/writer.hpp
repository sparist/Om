/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Writer_

	#define Om_Writer_ \
	Om::Writer

	#include "om/code_point.hpp"
	#include "om/default_consumer.hpp"

namespace Om {

	//! \cond
	namespace Sink {

		template <typename ThisItem>
		class Sink;

	}
	//! \endcond

	// MARK: - Om::Writer

	/*!
	\brief
		A Consumer that pushes each Element to a #CodePoint Sink upon receipt.
	*/
	class Writer:
	public DefaultConsumer<Writer> {

	public: // MARK: public (non-static)

		explicit Writer(
			Sink::Sink<CodePoint const> &
		);

		virtual void ReadElements(Parser &);

		virtual void ReadQuotedElements(Parser &);

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
		Sink::Sink<CodePoint const> & thisCodePointSink;

	};

}

	#include "om/writer.cpp"

#endif
