/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
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
*/
#if !defined( Om_DefaultElement_ )
	#define Om_DefaultElement_ Om::DefaultElement

	#include "om/default_program.hpp"

namespace Om
{
	// MARK: - Om::DefaultElement
	template< typename ThisImplementation, typename ThisInterface = Element >
	struct DefaultElement
	:
	DefaultProgram< ThisImplementation, ThisInterface >
	{
	public: // MARK: public (non-static)

		virtual ~DefaultElement() = 0;

		virtual bool operator ==( Element const & ) const;

		virtual std::auto_ptr< Source< Element > > GetElementRange();

		virtual std::auto_ptr<
			Source< Element const >
		> GetElementRange() const;

		virtual void GiveElements( Queue & );

		virtual void GiveElements( Queue & ) const;

	private: // MARK: private (non-static)

		Element & operator =( Element const & );
	};
}

	#include "om/default_element.cpp"
#endif
