/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb

\mainpage Main Page

	\section introduction__ Introduction
		The <a href="http://om-language.org">Om language</a> is:
		-	a novel, maximally-simple <a href="http://concatenative.org">concatenative</a>, <a href="http://en.wikipedia.org/wiki/Homoiconicity">homoiconic</a> <b>programming and algorithm notation language</b> with:
			-	\ref language__syntax__ "minimal syntax", comprised of only three elements.
			-	\ref language__functions__ "prefix notation", in which functions manipulate the remainder of the program itself.
			-	\ref language__data__ "panmorphic typing", allowing programming without data types.
		-	a trivial-to-parse <b>data transfer format</b>.
		-	<b>unicode-correct</b>: any <a href="http://www.utf8everywhere.org">UTF-8</a> text (without byte-order marker) defines a valid %Om program.
		-	implemented as a <b>C++ library</b> and:
			-	\ref using__including__ "embeddable" into any C++ or Objective-C++ program.
			-	\ref contributing__developing__ "extensible" with new data types or operations.

		The %Om language is <b><em>not</em></b>:
		-	<b>complete</b>. Although the intent is to develop it into a full-featured language, the software is currently at a very early "proof of concept" stage, requiring the addition of many operations (such as basic number and file operations) and optimizations before it can be considered useful for any real-world purpose. It has been made available in order to demonstrate the underlying concepts and welcome others to get involved in early development.
		-	<b>stationary</b>. %Om will likely undergo significant changes on its way to version 1.0.

	\section license__ License
		This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.

		For more information about this license, please see the <a href="http://www.eclipse.org/legal/eplfaq.php">Eclipse Public License FAQ</a>.

	\section using__ Using
		The %Om source code can be used for:
		-	\ref using__building__ a stand-alone interpreter from a script-generated build project.
		-	\ref using__including__ as a C++ header-only library.

		\subsection using__downloading__ Downloading
			The %Om source code is downloadable from the <a href="https://github.com/sparist/Om">Om GitHub repository</a>:
			-	The <b>Development</b> version (to which this documentation applies) can be obtained via <a href="https://github.com/sparist/Om">Git clone</a> or <a href="https://github.com/sparist/Om/archive/master.zip">archive file</a>.
			-	<b>Released</b> versions can be obtained via archive files from the <a href="https://github.com/sparist/Om/tags">GitHub tags page</a>.

		\subsection using__dependencies__ Dependencies
			\subsubsection using__dependencies__programs__ Programs
				To run scripts which build the dependency \ref using__dependencies__libraries__ and generate the build project, the following programs are required:
				-	<a href="http://cmake.org">CMake</a>
				-	Mac OS X:
					-	Xcode
				-	Windows:
					-	Visual Studio
					-	<a href="http://cygwin.com">Cygwin</a> (with bash, GNU make, ar, and ranlib)
				-	Ubuntu:
					-	Build-Essential package (<tt>sudo apt-get install build-essential</tt>)

				To build the \ref using__building__documentation__ in the build project, the following additional programs are required:
				-	<a href="http://doxygen.org">Doxygen</a>
				-	<a href="http://graphviz.org">Graphviz</a>

				To ensure that correct programs are used, programs should be listed in the command line path in the following order:
				-	Graphviz, Doxygen, and CMake
				-	Cygwin (&quot;<em>[cygwin]</em>/bin&quot;) <b>(Windows only)</b>
				-	Any other paths

			\subsubsection using__dependencies__libraries__ Libraries
				The following libraries are required to build the %Om code:
				-	ICU4C (the C++ implementation of the <a href="http://icu-project.org">ICU</a> library)
				-	<a href="http://boost.org">Boost</a>

		\subsection using__building__ Building
			A build project, containing targets for building the interpreter, tests, and documentation, can be generated into &quot;<em>[builds directory path]</em>/Om/projects/<em>[project]</em>&quot; by running the appropriate "generate" script from the desired builds directory:
			- "generate.sh" (Unix-based platforms)
			- "generate.bat" (Windows, to be run from the Visual Studio command line)

			Arguments include the desired project name (required), followed by any desired CMake arguments.

			By default, this script automatically installs all external dependency libraries (downloading and building as necessary) into &quot;<em>[builds directory path]</em>/<em>[dependency name]</em>/downloads/<em>[MD5]</em>/build/<em>[platform]</em>/install&quot;. This behaviour can be overridden by passing paths of pre-installed dependency libraries to the script:
			-	<tt>-D Icu4cInstallDirectory:Path=&quot;<em>[absolute ICU4C install directory path]</em>&quot;</tt>
			-	<tt>-D BoostInstallDirectory:Path=&quot;<em>[absolute Boost install directory path]</em>&quot;</tt>

			\subsubsection using__building__interpreter__ Interpreter
				The <b>Om.Interpreter</b> target builds the interpreter executable as &quot;<em>[%Om build directory path]</em>/executables/<em>[platform]</em>/<em>[configuration]</em>/Om.Interpreter&quot;. The interpreter:
					-	Accepts an optional command-line argument that specifies the desired UTF-8 <a href="http://userguide.icu-project.org/locale">locale string</a>. The default value is "en_US.UTF-8".
					-	Reads input from the standard input stream, ending at the first unbalanced end brace, and writes output to the standard output stream as it is computed.

			\subsubsection using__building__test__ Test
				The <b>Om.Test</b> target builds the test executable, which runs all unit tests, as &quot;<em>[%Om build directory path]</em>/executables/<em>[platform]</em>/<em>[configuration]</em>/Om.Test&quot;. These tests are also run when building the <tt>RUN_TESTS</tt> target (which is included when building the <tt>ALL_BUILD</tt> target).

			\subsubsection using__building__documentation__ Documentation
				The <b>Om.Documentation</b> target builds this documentation into the following folders in &quot;<em>[%Om build directory path]</em>/documentation&quot;:
				-	<b>&quot;html&quot;:</b> This HTML documentation. To view in a browser, open "index.html".
				-	<b>&quot;xml&quot;:</b> The XML documentation, which can be read by an integrated development environment to show context-sensitive documentation.

		\subsection using__including__ Including
			%Om is a header-only C++ library that can be incorporated into any C++ or Objective-C++ project as follows:
			-	Add the %Om "code" directory to the include path and include the desired files. Inclusion of any operation header files will automatically add the corresponding operation to the global system. Include "om.hpp" to include all %Om header files.
			-	Configure the project to link to the code dependencies as necessary, built with the correct configuration for the project. See the dependency "build.cmake" scripts for guidance.
			-	Call the <tt>Om::Language::System::Initialize</tt> function prior to use (e.g. in the <tt>main</tt> function), passing in the desired UTF-8 <a href="http://userguide.icu-project.org/locale">locale string</a> (e.g. "en_US.UTF-8").
			-	Construct an <tt>Om::Language::Environment</tt>, populate with any additional operator-program mappings, and call one of its <tt>Om::Language::Environment::Evaluate</tt> functions to evaluate a program.

			For more in-depth usage of the library, see the Om code documentation.

	\section language__ Language

		\subsection language__syntax__ Syntax
			An %Om program is a combination of three elements&mdash;operator, separator, and operand&mdash;as follows:
			\image html "program.png" width=100%

			\subsubsection language__syntax__operator__ Operator
				An operator has the following syntax:
				\image html "operator.png" width=100%

				Backquotes (<tt>`</tt>) in operators are disregarded if the code point following is not a backquote, operand brace, or separator code point.

			\subsubsection language__syntax__separator__ Separator
				A separator has the following syntax:
				\image html "separator.png" width=100%

			\subsubsection language__syntax__operand__ Operand
				An operand has the following syntax:
				\image html "operand.png" width=100%

		\subsection language__functions__ Functions
			The %Om language is <a href="http://concatenative.org">concatenative</a>, meaning that each %Om program evaluates to a function (that takes a program as input, and returns a program as output) and the concatenation of two programs (with an intervening separator, as necessary) evaluates to the composition of the corresponding functions.

			\subsubsection language__functions__prefix__ Prefix Notation
				Unlike other concatenative languages, the %Om language uses <a href="http://en.wikipedia.org/wiki/Polish_notation">prefix notation</a>. A function takes the remainder of the program as input and returns a program as output (which gets passed as input to the leftward function).

				Prefix notation has the following advantages over postfix notation:
				-	Stack underflows are impossible.
				-	Prefix notation more closely models function composition. Instead of storing a data stack in memory, the %Om evaluator stores a composed partial function.
				-	The evaluator can read, parse and evaluate the input stream in a single pass, sending results to the output stream as soon as they are evaluated. This cannot be done with a postfix, stack-based language because any data on the stack must remain there as it may be needed by a function later.
				-	Functions can be optimized to only read into memory the data that is required; stack-based postfix languages have no knowledge of the function to apply until the data is already in memory, on the stack.
				-	Incoming data, such as events, become simple to handle at a language level: a program might evaluate to a function that acts as a state machine that processes any additional data appended to the program and transitions to a new state, ready to process new data.
				-	An integrated development environment can provide hints to the user about the data that is expected by a function.

			\subsubsection language__functions__evaluation__ Evaluation
				Only the <em>terms</em> (operators and operands) of a program are significant to functions: separators are discarded from input, and are inserted between output terms in a "normalized" form (for consistent formatting and proper operator separation).

				There are three fundamental types of functions:
				-	<b>Identity:</b> A function whose output program contains all the terms in the input program.
				-	<b>Constant:</b> A function whose output program contains a term, defined by the function, followed by all terms in the input program.
				-	<b>Operation:</b> A function that is named by an operator and defines a computation. An operation processes operands at the front of the input program as data for the computation, and pushes any terms generated by the computation onto the output program, until one of two things happens:
					-	If the computation is completed, the rest of the input terms are pushed onto the output program.
					-	If the computation cannot be completed (due to insufficient operands), the operator that names the operation is pushed onto the output program, followed by all remaining input terms.

				Programs are evaluated as functions in the following way:
				-	The <b>empty program</b> evaluates to the identity function.
				-	Programs that contain only a <b>single element</b> evaluate to functions as follows:
					-	<b>Separator:</b> Evaluates to the identity function.
					-	<b>Operand:</b> Evaluates to a constant function that pushes the operand, followed by all input terms, onto the output program.
					-	<b>Operator:</b> Evaluates to the operation defined for the operator in the environment. If none, evaluates to a constant function that pushes the operator, followed by all input terms, onto the output program.
				-	Programs that contain <b>multiple elements</b> can be considered a concatenation of sub-programs that each contain one of the elements. The concatenated program evaluates to the composition of the functions that each sub-program evaluates to.

				For example, program "A B" is the concatenation of programs "A", " ", and "B". The separator evaluates to the identity operation and can be disregarded. The programs "A" and "B" evaluate to functions which will be denoted as <tt>A</tt> and <tt>B</tt>, respectively. The input and output are handled by the composed function as follows:
				-	Function <tt>B</tt> receives the input, and its output becomes the input for function <tt>A</tt>.
				-	Function <tt>A</tt> receives the input, and its output becomes that of the composed function.

				Any programs may be concatenated together; however, note that concatenating programs "A" and "B" without an intervening separator would result in a program containing a single operator "AB", which is unrelated to operators "A" or "B".

			\subsubsection language__functions__operations__ Operations
				All operation implementations provided are documented in the \ref om__operation__ module.

		\subsection language__data__ Data
			There are no traditional data types in the %Om language: every data value is represented by an operand.

			\subsubsection language__data__panmorphism__ Panmorphism
				The %Om language uses a unique <em>panmorphic</em> type system, from Ancient Greek πᾶν (pan, "all") and μορφή (morphē, “form”), in which all data values are exposed exclusively through a common immutable interface.

				In the case of the %Om language, every data value is entirely represented in the language as an operand. Any operation will accept any operand as a valid input and interrogate its data solely through its contained program (a sequence of operator, separator, and/or operand). The operation is then free to process the data however is appropriate, and any operand that it produces as output can then be interrogated and processed by the next operation in the same way.

			\subsubsection language__data__implementation__ Implementation
				Although any operand can be treated as containing a literal array of operand, operator and/or separator elements, the implementation of operands takes advantage of some optimizations:
				-	Each operand in memory actually contains one of several possible program implementations, each optimized for a specific set of operations. For example, some operations treat separators as insignificant; operands produced by these operations could contain a program implementation that stores only terms (operators and/or operands) and presents a "normalized" separator (such as a line separator) between each term.
				-	Operations can interrogate an input operand for its program implementation type; if it is the optimal implementation type for the operation, the operation can manipulate the operand directly to produce the same result more efficiently.

				Operations in a program can be ordered by the programmer to increase performance by minimizing conversions between program implementations, but it is not necessary for obtaining a correct computation. Where relevant, an operation will document the program implementation types of its inputs and outputs to allow for this optional level of optimization.

			\subsubsection language__data__programs__ Programs
				All program implementations provided are documented in the \ref om__program__ module.

		\subsection language__examples__ Examples
			The following program contains a single operand containing an operator &quot;<tt>Hello,</tt>&quot;, a separator &quot;<tt> </tt>&quot;, and another operator &quot;<tt>world!</tt>&quot;:
			<table>
				<tr><td><tt><b>{Hello, world!}</b></tt></td></tr>
				<tr><td><tt><em>{Hello, world!}</em></tt></td></tr>
			</table>

			The following program contains a single operand containing an operator &quot;<tt>Hello,</tt>&quot;, a separator &quot;<tt> </tt>&quot;, and an operand &quot;<tt>{universe!}</tt>&quot; which in turn contains a single operator &quot;<tt>universe!</tt>&quot;:
			<table>
				<tr><td><tt><b>{Hello, {universe!}}</b></tt></td></tr>
				<tr><td><tt><em>{Hello, {universe!}}</em></tt></td></tr>
			</table>

			Note that separators are significant inside operands:
			<table>
				<tr><td><tt><b>{Hello, &nbsp;&nbsp;world!}</b></tt></td></tr>
				<tr><td><tt><em>{Hello, &nbsp;&nbsp;world!}</em></tt></td></tr>
			</table>

			Operands can be dropped and copied via the \ref om__operation__drop_operation__ and \ref om__operation__copy_operation__ operations:
			<table>
				<tr><td><tt><b>drop {A}{B}{C}</b></tt></td></tr>
				<tr><td><tt><em>{B}{C}</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>copy {A}{B}{C}</b></tt></td></tr>
				<tr><td><tt><em>{A}{A}{B}{C}</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>drop copy {A}</b></tt></td></tr>
				<tr><td><tt><em>{A}</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>copy copy {A}</b></tt></td></tr>
				<tr><td><tt><em>{A}{A}{A}</em></tt></td></tr>
			</table>

			The \ref om__operation__drop_operation__ operation can therefore be used for comments:
			<table>
				<tr><td><tt><b>drop {This is a comment.} {This is not a comment.}</b></tt></td></tr>
				<tr><td><tt><em>{This is not a comment.}</em></tt></td></tr>
			</table>

			The \ref om__operation__choose_operation__ operation selects one of two operands, depending on whether a third is empty:
			<table>
				<tr><td><tt><b>choose {It was empty.}{It was non-empty.}{I am not empty.}</b></tt></td></tr>
				<tr><td><tt><em>{It was non-empty.}</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>choose {It was empty.}{It was non-empty.}{}</b></tt></td></tr>
				<tr><td><tt><em>{It was empty.}</em></tt></td></tr>
			</table>

			An operation without sufficient operands evaluates to itself and whatever operands are provided:
			<table>
				<tr><td><tt><b>drop</b></tt></td></tr>
				<tr><td><tt><em>drop</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>choose {It was empty.}{It was non-empty.}</b></tt></td></tr>
				<tr><td><tt><em>choose{It was empty.}{It was non-empty.}</em></tt></td></tr>
			</table>

			The \ref om__operation__quote_operation__ and \ref om__operation__dequote_operation__ operations add and remove a layer of operand braces, respectively:
			<table>
				<tr><td><tt><b>quote {B}</b></tt></td></tr>
				<tr><td><tt><em>{{B}}</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>dequote {{B}}</b></tt></td></tr>
				<tr><td><tt><em>{B}</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>dequote {copy}</b></tt></td></tr>
				<tr><td><tt><em>copy</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>dequote {copy} {A}</b></tt></td></tr>
				<tr><td><tt><em>{A}{A}</em></tt></td></tr>
			</table>

			Operands can be popped from and pushed into:
			<table>
				<tr><td><tt><b>&lt;-[characters] {ABC}</b></tt></td></tr>
				<tr><td><tt><em>{A}{BC}</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>-&gt;[literal] {A}{BC}</b></tt></td></tr>
				<tr><td><tt><em>{ABC}</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>&lt;-[terms] {some terms}</b></tt></td></tr>
				<tr><td><tt><em>{some}{terms}</em></tt></td></tr>
			</table>

			A new operator definition can be provided with the \ref om__operation__define_operation__ operation, where the first operand is treated as containing a \ref om__lexicon__ with operator-to-operand mappings, and the second operand contains the program to evaluate using the defined operator:
			<table>
				<tr><td><tt><b>define { double-quote {quote quote} } { double-quote {A} }</b></tt></td></tr>
				<tr><td><tt><em>{{{A}}}</em></tt></td></tr>
			</table>

			Any string can be used as an operator, with separators and operand braces escaped with a backquote:
			<table>
				<tr><td><tt><b>define { double` quote {quote quote} } { double` quote {A} }</b></tt></td></tr>
				<tr><td><tt><em>{{{A}}}</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>&lt;-[terms] { double` quote operator }</b></tt></td></tr>
				<tr><td><tt><em>{double` quote}{operator}</em></tt></td></tr>
			</table>

			Unicode is fully supported:
			<table>
				<tr><td><tt><b>&lt;-[characters] {한글}</b></tt></td></tr>
				<tr><td><tt><em>{한}{글}</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>&lt;-[code` points] {한글}</b></tt></td></tr>
				<tr><td><tt><em>{ᄒ}{ᅡᆫ글}</em></tt></td></tr>
			</table>
			<table>
				<tr><td><tt><b>&lt;-[terms] {한글 韓}</b></tt></td></tr>
				<tr><td><tt><em>{한글}{韓}</em></tt></td></tr>
			</table>

			Strings are automatically <a href="http://unicode.org/reports/tr15">normalized</a> to <a href="http://unicode.org/reports/tr15/#Norm_Forms">NFD</a>, but can be explicitly normalized to <a href="http://unicode.org/reports/tr15/#Norm_Forms">NFKD</a> using the \ref om__operation__normalize_operation__ operation:
			<table>
				<tr><td><tt><b>normalize {2⁵}</b></tt></td></tr>
				<tr><td><tt><em>{25}</em></tt></td></tr>
			</table>

			Recursion is very efficient in the %Om language, due to (a) the "eager" evaluation model enabled by prefix concatenative syntax (i.e. data is consumed immediately rather than being left on a stack), and (b) the non-recursive evaluation implementation in the evaluator that minimizes memory overhead of recursive calls and prevents stack overflow. The following example uses recursion to give the minutes in a colon-delimited 24-hour time string:
			<table>
				<tr>
					<td><tt><b>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ minutes {1:23} }<br/>
					</b></tt></td>
				</tr>
				<tr>
					<td><tt><em>{23}</em></tt></td>
				</tr>
			</table>

			An important feature of %Om is that each step of an evaluation can be represented as a program. The following is the above program broken down into evaluation steps, where the code that is about to be replaced is <b>bold</b>, and the latest replacement is <em>italicized</em>:
			<table>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ <b>minutes</b> {1:23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ <em>dequote choose {minutes} {} = {:} &lt;-[characters]</em> {1:23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote choose {minutes} {} = {:} <b>&lt;-[characters] {1:23}</b> }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote choose {minutes} {} = {:} <em>{1} {:23}</em> }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote choose {minutes} {} <b>= {:} {1}</b> {:23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote choose {minutes} {} <em>{}</em> {:23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote <b>choose {minutes} {} {}</b> {:23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote <em>{minutes}</em> {:23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ <b>dequote {minutes}</b> {:23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ <em>minutes</em> {:23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ <b>minutes</b> {:23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ <em>dequote choose {minutes} {} = {:} &lt;-[characters]</em> {:23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote choose {minutes} {} = {:} <b>&lt;-[characters] {:23}</b> }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote choose {minutes} {} = {:} <em>{:} {23}</em> }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote choose {minutes} {} <b>= {:} {:}</b> {23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote choose {minutes} {} <em>{{:}}</em> {23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote <b>choose {minutes} {} {{:}}</b> {23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ dequote <em>{}</em> {23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ <b>dequote {}</b> {23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ {23} }<br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt><b>define<br/>
					{ minutes { dequote choose {minutes} {} = {:} &lt;-[characters] } }<br/>
					{ {23} }</b><br/>
					</tt></td>
				</tr>
				<tr>
					<td><tt><em>{23}</em></tt></td>
				</tr>
			</table>

			The \ref om__operation__rearrange_operation__ operation provides operand name binding, allowing for a more applicative style. The following example is a simplistic implementation of a left <a href="http://en.wikipedia.org/wiki/Fold_(higher-order_function)">fold</a>, along with an example call:
			\code{.unparsed}
			define
			{
				[Fold]<- {
					rearrange
					{
						rearrange
						{
							dequote
							choose
							quote Result
							pair pair pair {[Fold]<-} Function Result Remainder
							Remainder
						}
						{Result Remainder}
						dequote Function Base <-[terms] Source
					}
					{Function Base Source}
				}
			}
			{
				[Fold]<- {[literal]<-} {} {1 2 3}
			}
			\endcode

			The result is <tt>{321}</tt>.

			The example works as follows:
			-	<tt>[Fold]&lt;-</tt> takes three operands:
				-	<tt>Function</tt>
				-	<tt>Base</tt>
				-	<tt>Source</tt>
			-	The first term is popped from the <tt>Source</tt>.
			-	The <tt>Function</tt> is applied to:
				-	the <tt>Base</tt>
				-	the popped first term of the <tt>Source</tt>
				-	the remainder of the <tt>Source</tt>
				-	the remainder of the input program
			-	The first two operands output by the <tt>Function</tt> are:
				-	<tt>Result</tt>
				-	<tt>Remainder</tt>
			-	If the <tt>Remainder</tt> is empty, the <tt>Result</tt> is output. Otherwise, <tt>Function</tt>, <tt>Result</tt>, and <tt>Remainder</tt> are passed to a recursive <tt>[Fold]&lt;-</tt> call.

			A few things should be noted about the above example:
			-	The \ref om__operation__ list is very short at the moment; as it expands, higher-level constructs should allow for simplification of algorithms such as this one.
			-	When reading %Om code, it can be difficult to mentally group operations with the operands they consume (contrasted with Scheme, in which they are grouped at design time with parentheses). However, it should be possible for an %Om integrated development environment to generate a graphical indication of these groupings dynamically.

	\section contributing__ Contributing
		There are several ways to contribute to the %Om project:
		-	By \ref contributing__developing__ new \ref om__operation__ and \ref om__program__ classes.
		-	By \ref contributing__reporting_issues__ via bugs, patches, or enhancement requests.
		-	By \ref contributing__funding__ further development of the %Om language.

		\subsection contributing__developing__ Developing
			%Om is written in modern, portable C++ that adheres to the <a href="http://sparist.github.io/cpp_coding_standard.html">Sparist C++ Coding Standard</a>.

			<b>Note:</b> Because this is an early-stage project, there are not yet any compatibility guarantees between versions.

			\subsubsection contributing__developing__forking__ Forking
				%Om code can be <a href="https://github.com/sparist/Om/fork">forked</a> from the <a href="https://github.com/sparist/Om">%Om GitHub repository</a>.

			\subsubsection contributing__developing__building__ Building
				See the \ref using__ section for instructions on building the code.

			\subsubsection contributing__developing__adding_or_removing_files Adding or Removing Files
				When adding or removing files from source, re-run the "generate" script from the build directory to update the project.

			\subsubsection contributing__developing__adding_operations__ Adding Operations
				Additional native functionality can be added to the %Om language by implementing new operations in C++.

				There are two ways to implement an operation: as a composite operation, or an atomic operation.

				To implement a composite operation, or an atomic operation that consumes no operands:
				-	Define the operation <tt>class</tt> in the <tt>Om::Language::Operation</tt> namespace.
				-	Define the static <tt>GetName()</tt> method, which returns a <tt>static char const *</tt> containing the name.
				-	Define the static <tt>Give(Om::Language::Evaluation &amp;)</tt> method, with no return value, to give existing operations and/or elements to the evaluation.

				To define an atomic operation that consumes one or more operands:
				-	Define the operation <tt>class</tt>, derived from <tt>Om::Language::Operation::DefaultIncompleteOperation</tt> (which has the operation <tt>class</tt> as its template argument), in the <tt>Om::Language::Operation</tt> namespace.
				-	Define the static <tt>GetName()</tt> method, which returns a <tt>static char const *</tt> containing the name.
				-	Implement the functions necessary to compile.
				-	Optionally override virtual function implementations in <tt>Om::Language::Operation::DefaultIncompleteOperation</tt> that may be more optimally implemented in the operation.

				For any operation implementation, code must be added to the operation header that inserts the operation into the system when the header is included, as follows (where <tt>WhateverOperation</tt> is a stand-in for the name of the operation <tt>class</tt>):

				\code
				namespace {

					static Om::Language::System::Definition<WhateverOperation> const theWhateverDefinition;

				}
				\endcode

			\subsubsection contributing__developing__adding_programs__ Adding Programs
				New data types can be added to the %Om language by extending <tt>Om::Language::Program</tt> and defining the functions necessary to instantiate the class. Use existing programs as a guide.

				Program types should be defined in the <tt>Om::Language</tt> namespace.

			\subsubsection contributing__developing__analyzing_code__ Analyzing Code
				Some basic free static analysis tools can be applied to the %Om code:
				-	<a href="https://github.com/terryyin/hfcca"><b>HFCCA</b></a> is a Python script that measures cyclomatic complexity and counts the number of lines of code in C++ source files, not including comments or tests. If Python is installed and in the path, HFCCA can be applied to %Om by entering the following at the terminal from inside the %Om directory:
					<blockquote><tt>python <em>[path]</em>/hfcca.py -p -v code</tt></blockquote>
				-	<a href="http://cloc.sourceforge.net"><b>CLOC</b></a> is a stand-alone Perl script that determines total line counts. If Perl is installed, CLOC can be applied to %Om by entering the following at the terminal from inside the %Om directory:
					<blockquote><tt><em>[path]</em>/cloc.pl code</tt></blockquote>

			\subsubsection contributing__developing__analyzing_tests__ Analyzing Test Coverage
				The Om.Test target of the Xcode project generates test coverage data that can be viewed as follows:
				-	Download and install <a href="http://code.google.com/p/coverstory/">CoverStory</a>. In Preferences, add <tt>"*.ipp"</tt> and <tt>"*.hpp"</tt> to the "SDK Files" list.
				-	Build and run the Om.Test target.
				-	In the CoverStory File menu, open the folder &quot;<em>[%Om build directory path]</em>/projects/Xcode/Om.build/<em>[configuration]</em>/Om.Test.build/Objects-normal/x86_64&quot;, where <em>[configuration]</em> is the build configuration (e.g. "Debug", "Release"). The main CoverStory window should be populated as follows:
					-	The left pane shows a list of %Om source files, each accompanied by a test coverage percentage.
					-	The right pane shows the contents of the currently selected source file, with each line annotated with the number of times it was executed.

			\subsubsection contributing__developing__submitting_changes__ Submitting Changes
				Changes can be submitted to %Om via <a href="https://github.com/sparist/Om/pull/new/master">pull request</a>.

		\subsection contributing__reporting_issues__ Reporting Issues
			Issues are reported and tracked with the <a href="https://github.com/sparist/Om/issues">Om GitHub issue tracker</a>.

			Before reporting an issue, please search existing issues first to ensure that it is not a duplicate.

		\subsection contributing__funding__ Funding
			The %Om language is currently a spare-time project of <a href="http://sparist.com">one person</a>. If you would like to speed the development of the %Om language in either a general or domain-specific direction, please contact me at <a href="mailto:information@sparist.com?subject=Om%20Funding">information@sparist.com</a>.

	\section language__references__ References and Thanks
		The following additional reading may help explain some of the concepts that contributed to the %Om language:
		-	<a href="http://evincarofautumn.blogspot.ca/2012/02/why-concatenative-programming-matters.html">Why Concatenative Programming Matters</a>
		-	The Concatenative <a href="http://concatenative.org">wiki</a>, <a href="http://tech.groups.yahoo.com/group/concatenative">mailing list</a>, and <a href="http://en.wikipedia.org/wiki/Concatenative_programming_language">Wikipedia entry</a>
		-	A <a href="http://www.kevinalbrecht.com/code/joy-mirror">mirror</a> of Manfred von Thun's original pages on the groundbreaking Joy Programming Language (<a href="http://en.wikipedia.org/wiki/Joy_(programming_language)">Wikipedia entry</a>), the father of all concatenative languages

		Thanks to all of the people who contributed to:
		-	The libraries and tools that the %Om implementation makes use of
		-	The technologies and ideas that %Om builds on
		-	%Om itself, in the form of bug reports, feedback, and encouragement

*/

#ifndef Om_Language_

	#define Om_Language_ \
	Om::Language

namespace Om {

	/*!
	\brief
		The Om language implementation.
	*/
	namespace Language {}

}

#endif
