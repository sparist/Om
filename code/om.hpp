/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.1
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\mainpage Main Page

\tableofcontents

\section introduction Introduction

The development of the <a href="http://om-language.org">Om</a> language was
guided by a single question:

<em>Starting from scratch, what is the simplest abstract syntax that can
articulate any algorithm for efficient and precise evaluation?</em>

The result is a fundamentally unique programming language.

<a href="http://om-language.org">Om</a> is:

-	<b>A concatenative programming language</b> with arguably the simplest
	syntax and type system possible in a usable language.
-	<b>An abstract algorithmic notation language</b> that does not expose any
	computer implementation details (such as byte or machine word length).
-	<b>A data transfer format</b> that is trivial to parse.
-	<b>Embeddable</b>: implemented as a header-only C++ library that can be
	incorporated into any C++ or Objective-C++ program.
-	<b>Extensible</b>: new native operations can be implemented as C++ classes.
-	<b>Unicode-correct</b>: any
	<a href="http://www.utf8everywhere.org">UTF-8</a> text (without byte-order
	marker) defines a valid <a href="http://om-language.org">Om</a> program.

<a href="http://om-language.org">Om</a> is <b>not</b>:

-	<b>Complete</b>.  Although the intent is to develop
	<a href="http://om-language.org">Om</a> into a full-featured language, the
	software is currently at a very early "proof of concept" stage, requiring
	the addition of many operations (such as basic number and file operations)
	and optimizations before it can be considered useful for any real-world
	purpose.  It has been made available in order to demonstrate the underlying
	concepts and welcome others to get involved in early development.
-	<b>Stationary</b>.  <a href="http://om-language.org">Om</a> will likely
	undergo significant changes on its way to version 1.0.

\section syntax Syntax

An <a href="http://om-language.org">Om</a> <b>program</b> is comprised of only
three syntactic elements, as follows:

\image html "program.png"

An <b>operator</b> has the following syntax:

\image html "operator.png"

A <b>separator</b> has the following syntax:

\image html "separator.png"

An <b>operand</b> has the following syntax:

\image html "operand.png"

\section how_it_works How It Works

\subsection how_it_works__operations Operations

An operation is a function, defined by a program, that takes the program itself
as input and generates a program as output.
<a href="http://om-language.org">Om</a> is a
<a href="http://concatenative.org">concatenative</a> language: the operation
defined by an <a href="http://om-language.org">Om</a> program is a composition
of operations defined by each sub-program.

Program elements each correspond to the following operations:

-	Separator:
	-	<b>Input:</b> The program, with the separator at the front.
	-	<b>Output:</b> The program, with the front separator normalized
		(top-level white space is insignificant).
-	Operand:
	-	<b>Input:</b> The program, with the operand at the front.
	-	<b>Output:</b> The program unchanged.
-	Operator:
	-	<b>Input:</b> The program, with the operator at the front.
	-	<b>Output:</b> The operation mapped to the operator by the evaluator,
		which is given the program as input.

Because programs are homomorphic with the operations they represent, the
application of operation A to a program B can be treated equivalently to the
composition of operation A with the operation represented by program B.

All of the native operations included in the current release are documented in
the \ref operations module.

\subsection how_it_works__evaluation Evaluation

Evaluation occurs from right to left and is performed recursively.

Backquotes (<tt>`</tt>) in operators are disregarded if the code point following
is not a backquote, operand brace, or separator code point.

The evaluator consists of:

-	<b>An environment</b> for resolving operators to operations.  If an operator
	is not mapped to anything in the environment, the operator resolves to an
	"identity" operation that leaves the program, including the operator,
	unchanged.
-	<b>An operation queue</b> for storing operations that are awaiting nested
	operations to be evaluated (in the event that the latter produces operands
	that can be consumed by the former).

The evaluator reads, parses and evaluates the input stream in a single pass,
sending results to the output stream as soon as they can be evaluated.  This is
possible because <a href="http://om-language.org">Om</a> uses prefix notation
rather than the postfix notation typical of concatenative languages.  Prefix
notation has the following benefits over postfix notation:

-	Stack underflows are impossible.
-	Operations can be optimized to only read into memory the data that is
	required; stack-based postfix languages have no knowledge of the operation
	to apply until the data is already in memory, on the stack.
-	An IDE can provide hints to the user about the data that is expected by
	an operation.

\subsection how_it_works__data_types Data Types

<a href="http://om-language.org">Om</a> uses a novel <em>panmorphic</em> type
system in which all data values are represented within the language solely
through a common program interface (comprised of only separators, operators,
and/or operands).  Any operation will accept any operand as a valid input and
interpret it however the operation deems appropriate.

There are no traditional data types in the language; data types are relegated to
an implementation layer and represent optimizations for a set of operations.
Each operand in memory contains a single program implementation; by default,
this is the \ref literal program, which preserves all data in the operand,
verbatim.  However, an operation may prefer an operand to have a different
program implementation that is optimized for specific functionality used by the
operation.  The \ref find_operation operation, for example, prefers one of its
operands to have a \ref lexicon program type for fast mapping from operator to
operand.  In such cases, an operation can simply convert an undesired program
implementation to the desired type through the common program interface without
impacting the semantics of the program.

Operations in a program can be ordered by the programmer to increase performance
by minimizing conversions between program implementations, but it is not
necessary for obtaining a correct computation.  Data types in
<a href="http://om-language.org">Om</a> therefore become an optimization-phase
implementation detail.

All of the native data types included in the current release are documented in
the \ref programs module.

\section examples Examples

The following program contains a single operand:

-	<tt>{Hello, world!}</tt>
	<blockquote><tt>{Hello, world!}</tt></blockquote>

Operands can be dropped and copied via the \ref drop_operation and
\ref copy_operation operations:

-	<tt>drop {A}{B}{C}</tt>
	<blockquote><tt>{B}{C}</tt></blockquote>
-	<tt>copy {A}{B}{C}</tt>
	<blockquote><tt>{A}{A}{B}{C}</tt></blockquote>
-	<tt>drop copy {A}</tt>
	<blockquote><tt>{A}</tt></blockquote>
-	<tt>copy copy {A}</tt>
	<blockquote><tt>{A}{A}{A}</tt></blockquote>

The \ref drop_operation operation can therefore be used for comments:

-	<tt>drop {This is a comment.} ...</tt>
	<blockquote><tt>...</tt></blockquote>

The \ref choose_operation operation selects one of two operands, depending on
whether a third is empty:

-	<tt>choose {It was empty.}{It was non-empty.}{I am not empty.}</tt>
	<blockquote><tt>{It was non-empty.}</tt></blockquote>
-	<tt>choose {It was empty.}{It was non-empty.}{}</tt>
	<blockquote><tt>{It was empty.}</tt></blockquote>

An operation without sufficient operands becomes the identity operation:

-	<tt>drop</tt>
	<blockquote><tt>drop</tt></blockquote>
-	<tt>choose {It was empty.}{It was non-empty.}</tt>
	<blockquote><tt>choose {It was empty.}{It was non-empty.}</tt></blockquote>

The \ref quote_operation and \ref dequote_operation operations add and remove a
layer of operand braces, respectively:

-	<tt>quote {B}</tt>
	<blockquote><tt>{{B}}</tt></blockquote>
-	<tt>dequote {{B}}</tt>
	<blockquote><tt>{B}</tt></blockquote>
-	<tt>dequote {copy}</tt>
	<blockquote><tt>copy</tt></blockquote>
-	<tt>dequote {copy} {A}</tt>
	<blockquote><tt>{A}{A}</tt></blockquote>

Operands can be popped from and pushed to:

-	<tt>&lt;-characters {ABC}</tt>
	<blockquote><tt>{A}{BC}</tt></blockquote>
-	<tt>-&gt;literal {A}{BC}</tt>
	<blockquote><tt>{ABC}</tt></blockquote>
-	<tt>&lt;-terms {some terms}</tt>
	<blockquote><tt>{some}{terms}</tt></blockquote>

A new operation can be defined with the \ref define_operation operation, where
the first operand is treated as containing a \ref lexicon with
operator-to-operand mappings, and the second operand contains the program to
evaluate using the defined operation:

-	<tt>define { double-quote {quote quote} } { double-quote {A} }</tt>
	<blockquote><tt>{{{A}}}</tt></blockquote>

Any string can be used as an operator, with separators and operand braces
escaped with a backquote:

-	<tt>define { double` quote {quote quote} } { double` quote {A} }</tt>
	<blockquote><tt>{{{A}}}</tt></blockquote>
-	<tt>&lt;-terms { double` quote operator }</tt>
	<blockquote><tt>{double` quote}{operator}</tt></blockquote>

Unicode is fully supported:

-	<tt>&lt;-characters {한글}</tt>
	<blockquote><tt>{한}{글}</tt></blockquote>
-	<tt>&lt;-code` points {한글}</tt>
	<blockquote><tt>{ᄒ}{ᅡᆫ글}</tt></blockquote>
-	<tt>&lt;-terms {한글 韓}</tt>
	<blockquote><tt>{한글}{韓}</tt></blockquote>

Strings are automatically
<a href="http://unicode.org/reports/tr15">normalized</a> to
<a href="http://unicode.org/reports/tr15/#Norm_Forms">NFD</a>, but can be
explicitly normalized to
<a href="http://unicode.org/reports/tr15/#Norm_Forms">NFKD</a> using the
\ref normalize_operation operation:

-	<tt>normalize {2⁵}</tt>
	<blockquote><tt>{25}</tt></blockquote>

Recursion is very efficient in <a href="http://om-language.org">Om</a>, due to
(a) the "eager" evaluation model enabled by prefix concatenative syntax (i.e.
data is consumed immediately rather than being left on a stack), and (b) the
non-recursive evaluation implementation in the evaluator that minimizes memory
overhead of recursive calls and prevents stack overflow.  The following example
uses recursion to give the minutes in a colon-delimited 24-hour time string:

-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ minutes {1:23} }<br/>
	</tt>
	<blockquote><tt>{23}</tt></blockquote>

Each step of an evaluation can be represented as a program.  The following is
the above program broken down into its evaluation steps, where the code that is
about to be replaced is <b>bold</b>, and the code that was just replaced is
<em>italicized</em>:

-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ <b>minutes</b> {1:23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ <em>dequote choose {minutes} {} = {:} &lt;-characters</em> {1:23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote choose {minutes} {} = {:} <b>&lt;-characters {1:23}</b> }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote choose {minutes} {} = {:} <em>{1} {:23}</em> }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote choose {minutes} {} <b>= {:} {1}</b> {:23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote choose {minutes} {} <em>{}</em> {:23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote <b>choose {minutes} {} {}</b> {:23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote <em>{minutes}</em> {:23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ <b>dequote {minutes}</b> {:23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ <em>minutes</em> {:23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ <b>minutes</b> {:23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ <em>dequote choose {minutes} {} = {:} &lt;-characters</em> {:23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote choose {minutes} {} = {:} <b>&lt;-characters {:23}</b> }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote choose {minutes} {} = {:} <em>{:} {23}</em> }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote choose {minutes} {} <b>= {:} {:}</b> {23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote choose {minutes} {} <em>{{:}}</em> {23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote <b>choose {minutes} {} {{:}}</b> {23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ dequote <em>{}</em> {23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ <b>dequote {}</b> {23} }<br/>
	</tt>
-	<tt>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ {23} }<br/>
	</tt>
-	<tt><b>define<br/>
	{ minutes { dequote choose {minutes} {} = {:} &lt;-characters } }<br/>
	{ {23} }</b><br/>
	</tt>
-	<tt><em>{23}</em></tt>

\section downloading Downloading

Archive files of all versions of the <a href="http://om-language.org">Om</a>
code can be downloaded from the
<a href="https://github.com/sparist/Om/tags">GitHub Tags page</a>.

Code can also be obtained by Git checkout, as indicated on the
<a href="https://github.com/sparist/Om">GitHub main page</a>.

\section building Building

Although it should be possible to build the code on any mainstream platform, it
has only been built and tested on:

-	Xcode 4.5.2 on Mac OS X 10.8.2 (Mountain Lion)
-	Visual Studio 2010 Express on Windows Vista

The project is generated by CMake, and contains the following targets:

-	<b>%Om</b>: builds the interpreter project into
	<tt>products/</tt><em>platform</em>.
-	<b>%Om Documentation</b>: builds the documentation into
	<tt>products/doxygen</tt>.
	Open <tt>html/index.html</tt> to view the HTML documentation in a browser.

\subsection building__xcode Xcode

Building in Xcode requires:

-	<a href="http://itunes.apple.com/us/app/xcode/id497799835?ls=1&mt=12">Xcode</a>
-	<a href="http://doxygen.org">Doxygen</a> and
	<a href="http://www.macports.org/ports.php?by=name&substr=graphviz">Graphviz
	(via MacPorts)</a>

To generate the <tt>Om.xcodeproj</tt> file (in <tt>products/xcode</tt>):

-	Ensure that Doxygen and Graphviz are installed, and in the path variable
	visible to applications.
	<a href="http://overwatering.org/blog/2012-2013/08/setting-path-osx-mountain-lion">This
	article</a> explains how to do so.
-	Clone the Git repository.
-	Run <tt>make.sh</tt> and pass it the following arguments (in order):
	- 	The ICU root directory path.  To create this directory, download and
		unpack the
		<a href="http://download.icu-project.org/files/icu4c/50.1.1/icu4c-50_1_1-src.tgz">ICU4C
		50.1.1 code archive</a> from the
		<a href="http://site.icu-project.org/download">ICU download page</a>.
	-	The Boost root directory path.  To create this directory, download and
		unpack the
		<a href="http://sourceforge.net/projects/boost/files/boost/1.52.0/boost_1_52_0.tar.gz/download">Boost
		1.52.0 code archive</a> from the
		<a href="http://www.boost.org/users/download">Boost download page</a>.
	-	<b>Optional:</b> The UnitTest++ root directory path.  If omitted, unit
		tests will be excluded from the build.  To create this directory,
		download and unpack the
		<a href="http://sourceforge.net/projects/unittest-cpp/files/latest/download?source=files">UnitTest++
		1.4 code archive</a> from the
		<a href="http://sourceforge.net/projects/unittest-cpp/files">UnitTest++
		download page</a>.

To update the Xcode project to reflect changes to the code directory tree:

-	Run <tt>remake.sh</tt>.

To remove the directory generated by <tt>make.sh</tt>:

-	Run <tt>unmake.sh</tt>.

\subsection building__visual_studio Visual Studio

Building in Visual Studio requires:

-	<a href="http://www.microsoft.com/visualstudio/eng/downloads">Visual Studio
	2010</a>
-	<a href="http://msysgit.github.com">Git</a>
-	<a href="http://www.cmake.org">CMake</a>
-	<a href="http://doxygen.org">Doxygen</a> and
	<a href="http://graphviz.org">Graphviz</a>
-	<a href="http://subversion.tigris.org">Subversion</a> (if unit tests are to
	be included)

To generate the <tt>Om.sln</tt> file (in <tt>products/vs</tt>):

-	Ensure that Doxygen and Graphviz are installed, and in the path variable.
-	Clone the Git repository.
-	Run <tt>make.bat</tt> and pass it the following arguments (in order):
	- 	The ICU root directory path.  To create this directory, download and
		unpack the
		<a href="http://download.icu-project.org/files/icu4c/49.1.2/icu4c-49_1_2-src.zip">ICU4C
		49.1.2 code archive</a> from the
		<a href="http://site.icu-project.org/download">ICU download page</a>.
		(Note that there is presently a
		<a href="https://svn.boost.org/trac/boost/ticket/7839">Boost bug</a>
		that prevents building against ICU4C 50.1.1 on Windows.)
	-	The Boost root directory path.  To create this directory, download and
		unpack the
		<a href="http://sourceforge.net/projects/boost/files/boost/1.52.0/boost_1_52_0.zip/download">Boost
		1.52.0 code archive</a> from the
		<a href="http://www.boost.org/users/download">Boost download page</a>.
	-	<b>Optional:</b> The UnitTest++ root directory path.  If omitted, unit
		tests will be excluded from the build.  To create this directory, get
		the UnitTest++ 1.4 code via Subversion checkout (described on the
		<a href="https://sourceforge.net/projects/unittest-cpp/develop">UnitTest++
		developer page</a>) and apply the patch attached to the
		<a href="https://sourceforge.net/tracker/?func=detail&aid=3583690&group_id=158151&atid=806686">Visual
		Studio 2010 support ticket</a>.  The UnitTest++ root directory is the
		<tt>UnitTest++</tt> subdirectory of the Subversion checkout directory.

To update the Visual Studio solution to reflect changes to the code directory
tree:

-	Run <tt>remake.bat</tt>.

To remove the directory generated by <tt>make.bat</tt>:

-	Run <tt>unmake.bat</tt>.

\section using Using

The <a href="http://om-language.org">Om</a> interpreter takes input from the
standard input stream, ending at the first unbalanced end brace, and sends
output to the standard output stream.

<a href="http://om-language.org">Om</a> can be incorporated into any C++ or
Objective-C++ project as follows:

-	Add the <a href="http://om-language.org">Om</a> <tt>code</tt> directory to
	the include path and include the desired files.  Inclusion of any operation
	files will automatically add the corresponding operation to the global
	system.
-	Link to the required <a href="http://icu-project.org">ICU (ICU4C 49.1.2)</a>
	and/or <a href="http://boost.org">Boost (1.51.0)</a> library dependencies.
-	Call the <tt>Om::System::Initialize</tt> function prior to use (eg. in the
	<tt>main</tt> function), passing in the desired UTF-8 locale (eg.
	"en_US.UTF-8").
-	Construct an <tt>Om::Environment</tt>, populate with any additional
	operator-program mappings, and call one of its <tt>Evaluate</tt> functions
	to evaluate a program.

\section developing Developing

The <a href="http://om-language.org">Om</a> library is written in modern,
portable C++.

\subsection developing__coding_standard Coding Standard

All <a href="http://om-language.org">Om</a> development must adhere to the
<a href="http://sparist.github.com/cpp_coding_standard.html">Sparist C++ Coding
Standard</a>.

\subsection developing__adding_operations Adding Operations

Additional native functionality can be added to
<a href="http://om-language.org">Om</a> by implementing new operations in C++.

There are two ways to implement an operation: as a composite operation, or an
atomic operation.

To implement a composite operation, or an atomic operation that consumes no
operands:

-	Define the operation <tt>struct</tt> in the <tt>Om::Operations</tt>
	namespace.
-	Define the static <tt>GetName()</tt> method, which returns a <tt>static char
	const *</tt> containing the name.
-	Define the static <tt>Give( Evaluation &amp; )</tt> method, with no return
	value, to give existing operations and/or elements to the evaluation.

To define an atomic operation that consumes one or more operands:

-	Define the operation <tt>struct</tt>, derived from
	<tt>Om::DefaultOperation&lt;</tt> <em>operation</em> <tt>&gt;</tt> (where
	<em>operation</em> is the name of the operation <tt>struct</tt>), in the
	<tt>Om::Operations</tt> namespace.
-	Define the static <tt>GetName()</tt> method, which returns a <tt>static char
	const *</tt> containing the name.
-	Add the implementation, using existing operations as a guide:
	-	Implement the functions necessary to compile.
	-	Optionally override virtual function implementations in
		<tt>DefaultOperation</tt>, such as <tt>ReadQuotedElements</tt>, that may
		be more optimally implemented in the operation.

For any operation implementation, code must be added to the operation header
that inserts the operation into the system when the header is included, as
follows (where <tt>WhateverOperation</tt> is a stand-in for the name of the
operation <tt>struct</tt>):

<code>
	namespace<br/>
	{<br/>
	&nbsp;&nbsp;&nbsp;&nbsp;static Definition< WhateverOperation > const
	theWhateverDefinition;<br/>
	}
</code>

\subsection developing__adding_programs Adding Programs

New data types can be added to <a href="http://om-language.org">Om</a> by
extending <tt>Om::Program</tt> and defining the functions necessary to
instantiate the class.  Use existing programs as a guide.

Program types should be defined in the <tt>Om</tt> namespace.

\subsection developing__analyzing_code Analyzing Code

There are some basic free static analysis tools that can be applied to the
<a href="http://om-language.org">Om</a> code.

-	<a href="https://github.com/terryyin/hfcca"><b>HFCCA</b></a> is a Python
	script that measures cyclomatic complexity and counts the number of lines of
	code in C++ source files, not including comments or tests.  If Python is
	installed and in the path, HFCCA can be applied to
	<a href="http://om-language.org">Om</a> by entering the following at the
	terminal from inside the <a href="http://om-language.org">Om</a> directory:
	<blockquote><tt>python hfcca.py -p -v code</tt></blockquote>
-	<a href="http://cloc.sourceforge.net"><b>CLOC</b></a> is a stand-alone Perl
	script that determines total line counts.  If Perl is installed, CLOC can be
	applied to <a href="http://om-language.org">Om</a> by entering the following
	at the terminal from inside the <a href="http://om-language.org">Om</a>
	directory:
	<blockquote><tt>cloc.pl code</tt></blockquote>

\section issue_tracking Issue Tracking

Issues are reported and tracked with the
<a href="https://github.com/sparist/Om/issues">Om GitHub issue tracker</a>.

\section license License

This program and the accompanying materials are made available under the terms
of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public
License, Version 1.0</a>, which accompanies this distribution.

For more information about this license, please see the
<a href="http://www.eclipse.org/legal/eplfaq.php">Eclipse Public License
FAQ</a>.

\section funding Funding

If you are interested in funding development of the Om language, either for
general or domain-specific functionality, please contact me at <a
	href="mailto:information@sparist.com?subject=Om%20Funding"
>information@sparist.com</a>.

*/
#if !defined( Om_ )
	#define Om_ Om

//! The Om language implementation.
namespace Om
{
}

#endif
