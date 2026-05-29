if(NOT DEFINED EXIP_BUILD_DIR)
  message(FATAL_ERROR "EXIP_BUILD_DIR is required")
endif()

set(_required_bins
  "${EXIP_BUILD_DIR}/examples/simpleEncoding/exipe.exe"
  "${EXIP_BUILD_DIR}/examples/simpleDecoding/exipd.exe"
  "${EXIP_BUILD_DIR}/utils/schemaHandling/exipg.exe"
)

foreach(_bin IN LISTS _required_bins)
  if(NOT EXISTS "${_bin}")
    message(FATAL_ERROR "Missing mingw artifact: ${_bin}")
  endif()
endforeach()

message(STATUS "mingw artifact smoke check passed")
