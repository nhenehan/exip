# Encode/decode smoke test without a schema:
#   cmake -DEXIPE=<exipe> -DEXIPD=<exipd> -DWORK=<dir> [-DEMULATOR=<cmd>] -P smoke-roundtrip.cmake
# exipe writes its built-in test document; exipd must decode it back to XML.
foreach(_v EXIPE EXIPD WORK)
  if(NOT DEFINED ${_v})
    message(FATAL_ERROR "${_v} is required")
  endif()
endforeach()

file(MAKE_DIRECTORY "${WORK}")
set(_exi "${WORK}/smoke-roundtrip.exi")
file(REMOVE "${_exi}")

execute_process(COMMAND ${EMULATOR} "${EXIPE}" "${_exi}"
  RESULT_VARIABLE _rc OUTPUT_VARIABLE _out ERROR_VARIABLE _err)
if(NOT _rc EQUAL 0 OR NOT EXISTS "${_exi}")
  message(FATAL_ERROR "exipe failed (${_rc}): ${_out}${_err}")
endif()

execute_process(COMMAND ${EMULATOR} "${EXIPD}" -xml "${_exi}"
  RESULT_VARIABLE _rc OUTPUT_VARIABLE _xml ERROR_VARIABLE _err)
if(NOT _rc EQUAL 0)
  message(FATAL_ERROR "exipd failed (${_rc}): ${_xml}${_err}")
endif()

set(_expected "<p0:EXIPEncoder testByte=\"55\" version=\"0.2\">This is an example of serializing EXI streams using EXIP low level API</p0:EXIPEncoder>")
string(FIND "${_xml}" "${_expected}" _pos)
if(_pos LESS 0)
  message(FATAL_ERROR "exipd output lacks the encoded element:\n${_xml}")
endif()
message(STATUS "round trip passed")
