/**
 * @defgroup utils EXIP utilities
 *
 * @brief Information on utility tools part of the exip library
 *
 * The folder /utils contains useful utility applications that are used as part of the EXIP library.
 * For example, createGrammars utility is used to generate static representation of
 * the EXI grammars. It is also used internally to provide grammar definitions for
 * the EXIOptions XML Schema document. 
 * 
 * @date Jul 19, 2011
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: README.txt 141 2012-06-20 12:21:18Z rumen $
 * 
 */

Note: exipg generator workflow

Location:
- utils/schemaHandling/exipg

Input contract:
- exipg consumes EXI-encoded XSD schema inputs (for example: *-xsd.exi files).
- Multiple schema files may be provided as a comma-separated list via -schema=.

Output modes (current state):
- -text: supported and validated.
- -static: supported and validated.
- -dynamic: currently not implemented (returns EXIP_NOT_IMPLEMENTED_YET).
- -exip: currently not implemented (returns EXIP_NOT_IMPLEMENTED_YET).

Determinism policy:
- Static output banner is deterministic (no wall-clock timestamp).
- Golden fixtures are maintained under tests/golden/exipg.

Golden test workflow:
- Configure/build: cmake --preset gcc-debug && cmake --build --preset gcc-debug --target exipg
- Run generator regression tests: ctest --preset gcc-debug -L golden

Current golden coverage:
- NonBlockingStreaming: -text, -static
- emptyType: -text, -static
- SenML: -text
