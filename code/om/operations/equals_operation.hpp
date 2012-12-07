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

\defgroup equals_operation =
	\ingroup operations
	\brief
		Compares two \ref programs for equality.
	\par Examples
		-	<tt>= {A} {A}</tt>
			<blockquote><tt>{{A}}</tt></blockquote>
		-	<tt>= {A} {B}</tt>
			<blockquote><tt>{}</tt></blockquote>
		-	<tt>= {} {A}</tt>
			<blockquote><tt>{}</tt></blockquote>
		-	<tt>= {} {}</tt>
			<blockquote><tt>{{}}</tt></blockquote>
	\par Implementation
		Om#Operations#EqualsOperation
*/
#if !defined( Om_Operations_EqualsOperation_ )
	#define Om_Operations_EqualsOperation_ Om::Operations::EqualsOperation

	#include "om/default_evaluation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_EqualsOperation_GetName_() "="

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::EqualsOperation
		/*!
		\brief
			The \ref equals_operation Operation implementation.
		*/
		struct EqualsOperation
		:
		DefaultEvaluation< EqualsOperation >
		{
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheEqualsOperation >
			static void GiveElements( TheEqualsOperation &, Queue & );

		public: // MARK: public (non-static)

			EqualsOperation();

			template< typename TheOperand >
			bool TakeOperand( Evaluator &, TheOperand & );

			template< typename TheQueue >
			bool TakeQuotedQueue( Evaluator &, TheQueue & );

		private: // MARK: private (non-static)

			//! The Operand to compare with.
			boost::optional< Operand > thisOperand;
		};

		namespace
		{
			static Definition< EqualsOperation > const theEqualsDefinition;
		}
	}
}

	#include "om/operations/equals_operation.cpp"
#endif
