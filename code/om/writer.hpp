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

#ifndef Om_Writer_

	#define Om_Writer_ \
	Om::Writer

	#include "om/code_point.hpp"
	#include "om/default_queue.hpp"

namespace Om {

	//! \cond
	template <typename ThisItem>
	class Sink;
	//! \endcond

	// MARK: - Om::Writer
	/*!
	\brief
		A Queue that pushes each Element to a #CodePoint Sink upon receipt.

	Giving an Element does nothing.
	*/
	class Writer:
	public DefaultQueue<Writer> {
	public: // MARK: public (non-static)

		explicit Writer(
			Sink<CodePoint const> &
		);

		virtual bool operator ==(Program const &) const;

		virtual void Clear();

		virtual void GiveElements(Queue &);

		virtual void GiveElements(Queue &) const;

		virtual std::auto_ptr<Program> GiveProgram();

		virtual std::auto_ptr<Program> GiveProgram() const;

		virtual bool IsEmpty() const;

		virtual void ReadElements(Parser &);

		virtual void ReadQuotedElements(Parser &);

		template <typename TheOperand>
		void TakeOperand(TheOperand &);

		template <typename TheOperator>
		void TakeOperator(TheOperator &);

		template <typename TheQueue>
		void TakeQuotedQueue(TheQueue &);

		template <typename TheSeparator>
		void TakeSeparator(TheSeparator &);

	private: // MARK: private (non-static)

		Writer(Writer const &);

		Writer const & operator =(Writer const &);

		/*!
		\brief
			The output #CodePoint Sink.
		*/
		Sink<CodePoint const> & thisCodePointSink;

	};

}

	#include "om/writer.cpp"

#endif
