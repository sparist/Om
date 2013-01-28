/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_SubstituteOperation_ )

	#define Om_Operations_SubstituteOperation_ \
	Om::Operations::SubstituteOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"
	#include "om/operations/translate_operation.hpp"

	#define Om_Operations_SubstituteOperation_GetName_() \
	"substitute"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::SubstituteOperation
		/*!
		\brief
			The \ref substitute_operation Operation implementation.
		*/
		struct SubstituteOperation:
		TranslateOperation< SubstituteOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

		public: // MARK: public (non-static)

			template< typename TheQueue >
			void Translate(
				Translator const &,
				TheQueue &,
				Expression &
			) const;
		};

		namespace
		{
			static Definition< SubstituteOperation > const theSubstituteDefinition;
		}
	}
}

	#include "om/operations/substitute_operation.cpp"

#endif
