# Windows build artifact check: cmake -DEXIP_ARTIFACTS=<exe;exe...> -P verify-windows-artifacts.cmake
# Each artifact must exist, be named *.exe and start with the "MZ" executable header. Used by
# cross builds that cannot run the programs (mingw-w64 on Linux) and by native Windows builds.
if(NOT DEFINED EXIP_ARTIFACTS)
  message(FATAL_ERROR "EXIP_ARTIFACTS is required")
endif()

foreach(_bin IN LISTS EXIP_ARTIFACTS)
  if(NOT EXISTS "${_bin}")
    message(FATAL_ERROR "Missing Windows artifact: ${_bin}")
  endif()
  if(NOT _bin MATCHES "\\.exe$")
    message(FATAL_ERROR "Not a Windows executable name: ${_bin}")
  endif()
  file(READ "${_bin}" _magic LIMIT 2 HEX)
  if(NOT _magic STREQUAL "4d5a")
    message(FATAL_ERROR "No MZ header in ${_bin}")
  endif()
endforeach()

message(STATUS "Windows artifact check passed")
