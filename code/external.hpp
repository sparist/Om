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
*/

#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include "boost/checked_delete.hpp"
#include "boost/integer_traits.hpp"
#include "boost/intrusive_ptr.hpp"
#include "boost/locale/boundary.hpp"
#include "boost/locale/conversion.hpp"
#include "boost/locale/encoding.hpp"
#include "boost/locale/generator.hpp"
#include "boost/locale/utf.hpp"
#include "boost/optional.hpp"
#include "boost/ptr_container/ptr_deque.hpp"
#include "boost/ptr_container/ptr_map.hpp"
#include "boost/ptr_container/ptr_vector.hpp"
#include "boost/ref.hpp"
#include "boost/scoped_ptr.hpp"
#include "boost/swap.hpp"
