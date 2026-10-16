# The tools must take file names and options of any length.
#   cmake -DEXIPE=<exipe> -DEXIPD=<exipd> -DEXIPG=<exipg> -DSCHEMA=<a-xsd.exi> -DWORK=<dir>
#         -P tools-long-arguments.cmake
# exipe and exipd used to copy the file name and each -schema= file into 500-byte
# stack buffers, and exipg the -pfx= prefix into 20 bytes, with strcpy. A longer
# argument overwrote the stack: a crash, not an error message.
foreach(_v EXIPE EXIPD EXIPG SCHEMA WORK)
  if(NOT DEFINED ${_v})
    message(FATAL_ERROR "${_v} is required")
  endif()
endforeach()

# A real directory whose path is longer than 500 bytes (each name stays below 255)
string(REPEAT "d" 150 _name)
set(_dir "${WORK}/${_name}/${_name}/${_name}/${_name}")
file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${_dir}")
file(COPY "${SCHEMA}" DESTINATION "${_dir}")
get_filename_component(_schema_name "${SCHEMA}" NAME)
set(_schema "${_dir}/${_schema_name}")
set(_exi "${_dir}/out.exi")

# Runs a tool and fails the test if it was killed by a signal or did not exit with
# one of the allowed codes; the output goes to _out
function(run_tool what allowed)
  execute_process(COMMAND ${ARGN} RESULT_VARIABLE _rc OUTPUT_VARIABLE _o ERROR_VARIABLE _e)
  if(NOT _rc MATCHES "^(${allowed})$")
    message(FATAL_ERROR "${what}: exit '${_rc}', expected ${allowed}\n${_o}${_e}")
  endif()
  set(_out "${_o}${_e}" PARENT_SCOPE)
endfunction()

run_tool("exipe, long output file name" "0" "${EXIPE}" "${_exi}")
run_tool("exipd, long input file name" "0" "${EXIPD}" -xml "${_exi}")
if(NOT _out MATCHES "This is an example of serializing EXI streams")
  message(FATAL_ERROR "exipd did not decode the stream:\n${_out}")
endif()

# The schema does not fit the built-in example, so the run may end with an error
# (exit 1); it must still read the schema file and not crash
run_tool("exipe, long -schema= file name" "0|1" "${EXIPE}" "-schema=${_schema}" "${_dir}/schema-out.exi")
run_tool("exipd, long -schema= file name" "0|1" "${EXIPD}" -xml "-schema=${_schema}" "${_exi}")
if(_out MATCHES "Unable to open file")
  message(FATAL_ERROR "exipd did not open the schema file:\n${_out}")
endif()

string(REPEAT "p" 40 _pfx)
run_tool("exipg, long -pfx=" "1" "${EXIPG}" -static "-pfx=${_pfx}" "-schema=${SCHEMA}" "${_dir}/out.c")
if(NOT _out MATCHES "prefix")
  message(FATAL_ERROR "exipg gave no message about the prefix:\n${_out}")
endif()
file(REMOVE_RECURSE "${WORK}")
message(STATUS "long arguments passed")
