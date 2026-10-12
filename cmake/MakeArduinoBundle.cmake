# Arduino library bundle:
#   cmake -DSOURCE_DIR=<exip> -DOUT_DIR=<dir> -DVERSION=<x.y.z> -P MakeArduinoBundle.cmake
# writes <OUT_DIR>/exip/ in the Arduino library format: library.properties, a flat src/
# (the Arduino IDE only searches src/ for "..." includes) with the public headers and the
# common, streamIO, contentIO and grammar modules, examples/ and the license. grammarGen
# (schema loading at run time) is not included: generate static grammars with exipg instead.
# exipConfig.h selects exip_arduino_config.h by itself when ARDUINO is defined.
foreach(_v SOURCE_DIR OUT_DIR VERSION)
    if(NOT DEFINED ${_v})
        message(FATAL_ERROR "${_v} is required")
    endif()
endforeach()

set(_lib "${OUT_DIR}/exip")
file(REMOVE_RECURSE "${_lib}")
file(MAKE_DIRECTORY "${_lib}/src" "${_lib}/examples")

set(_modules common streamIO contentIO grammar)
file(GLOB _files "${SOURCE_DIR}/include/*.h")
list(FILTER _files EXCLUDE REGEX "/grammarGenerator\\.h$")
foreach(_m IN LISTS _modules)
    file(GLOB _h "${SOURCE_DIR}/src/${_m}/include/*.h")
    file(GLOB _c "${SOURCE_DIR}/src/${_m}/src/*.c")
    list(APPEND _files ${_h} ${_c})
endforeach()

# flat src/: two files with one name would overwrite each other
set(_names)
foreach(_f IN LISTS _files)
    get_filename_component(_n "${_f}" NAME)
    list(FIND _names "${_n}" _dup)
    if(NOT _dup EQUAL -1)
        message(FATAL_ERROR "Arduino bundle: two sources are named ${_n}")
    endif()
    list(APPEND _names "${_n}")
    file(COPY "${_f}" DESTINATION "${_lib}/src")
endforeach()

file(GLOB _examples LIST_DIRECTORIES true "${SOURCE_DIR}/examples/arduino/*")
foreach(_e IN LISTS _examples)
    if(IS_DIRECTORY "${_e}")
        file(COPY "${_e}" DESTINATION "${_lib}/examples")
    endif()
endforeach()
file(COPY "${SOURCE_DIR}/LICENSE.txt" DESTINATION "${_lib}")

file(WRITE "${_lib}/library.properties"
"name=exip
version=${VERSION}
author=Rumen Kyusakov and the exip contributors
maintainer=nhenehan <https://github.com/nhenehan/exip>
sentence=Efficient XML Interchange (EXI) encoder and decoder in C.
paragraph=Schema-less and schema-informed W3C EXI encoding and decoding with a small footprint, for 32-bit ARM and ESP32 boards. In C++ the API is in namespace exip.
category=Data Processing
url=https://github.com/nhenehan/exip
architectures=sam,samd,mbed_nano,mbed_rp2040,rp2040,esp32
includes=exip.h
")

list(LENGTH _names _count)
message(STATUS "Arduino library bundle: ${_lib} (${_count} files in src/)")
