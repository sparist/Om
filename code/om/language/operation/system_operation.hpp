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

\defgroup om__operation__system_operation__ system
	\ingroup om__operation__
	\brief
		Produces the system \ref om__lexicon__.
	\par Details
		The system \ref om__lexicon__ contains each \ref om__operator__ defined by the system. Each \ref om__operator__ is without an \ref om__operand__ mapping to indicate that the native system operation is to be used.
	\par Implementation
		Om::Language::Operation::SystemOperation
*/

#ifndef Om_Language_Operation_SystemOperation_

	#define Om_Language_Operation_SystemOperation_ \
	Om::Language::Operation::SystemOperation

	#include "om/language/system.hpp"

	#define Om_Language_Operation_SystemOperation_GetName_() \
	"system"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::SystemOperation

			/*!
			\brief
				The \ref om__operation__system_operation__ operation implementation.
			*/
			class SystemOperation {

			public: // MARK: public (static)

				static char const * GetName();

				static void Give(Evaluation &);

			};

			namespace {

				static System::Definition<SystemOperation> const theSystemDefinition;

			}

		}

	}

}

	#include "om/language/operation/system_operation.cpp"

#endif
