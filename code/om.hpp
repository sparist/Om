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

\mainpage Main Page

\tableofcontents

\section introduction Introduction

The %Om language represents an attempt to answer the question: *What is the
simplest abstract syntax that can articulate any algorithm for efficient and
precise evaluation?*

%Om is:

-	**A concatenative programming language** with a fundamentally simple prefix
	syntax and type system.
-	**An abstract algorithmic notation language** that does not expose any
	computer implementation details (such as byte or machine word length).
-	**A data transfer format** that is trivial to parse.
-	**Embeddable**: implemented as a header-only C++ library that can be
	incorporated into any C++ or Objective-C++ program.
-	**Extensible**: new native operations can be implemented as C++ classes.
-	**Unicode-correct**: any <a href="http://www.utf8everywhere.org">UTF-8</a>
	text (without byte-order marker) defines a valid %Om program.

%Om is *not*:

-	**Complete**.  Although the intent is to develop %Om into a full-featured
	language, the software is currently at a very early "proof of concept"
	stage, requiring the addition of many operations (such as basic numerical
	operations) and optimizations before it can be considered useful for any
	purpose.  It has been made available in order to demonstrate the underlying
	concepts and welcome others to get involved in early development.
-	**Stationary**.  %Om may undergo dramatic changes in every respect before
	version 1.0.

\section syntax Syntax

The following sections define the syntax of %Om in its entirety.

\subsection syntax__program Program

An %Om program is comprised of only three syntactic elements, as follows:

![](program.png)

\subsection syntax__operator Operator

An operator has the following syntax:

![](operator.png)

Any code point may be included in an operator by encoding it with a preceding
backquote (<tt>`</tt>), which is disregarded if the code point is not a
backquote, operand bracket, or separator code point.

\subsection syntax__separator Separator

A separator has the following syntax:

![](separator.png)

\subsection syntax__operand Operand

An operand has the following syntax:

![](operand.png)

\section how_it_works How It Works

\subsection how_it_works__operations Operations

An operation is a function, defined by a program, that takes a program as input
and generates a program as output.  %Om is a <a
href="http://concatenative.org">concatenative</a> language: the operation
defined by an %Om program is a composition of operations defined by each
sub-program.

The application of an operation to the remaining program (to the right) results
in a transformation on the applied program itself.  Because programs are
homomorphic with the operations they represent, the application of an operation
to a program can be treated equivalently to the composition of an operation with
the operation that the applied program represents.  As such, the concept of
application can be omitted, resulting in <a
href="http://en.wikipedia.org/wiki/Combinatory_logic">combinatory logic</a>.

Program elements each correspond to the following operations:

-	Separator:
	-	**Input:** The program, with the separator at the front
	-	**Output:** The program, with the front separator normalized
		(top-level white space is insignificant)
-	Operand:
	-	**Input:** The program, with the operand at the front
	-	**Output:** The program unchanged
-	Operator:
	-	**Input:** The program, with the operator at the front
	-	**Output:** The operation mapped to the operator by the evaluator,
		which is given the program following the operator as input

All of the native operations included in the current release are documented in
the \ref operations module.

\subsection how_it_works__evaluation Evaluation

Evaluation occurs from right to left and is performed recursively.

The evaluator consists of:

-	<b>An environment</b> for resolving operators to operations.  Any operators
	that are not present map to an "identity" operation that leaves the program,
	including the operator, unchanged.
-	<b>An operation queue</b> for storing operations that are awaiting nested
	operations to be evaluated (in the event that the latter produces operands
	that can be consumed by the former).

The evaluator reads, parses and evaluates the input stream in a single pass,
sending results to the output stream as soon as they can be evaluated.  This is
possible because %Om uses a prefix notation, rather than the postfix notation
employed by other concatenative languages.  Other benefits of prefix notation
include:

-	Stack underflows are impossible.
-	Operations can be optimized to only read into memory the data that is
	required; stack-based postfix languages have no knowledge of the operation
	to apply until the data is already in memory, on the stack.
-	An IDE can provide hints to the user about the data that is expected by
	an operation.

\subsection how_it_works__data_types Data Types

%Om uses a novel **panmorphic** type system in which all data values are
represented within the language solely through a common program interface
(comprised of only separators, operators, and/or operands), and each operand 
exposes no data type: any operation will accept any operand as a valid input and
interpret it however the operation deems appropriate.

Data types are relegated to an implementation layer and represent optimizations
for a set of operations.  Each operand in memory contains a single program
implementation; by default, this is the \ref literal program, which preserves
all data in the operand, verbatim.  However, an operation may prefer an operand
to have a different program implementation that is optimized for specific
functionality used by the operation.  The \ref find_operation operation, for
example, prefers one of its operands to have a \ref lexicon program type for
fast mapping from operator to operand.  In such cases, an operation can simply
convert an undesired program implementation to the desired type through the
common program interface without impacting the semantics of the program.

Operations in a program can be ordered by the programmer to increase performance
by minimizing conversions between program implementations, but it is not
necessary for obtaining a correct computation.  Data types in %Om therefore
become an optimization-phase implementation detail.

All of the native data types included in the current release are documented in
the \ref programs module.

\section examples Examples

Operands can be dropped and copied:

-	`drop {A}{B}{C}`

		{B}{C}

-	`copy {A}{B}{C}`

		{A}{A}{B}{C}

-	`drop copy {A}`

		{A}

-	`copy copy {A}`

		{A}{A}{A}

The \ref choose_operation operation selects one of two operands, depending on
whether a third is empty:

-	`choose {It was empty.}{It was non-empty.}{I am not empty.}`

		{It was non-empty.}

-	`choose {It was empty.}{It was non-empty.}{}`

		{It was empty.}

An operation without sufficient operands becomes the identity operation:

-	`drop`

		drop

-	`choose {It was empty.}{It was non-empty.}`

		choose {It was empty.}{It was non-empty.}

The \ref quote_operation and \ref dequote_operation operations add and remove a
layer of operand braces, respectively:

-	`quote {B}`

		{{B}}

-	`dequote {{B}}`

		{B}

-	`dequote {copy}`

		copy

-	`dequote {copy} {A}`

		{A}{A}

Operands can be popped from and pushed to:

-	`<-characters {ABC}`

		{A}{BC}

-	`->literal {A}{BC}`

		{ABC}

-	`<-terms {some terms}`

		{some}{terms}

Unicode is fully supported:

-	`<-characters {한글}`

		{한}{글}

-	`<-codepoints {한글}`

		{ᄒ}{ᅡᆫ글}

-	`<-terms {한글 韓}`

		{한글}{韓}

Strings are automatically <a
href="http://unicode.org/reports/tr15">normalized</a> to NFD, but can be
explicitly normalized to NFKD using the \ref normalize_operation operation:

-	`normalize {ﬁ}`

		{fi}

-	`normalize {2⁵}`

		{25}

A new operation can be defined within a scope with the \ref evaluate_operation
operation, where the first operand is treated as containing a \ref lexicon with
operator-to-operand mappings, and the second operand contains the program to
evaluate:

-	`evaluate { double-quote {quote quote} } { double-quote {A} }`

		{{{A}}}

Any string can be used as an operator, with separators and operand braces
escaped with a backquote:

-	``evaluate { double` quote {quote quote} } { double` quote {A} }``

		{{{A}}}

-	``<-terms { double` quote operator }``

		{double` quote}{operator}

Recursion is very efficient in %Om, due to (a) the "eager" evaluation model
enabled by prefix concatenative syntax (i.e. data is consumed immediately rather
than being left on a stack), and (b) the non-recursive evaluation implementation
in the evaluator that minimizes memory overhead of recursive calls and prevents
stack overflow.  The following example uses recursion to give the minutes in a
colon-delimited 24-hour time string:

-	`evaluate { minutes { dequote choose {minutes} {} = {:} <-characters } }
	{ minutes {12:34} }`

		{34}

\section downloading Downloading

Archive files of all versions of the %Om code can be downloaded from the <a
href="https://github.com/sparist/Om/tags">Om GitHub Tags page</a>.

Code can also be obtained by Git checkout, as indicated on the <a
href="https://github.com/sparist/Om">Om GitHub main page</a>.

\section building Building

Although it should be possible to build the code on any mainstream platform, it
has only been built and tested on:

-	Xcode 4.5.2 on Mac OS X 10.8.2 (Mountain Lion)
-	Visual Studio 2010 Express on Windows Vista

The project is generated by CMake, and contains the following targets:

-	<b>%Om</b>: builds the interpreter project into
	`products/`<em>platform</em>.
-	<b>%Om Documentation</b>: builds the documentation into `products/doxygen`.
	Open `html/index.html` to view the HTML documentation in a browser.

\subsection building__xcode Xcode

Building in Xcode requires:

-	<a
	href="http://itunes.apple.com/us/app/xcode/id497799835?ls=1&mt=12">Xcode</a>
-	<a href="http://doxygen.org">Doxygen</a> and <a
	href="http://www.macports.org/ports.php?by=name&substr=graphviz">Graphviz
	(via MacPorts)</a>

To generate the `Om.xcodeproj` file (in `products/xcode`):

-	Ensure that Doxygen and Graphviz are installed, and in the path variable
	visible to applications.  <a
	href="http://overwatering.org/blog/2012/08/setting-path-osx-mountain-lion">This
	article</a> explains how to do so.
-	Clone the Git repository.
-	Run `make.sh` and pass it the following arguments (in order):
	- 	The ICU root directory path.  To create this directory, download and
		unpack the <a
		href="http://download.icu-project.org/files/icu4c/49.1.2/icu4c-49_1_2-src.tgz">ICU4C
		49.1.2 code archive</a>.
	-	The Boost root directory path.  To create this directory, download and
		unpack the <a
		href="http://sourceforge.net/projects/boost/files/boost/1.51.0/boost_1_51_0.tar.gz/download">Boost
		1.51.0 code archive</a>.
	-	**Optional:** The UnitTest++ root directory path.  If omitted, unit
		tests will be excluded from the build.  To create this directory,
		download and unpack the <a
		href="http://sourceforge.net/projects/unittest-cpp/files/latest/download?source=files">UnitTest++
		1.4 code archive</a>.

To update the Xcode project to reflect changes to the code directory tree:

-	Run `remake.sh`.

To remove the directory generated by `make.sh`:

-	Run `unmake.sh`.

\subsection building__visual_studio Visual Studio

Building in Visual Studio requires:

-	<a href="http://www.microsoft.com/visualstudio/eng/downloads">Visual
	Studio 2010</a>
-	<a href="http://msysgit.github.com">Git</a>
-	<a href="http://www.cmake.org">CMake</a>
-	<a href="http://doxygen.org">Doxygen</a> and <a
	href="http://graphviz.org">Graphviz</a>
-	<a href="http://subversion.tigris.org">Subversion</a> (if unit tests are to
	be included)

To generate the `Om.sln` file (in `products/vs`):

-	Ensure that Doxygen and Graphviz are installed, and in the path variable.
-	Clone the Git repository.
-	Run `make.bat` and pass it the following arguments (in order):
	- 	The ICU root directory path.  To create this directory, download and
		unpack the <a
		href="http://download.icu-project.org/files/icu4c/49.1.2/icu4c-49_1_2-src.zip">ICU4C
		49.1.2 code archive</a>.
	-	The Boost root directory path.  To create this directory, download and
		unpack the <a
		href="http://sourceforge.net/projects/boost/files/boost/1.51.0/boost_1_51_0.zip/download">Boost
		1.51.0 code archive</a>.
	-	**Optional:** The UnitTest++ root directory path.  If omitted, unit
		tests will be excluded from the build.  To create this directory, get
		the UnitTest++ 1.4 code via Subversion checkout (described on the <a
		href="https://sourceforge.net/projects/unittest-cpp/develop">developer
		page</a>) and apply the patch attached to the <a
		href="https://sourceforge.net/tracker/?func=detail&aid=3583690&group_id=158151&atid=806686">Visual
		Studio 2010 support ticket</a>.
		The UnitTest++ root directory is the `UnitTest++` subdirectory of the
		Subversion checkout directory.

To update the Visual Studio solution to reflect changes to the code directory
tree:

-	Run `remake.bat`.

To remove the directory generated by `make.bat`:

-	Run `unmake.bat`.

\section using Using

The %Om interpreter takes input from the standard input stream, ending at the
first unbalanced end brace, and sends output to the standard output stream.

%Om can be incorporated into any C++ or Objective-C++ project as follows:

-	Add the %Om `code` directory to the include path and include the desired
	files.  Inclusion of any operation files will automatically add the
	corresponding operation to the global system.
-	Link to the required <a href="http://icu-project.org">ICU (ICU4C 49.1.2)</a>
	and/or <a href="http://boost.org">Boost (1.51.0)</a> library dependencies.
-	Call the `Om::System::Initialize` function prior to use (eg. in the `main`
	function), passing in the desired UTF-8 locale (eg. "en_US.UTF-8").
-	Construct an `Om::Environment`, populate with any additional
	operator-program mappings, and call one of its `Evaluate` functions to
	evaluate a program.

\section developing Developing

The %Om library is written in modern, portable C++.

All %Om development must adhere to the C++ coding standards given in the <a
href="http://sparist.com/development_standards.html">Development Standards</a>
page.

\subsection developing__adding_operations Adding Operations

Additional native functionality can be added to %Om by implementing new
operations in C++.

There are two ways to implement an operation: as a composite operation, or an
atomic operation.

To implement a composite operation, or an atomic operation that consumes no
operands:

-	Define the operation `struct` in the `Om::Operations` namespace.
-	Define the static `GetName()` method, which returns a `static char const *`
	containing the name.
-	Define the static `Give( Evaluation & )` method, with no return value, to
	give existing operations and/or elements to the evaluation.

To define an atomic operation that consumes one or more operands:

-	Define the operation `struct`, derived from
	`Om::DefaultOperation<` *operation* `>` (where *operation* is the name of
	the operation `struct`), in the `Om::Operations` namespace.
-	Define the static `GetName()` method, which returns a `static char const *`
	containing the name.
-	Add the implementation, using existing operations as a guide:
	-	Implement the functions necessary to compile.
	-	Optionally override virtual function implementations in
		`DefaultOperation`, such as `ReadQuotedElements`, that may be more
		optimally implemented in the operation.

For any operation implementation, code must be added to the operation header
that inserts the operation into the system when the header is included, as
follows (where `WhateverOperation` is a stand-in for the name of the operation
`struct`):

	namespace
	{
		static Definition< WhateverOperation > const theWhateverDefinition;
	}

\subsection developing__adding_programs Adding Programs

New data types can be added to %Om by extending `Om::Program` and defining the
functions necessary to instantiate the class.  Use existing programs as a guide.

Program types should be defined in the `Om` namespace.

\subsection developing__analyzing_code Analyzing Code

There are some basic free static analysis tools that can be applied to the %Om
code.

-	<a href="https://github.com/terryyin/hfcca"><b>HFCCA</b></a> is a Python
	script that measures cyclomatic complexity and counts the number of lines of
	code in C++ source files, not including comments or tests.  If Python is
	installed and in the path, HFCCA can be applied to %Om by entering the
	following at the terminal from inside the %Om directory:

		python hfcca.py -p -v code

-	<a href="http://cloc.sourceforge.net"><b>CLOC</b></a> is a stand-alone Perl
	script that determines total line counts.  If Perl is installed, CLOC can be
	applied to %Om by entering the following at the terminal from inside the %Om
	directory:

		cloc.pl code

\section issue_tracking Issue Tracking

Issues are reported and tracked with the <a
href="https://github.com/sparist/Om/issues">Om GitHub issue tracker</a>.

\section license License

This program and the accompanying materials are made available under the terms
of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public
License, Version 1.0</a>, which accompanies this distribution.

For more information about this license, please see the <a
href="http://www.eclipse.org/legal/eplfaq.php">Eclipse Public License FAQ</a>.

*/
#if !defined( Om_ )
	#define Om_ Om

//! The Om language implementation.
namespace Om
{
}

#endif
