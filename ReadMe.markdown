# Om

<a href="http://om-language.org">Om</a> is an experimental high-level programming language with the goal of maximal simplicity.

See the <a href="http://sparist.github.com/Om">Om documentation</a> for more information.

Changes for each released version are listed below.

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
