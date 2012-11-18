## Introduction

The Om language represents an attempt to answer the question: *What is the
simplest abstract syntax that can articulate any algorithm for efficient and
precise evaluation?*

Om is:

-	**A concatenative programming language** with a fundamentally simple prefix
	syntax and type system.
-	**An abstract algorithmic notation language** that does not expose any
	computer implementation details (such as byte or machine word length).
-	**A data transfer format** that is trivial to parse.
-	**Embeddable**: implemented as a header-only C++ library that can be
	incorporated into any C++ or Objective-C++ program.
-	**Extensible**: new native operations can be implemented as C++ classes.
-	**Unicode-correct**: any [UTF-8](http://www.utf8everywhere.org) text
	(without byte-order marker) defines a valid Om program, and all text is
	treated as UTF-8.

Om is *not*:

-	**Complete**.  Although the intent is to develop Om into a full-featured
	language, the software is currently at a very early "proof of concept"
	stage, requiring the addition of many operations (such as basic numerical
	operations) and optimizations before it can be considered useful for any
	purpose.  It has been made available in order to demonstrate the underlying
	concepts and welcome others to get involved in early development.
-	**Stationary**.  Om may undergo dramatic changes in every respect before
	version 1.0.

## Syntax

The following sections define the syntax of Om in its entirety.

### Program

An Om program is comprised of only three syntactic elements, as follows:

![](http://sparist.com/projects/om/images/program.png)

### Operator

An operator has the following syntax:

![](http://sparist.com/projects/om/images/operator.png)

Any code point may be included in an operator by encoding it with a preceding
backquote (\`), which is disregarded if the code point is not a backquote,
operand bracket, or separator code point.

### Separator

A separator has the following syntax:

![](http://sparist.com/projects/om/images/separator.png)

### Operand

An operand has the following syntax:

![](http://sparist.com/projects/om/images/operand.png)

## How It Works

### Operations

Om is a [concatenative](http://concatenative.org) language; an Om program
defines an *operation*, which is a composition of operations defined by each
sub-program.

An operation is a function that takes a program as input, and generates a
program as output.  Each operation represents a transformation on the program
itself.

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

### Evaluation

Evaluation occurs from right to left and is performed recursively.

The evaluator consists of:

-	An environment, for resolving operators to operations.  Any operators that
	are not present map to an "identity" operation that leaves the program,
	including the operator, unchanged.
-	An operation queue, for storing operations that are awaiting nested
	operations to be evaluated (in the event that the latter produces
	operands that can be consumed by the former).

The evaluator reads, parses and evaluates the input stream in a single pass,
sending results to the output stream as soon as they can be evaluated.  This is
possible because Om uses a prefix notation, rather than the postfix notation
employed by other concatenative languages.  Other benefits of prefix notation
include:

-	Stack underflows are impossible.
-	Operations can be optimized to only read into memory the data that is
	required; stack-based postfix languages have no knowledge of the operation
	to apply until the data is already in memory, on the stack.
-	An IDE can provide hints to the user about the data that is expected by
	an operation.

### Data Types

Om uses a novel **panmorphic** type system, in which all data values are
represented entirely within the language through a common interface (the
operand), and each operand exposes no data type: any operation will accept any
operand as a valid input and will interpret it in whatever way the operation
deems appropriate.

Data types are relegated to an implementation layer and represent optimizations
for a set of operations.  Each operand in memory contains a single program
implementation.  By default, this is the "literal" program, which preserves all
data in the operand, verbatim.  An operation may convert this to another program
implementation (eg. a "find" operation would convert the program of one of its
operands to the "lexicon" type, which provides fast mapping from operator to
operand).  These conversions can be done transparently because all operands
share the same interface (comprised of separators, operators, and/or operands).

Operations in a program can be ordered by the programmer to minimize these
conversions and increase performance (since the conversion will not occur if the
operand already has the desired program implementation), but it is not necessary
for obtaining a correct computation.  As such, data types become an
implementation detail.

## Examples

Operands can be dropped and copied:

-	`drop {A}{B}{C}`

		{B}{C}

-	`copy {A}{B}{C}`

		{A}{A}{B}{C}

-	`drop copy {A}`

		{A}

-	`copy copy {A}`

		{A}{A}{A}

The `choose` operation selects one of two operands, depending on whether a
third is empty:

-	`choose {It was empty.}{It was non-empty.}{I am not empty.}`

		{It was non-empty.}

-	`choose {It was empty.}{It was non-empty.}{}`

		{It was empty.}

An operation without sufficient operands becomes the identity operation:

-	`drop`

		drop

-	`choose {It was empty.}{It was non-empty.}`

		choose {It was empty.}{It was non-empty.}

The `quote` and `dequote` operations add and remove a layer of operand braces,
respectively:

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

Strings are automatically [normalized](http://unicode.org/reports/tr15) to NFD,
but can be explicitly normalized to NFKD using the `normalize` operator:

-	`normalize {ﬁ}`

		{fi}

-	`normalize {2⁵}`

		{25}

A new operation can be defined within a scope with the `evaluate` operator,
where the first operand is treated as a "lexicon" with operator-to-operand 
mappings:

-	`evaluate { double-quote {quote quote} } { double-quote {A} }`

		{{{A}}}

Any string can be used as an operator, with separators and operand braces
escaped with a backquote:

-	``evaluate { double` quote {quote quote} } { double` quote {A} }``

		{{{A}}}

-	``<-terms { double` quote operator }``

		{double` quote}{operator}

## Downloading

The Git repository for Om can be found on the [Om
GitHub page](https://github.com/sparist/Om).

## Building

Although it should be possible to build the sources on any mainstream platform,
the code has only been built and tested on:

-	Xcode 4.5.2 on Mac OS X 10.8.2 (Mountain Lion)
-	Visual Studio 2010 Express on Windows Vista

The project/solution file is generated by CMake, and contains the following
targets:

-	**Om**: builds the interpreter executable.
-	**Om Documentation**: builds the documentation into products/doxygen.  Open
	html/index.html to view the HTML documentation in a browser.

### Xcode

Building in Xcode requires:

-	[Xcode](http://itunes.apple.com/us/app/xcode/id497799835?ls=1&mt=12)
-	[Doxygen](http://doxygen.org) and [Graphviz
	(via MacPorts)](http://www.macports.org/ports.php?by=name&substr=graphviz)

To generate the Om.xcodeproj file (in products/xcode):

-	Ensure that Doxygen and Graphviz are installed, and in the path variable
	visible to applications.  See [this
	article](http://overwatering.org/blog/2012/08/setting-path-osx-mountain-lion)
	for how to do this.
-	Clone the git repository.
-	Run make.sh and pass it the following arguments (in order):
	- 	The ICU root directory path.  To create this directory, download and
		unpack the [ICU4C 49.1.2 source
		archive](http://download.icu-project.org/files/icu4c/49.1.2/icu4c-49_1_2-src.tgz).
	-	The Boost root directory path.  To create this directory, download and
		unpack the [Boost 1.51.0 source
		archive](http://sourceforge.net/projects/boost/files/boost/1.51.0/boost_1_51_0.tar.gz/download).
	-	**Optional:** The UnitTest++ root directory path.  If omitted, unit
		tests will be excluded from the build.  To create this directory,
		download and unpack the [UnitTest++ 1.4 sources
		archive](http://sourceforge.net/projects/unittest-cpp/files/latest/download?source=files).

To update the Xcode project to reflect changes to the code directory tree:

-	Run remake.sh.

To remove the directory generated by make.sh:

-	Run unmake.sh.

### Visual Studio

Building in Visual Studio requires:

-	[Visual Studio 2010](http://www.microsoft.com/visualstudio/eng/downloads)
-	[Git](http://msysgit.github.com)
-	[CMake](http://www.cmake.org)
-	[Doxygen](http://doxygen.org) and [Graphviz](http://graphviz.org)
-	[Subversion](http://subversion.tigris.org) (if unit tests are to be
	included)

To generate the Om.sln file (in products/vs):

-	Ensure that Doxygen and Graphviz are installed, and in the path variable.
-	Clone the git repository.
-	Run make.bat and pass it the following arguments (in order):
	- 	The ICU root directory path.  To create this directory, download and
		unpack the [ICU4C 49.1.2 source
		archive](http://download.icu-project.org/files/icu4c/49.1.2/icu4c-49_1_2-src.zip).
	-	The Boost root directory path.  To create this directory, download and
		unpack the [Boost 1.51.0 source
		archive](http://sourceforge.net/projects/boost/files/boost/1.51.0/boost_1_51_0.zip/download).
	-	**Optional:** The UnitTest++ root directory path.  If omitted, unit
		tests will be excluded from the build.  To create this directory, get
		the UnitTest++ 1.4 sources via Subversion checkout (described on the
		[developer page](https://sourceforge.net/projects/unittest-cpp/develop))
		and apply the patch attached to the [Visual Studio 2010 support
		ticket](https://sourceforge.net/tracker/?func=detail&aid=3583690&group_id=158151&atid=806686).
		The UnitTest++ root directory is the UnitTest++ subdirectory of the
		Subversion checkout directory.

To update the Visual Studio solution to reflect changes to the code directory
tree:

-	Run remake.bat.

To remove the directory generated by make.bat:

-	Run unmake.bat.

## Using

The Om interpreter takes input from the standard input stream, ending at the
first unbalanced end brace, and sends output to the standard output stream.

Om can be incorporated into any C++ or Objective-C++ project as follows:

-	Add the Om code directory to the include path and include the
	desired files.  Inclusion of any operation files will automatically
	add the corresponding operation to the global system.
-	Link to the required [ICU (ICU4C 49.1.2)](http://icu-project.org) and/or
	[Boost (1.51.0)](http://boost.org/") library dependencies.
-	Call `Om::System::Initialize()` prior to use (eg. in `main()`), passing in
	the desired UTF-8 locale (eg. "en_US.UTF-8").
-	Construct an `Om::Environment`, populate with any additional
	operator-program mappings, and call one of its Evaluate() methods to
	evaluate a program.

## Developing

The Om library is written in modern, portable C++.

All Om development must adhere to the C++ coding standards given in the
[Development Standards](http://sparist.com/development_standards.html) page.

### Adding Operations

Additional native functionality can be added to Om by implementing new
operations in C++.

There are two ways to implement an operation: as a composite operation, or an
atomic operation.

To implement a composite operation:

-	Define the operation `struct`.
-	Define the static `GetName()` method, which returns a `static char const *`
	containing the name.
-	Define the static `Give( Evaluator & )` method, with no return value, to
	give existing operations and/or elements to the evaluator in the desired
	order.

To define an atomic operation:

-	Define the operation `struct`, derived from
	`Om::DefaultEvaluand<` *operation* `>`, where *operation* is the name of the
	operation.
-	Define the static `GetName()` method, which returns a `static char const *`
	containing the name.
-	Add the implementation, using existing operations as a guide:
	-	Implement the functions necessary to compile.
	-	Optionally override virtual function implementations in
		`DefaultEvaluand`, such as `ReadQuotedElements`, that may be more
		optimally implemented in the operation.

Operation types should be defined in the `Om::Operations` namespace.

For any operation implementation, code must be added to the operation header
that inserts the operation into the system when the header is included, as
follows (where `WhateverOperation` is a stand-in for the name of the operation
`struct`):

	namespace
	{
		static Definition< WhateverOperation > const theWhateverDefinition;
	}

### Adding Programs

New data types can be added to Om by extending `Om::Program` and defining the
functions necessary to instantiate the class.  Use existing programs as a guide.

Program types should be defined in the `Om` namespace.

### Analyzing Code

There are some basic free static analysis tools that can be applied to the Om
code.

#### HFCCA

[Header-free cyclomatic complexity analyzer
(HFCCA)](https://github.com/terryyin/hfcca) is a Python script that measures
cyclomatic complexity and counts the number of lines of code in cpp files, not
including comments or tests.  If Python is installed and in the path, HFCCA can
be applied to Om by entering the following at the terminal from inside the Om
directory:

	python hfcca.py -p -v code

#### CLOC

[CLOC](http://cloc.sourceforge.net) is a stand-alone Perl script that determines
total line counts.  If Perl is installed, CLOC can be applied to Om by entering
the following at the terminal from inside the Om directory:

	cloc.pl code

## Roadmap

This section provides the tentative roadmap for new development over the next
few releases.  This is subject to change.

### 0.1

-	Initial proof-of-concept implementation.  Note that the software and
	language are likely to undergo significant changes in subsequent releases,
	some of which may not be backward-compatible with this release.

### 0.2

-	Restructure operation implementations as necessary so that they can present
	metadata (eg. IDE hints) such as:
	-	What does the operation do?
	-	What program type will the next operand be converted to?
	-	How will the operation use the next program?
-	Fill out basic functionality, such as:
	-	A Number program type, and related operations, with the following
		qualities:
		-	Machine-independent representation.
		-	Based on the [Extended Complex
			Plane](http://en.wikipedia.org/wiki/Riemann_sphere).
		-	Retains the entire computation that generates it, and optimizes
			operations on the computation itself (such as operations cancelling
			out), until it needs to be written or converted, at which point the
			computation is executed to the specified number of significant
			figures.
		-	Implemented using [GMP](http://gmplib.org).
	-	Basic comparison operations for which false is the empty string and true
		is the original value.  For example, `< {3} {2}` (2 less than 3) would
		become `{2}`, and `< {3} {4}` would become `{}`.
	-	More Unicode-compliant string operations.

### 0.3

-	Test.
-	Write some sample programs, and implement operations as necessary.
-	Benchmark and optimize; may include implementing concurrent evaluation
	(using [Intel Threading Building
	Blocks](http://threadingbuildingblocks.org)).

## License

This program and the accompanying materials are made available under the terms
of the [Eclipse Public License, Version
1.0](http://www.eclipse.org/legal/epl-v10.html), which accompanies this
distribution.

For more information about this license, please see the [Eclipse Public License
FAQ](http://www.eclipse.org/legal/eplfaq.php).
