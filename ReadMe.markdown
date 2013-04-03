# Om

<a href="http://om-language.org">Om</a> is an experimental high-level programming language with the goal of maximal simplicity.

See the <a href="http://sparist.github.com/Om">documentation</a> for more information.

Changes for each released version are listed below.

## 0.1.3 (In development)

-	Refactored build, and file layout, with continuous integration in mind. The following can now be done with provided scripts:
	-	Download and build dependencies, then generate the Om project.
	-	Generate the Om project using existing dependency builds.
	-	Download and build dependencies only.
-	Updated ICU4C to 51.1.
-	Removed Boost Chrono library dependency.
-	Added test coverage detection and made minor test coverage improvements.
-	Refactored:
	-	Improved equality operator implementations.
	-	Replaced Queue class with Producer and Consumer classes.
-	Improved documentation.
-	Improved coding style.
-	In project, moved "dox" files into Om.Documentation target folder.

## 0.1.2

### Operations

-	Added:
	-	`pair`

### Documentation

-	Added more examples (#13).
-	Improved general readability and organization.
-	Better separated "C++ library" and "language"; the latter is in its own "Language" section.
-	Removed search field, which didn't work on iPad.
-	Added XML documentation generation, which can be used for "documentation metadata" (e.g. for IDE).

### Testing

-	Switched from UnitTest++ to the Boost Unit Test library.
-	Added CMake test that runs the unit tests.

### Versions

-	Updated Doxygen to 1.8.3.1.
-	Updated Graphviz to 2.30.1.
-	Updated Boost to 1.53.0, which addresses a <a href="http://www.boost.org/users/news/boost_locale_security_notice.html">security issue</a>.
-	Updated ICU to 50.1.2.

### Build

-	Split external building into separate "premake" scripts.
-	Added better argument checks to scripts.
-	Changed Windows scripts to statically build ICU via Cygwin.
-	Reorganized products folder.
-	Added "setlocal" to Windows scripts to prevent non-local environment modifications.

### General

-	Made fixes to Lexicon (#20, #21).
-	Made om.hpp an "umbrella" header, populated automatically by CMake, which contains all Om headers (#18).
-	Moved user documentation into ".dox" files, since these can contain non-ASCII UTF-8 characters (vs. C++ files, which should only contain ASCII).
-	Made changes to the coding standard:
	-	Removed line width restriction, and made changes to ensure readability when soft-wrapping.
	-	Replaced `struct` with `class`, reserving the former for C-style POD types.
	-	Made stylistic changes for consistency and readability.
-	Improved Doxygen naming convention to prevent conflicts with Doxygen-generated pages.
-	Refactored code.

## 0.1.1

### Operations

-	Added:
	-	`system`
	-	`environment`
	-	`elements->operand`
	-	`elements->operator`
	-	`elements->separator`
	-	`operand<-elements`
	-	`operator<-elements`
	-	`separator<-elements`
	-	`separator`
	-	`operand`
	-	`define`
-	Removed:
	-	`scope`
-	Renamed:
	-	`<-codepoints` to ``<-code` points``
	-	`codepoints->` to ``code` points->``
-	Modified:
	-	`evaluate`: now evaluates in place using the current environment
	-	`find`: now provides information about whether the operator is included, and the output is reordered for ease of use

### Programs

-	Fixed Operand program semantics so that an "empty" Operand is an empty Program.

### Documentation

-	Made documentation content and style improvements.
-	Removed temporary generated documentation file on Windows.
-	Created "gh-pages" branch containing generated Doxygen for the documentation.
-	Updated Doxygen to 1.8.3.

### Testing

-	Improved unit test coverage.

### General

-	Removed recursion that was not statically bounded (#2).
-	Moved roadmap to issue tracker (#3).
-	Improved comments.
-	Improved GCC build.
-	Renamed, refactored, and reorganized classes and files.
-	Tested with Boost 1.52.0 and updated build documentation.
-	Tested with ICU4C 50.1.1 and updated build documentation.

## 0.1

Initial release.
