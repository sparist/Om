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

#ifndef Om_DefaultProgram_

	#define Om_DefaultProgram_ \
	Om::DefaultProgram

	#include "om/default_consumer.hpp"
	#include "om/default_giveable.hpp"
	#include "om/program.hpp"
	#include "om/taker.hpp"

namespace Om {

	// MARK: - Om::DefaultProgram

	/*!
	\brief
		A partial implementation of Program.
	*/
	template <
		typename ThisImplementation,
		typename ThisInterface = Program
	>
	class DefaultProgram:
	public DefaultConsumer<
		ThisImplementation,
		DefaultGiveable<
			ThisImplementation,
			ThisInterface
		>
	>,
	public Taker<ThisImplementation> {

	public: // MARK: public (non-static)

		virtual ~DefaultProgram() = 0;

		using DefaultConsumer<
			ThisImplementation,
			DefaultGiveable<
				ThisImplementation,
				ThisInterface
			>
		>::Equals;

		virtual bool Equals(Program const &) const;

		virtual void TakeElements(Producer &);

		virtual void TakeElements(Producer const &);

	private: // MARK: private (non-static)

		DefaultProgram & operator =(DefaultProgram const &);

		template <
			typename TheCast,
			typename TheProducer
		>
		void TakeProducer(TheProducer &);

	};

}

	#include "om/default_program.cpp"

#endif
