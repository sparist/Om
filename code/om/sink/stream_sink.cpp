/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Sink_StreamSink_

	#include "om/sink/stream_sink.hpp"

#else

// MARK: - Om::Sink::StreamSink

	#define Template_ \
	template <typename ThisItem>

	#define Type_ \
	Om::Sink::StreamSink<ThisItem>

// MARK: public (non-static)

Template_
inline Type_::StreamSink(std::ostream & theStream):
IteratorSink<
	ThisItem const,
	std::ostreambuf_iterator<ThisItem>
>(theStream) {}

	#undef Type_
	#undef Template_

#endif
