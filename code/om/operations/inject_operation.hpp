/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup inject_operation inject
	\ingroup operations
	\brief
		Injects a \ref programs "Program" before each \ref operand of another.
	\par Input
		<tt>{injector}{program}</tt>
	\par Output
		Dequotes <tt>{program}</tt>, injects the dequoted <tt>{injector}</tt>
		between the \ref programs "Program" and each of its
		\ref operand "Operands", then \ref quote_operation "quotes" the result.
	\par Examples
		-	<tt>inject{quote}{copy}{A}</tt>
			<blockquote><tt>{{{A}}{{A}}}</tt></blockquote>
	\par Implementation
		Om#Operations#InjectOperation
*/
#if !defined( Om_Operations_InjectOperation_ )
	#define Om_Operations_InjectOperation_ Om::Operations::InjectOperation

	#include "om/default_evaluand.hpp"
	#include "om/definition.hpp"
	#include "om/expression.hpp"

	#define Om_Operations_InjectOperation_GetName_() "inject"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::InjectOperation
		/*!
		\brief
			The \ref inject_operation Operation implementation.
		*/
		struct InjectOperation
		:
		DefaultEvaluand< InjectOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheInjectOperation >
			static void GiveElements( TheInjectOperation &, Queue & );

		public: // MARK: public (non-static)

			InjectOperation();

			template< typename TheOperand >
			bool TakeOperand( Evaluator &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluator &, TheQueue & );

		private: // MARK: private (non-static)

			Expression thisInjector;

			//! The argument to be used as Output.
			Expression thisOutput;

			/*!
			\brief
				The local Evaluator.
			\note
				This will hold a reference to the Evaluator's Translator, which
				must remain alive.
			*/
			boost::optional< Evaluator > thisScope;
		};

		namespace
		{
			static Definition< InjectOperation > const theInjectDefinition;
		}
	}
}

	#include "om/operations/inject_operation.cpp"
#endif
