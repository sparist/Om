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

#ifndef Om_Operations_ProgramOperation_

	#define Om_Operations_ProgramOperation_ \
	Om::Operations::ProgramOperation

	#include "om/default_operation.hpp"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::ProgramOperation

		/*!
		\brief
			An Operation that normalizes a Program to a specific type.
		*/
		template <typename ThisProgram>
		class ProgramOperation:
		public DefaultOperation<
			ProgramOperation<ThisProgram>
		> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheProgramOperation>
			static void GiveElements(
				TheProgramOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

			virtual bool ReadQuotedElements(
				Evaluation &,
				Parser &
			);

			template <typename TheOperand>
			bool TakeOperand(
				Evaluation &,
				TheOperand &
			);

			template <typename TheProducer>
			bool TakeQuotedProducer(
				Evaluation &,
				TheProducer &
			);

		};

	}

}

	#include "om/operations/program_operation.cpp"

#endif
