if(NOT DEFINED EXIPG OR NOT DEFINED MODE OR NOT DEFINED SCHEMA OR NOT DEFINED GOLDEN OR NOT DEFINED TMP)
    message(FATAL_ERROR "Required variables: EXIPG, MODE, SCHEMA, GOLDEN, TMP")
endif()

if(MODE STREQUAL "-static")
    if(NOT DEFINED PFX)
        message(FATAL_ERROR "PFX is required for -static mode")
    endif()
    execute_process(
        COMMAND "${EXIPG}" "${MODE}" "-pfx=${PFX}" "-schema=${SCHEMA}" "${TMP}"
        RESULT_VARIABLE EXIPG_RESULT)
else()
    execute_process(
        COMMAND "${EXIPG}" "${MODE}" "-schema=${SCHEMA}" "${TMP}"
        RESULT_VARIABLE EXIPG_RESULT)
endif()

if(NOT EXIPG_RESULT EQUAL 0)
    message(FATAL_ERROR "exipg failed with exit code ${EXIPG_RESULT} for schema ${SCHEMA}")
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E compare_files "${GOLDEN}" "${TMP}"
    RESULT_VARIABLE DIFF_RESULT)

if(NOT DIFF_RESULT EQUAL 0)
    message(FATAL_ERROR "Golden mismatch: ${TMP} differs from ${GOLDEN}")
endif()
