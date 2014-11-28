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

#ifndef Om_Language_Reader_

	#define Om_Language_Reader_ \
	Om::Language::Reader

	#include "om/code_point.hpp"
	#include "om/source/default_source.hpp"

namespace Om {

	namespace Language {

		// MARK: - Om::Language::Reader

		/*!
		\brief
			Produces each #CodePoint until the end of the Source.
		*/
		class Reader:
		public Om::Source::DefaultSource<
			CodePoint const,
			Reader
		> {

		public: // MARK: public (non-static)

			explicit Reader(
				Om::Source::Source<CodePoint const> &
			);

			virtual CodePoint const & operator *() const;

			virtual bool operator !() const;

			using Om::Source::DefaultSource<
				CodePoint const,
				Reader
			>::Equals;

			bool Equals(Reader const &) const;

			virtual void Pop();

		private: // MARK: private (non-static)

			Reader(Reader const &);

			Reader const & operator =(Reader const &);

			Om::Source::Source<CodePoint const> & thisCodePointSource;

			size_t thisDepth;

			bool thisIsEncoded;

		};

		// MARK: - Om::Language::

		bool operator ==(
			Reader const &,
			Reader const &
		);

		bool operator !=(
			Reader const &,
			Reader const &
		);

	}

}

	#include "om/language/reader.cpp"

#endif
