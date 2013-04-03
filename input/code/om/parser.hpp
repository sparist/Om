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

#ifndef Om_Parser_

	#define Om_Parser_ \
	Om::Parser

	#include "om/code_point.hpp"
	#include "om/sources/default_source.hpp"

namespace Om {

	//! \cond
	class Consumer;
	//! \endcond

	// MARK: - Om::Parser

	/*!
	\brief
		Produces each #CodePoint until the end of the Source.
	*/
	class Parser:
	public Sources::DefaultSource<
		CodePoint const,
		Parser
	> {

	public: // MARK: public (non-static)

		explicit Parser(
			Source<CodePoint const> &
		);

		virtual CodePoint const & operator *() const;

		virtual bool operator !() const;

		using Sources::DefaultSource<
			CodePoint const,
			Parser
		>::Equals;

		bool Equals(Parser const &) const;

		template<
			typename TheOperator,
			typename TheSeparator
		>
		void Parse(Consumer &);

		virtual void Pop();

	private: // MARK: private (non-static)

		Parser(Parser const &);

		Parser const & operator =(Parser const &);

		Source<CodePoint const> & thisCodePointSource;

		size_t thisDepth;

		bool thisIsEncoded;

	};

	// MARK: - Om::

	bool operator ==(
		Parser const &,
		Parser const &
	);

	bool operator !=(
		Parser const &,
		Parser const &
	);

}

	#include "om/parser.cpp"

#endif
