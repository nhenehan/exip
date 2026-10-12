# Bare-metal ARM Cortex-M (GNU Arm Embedded, arm-none-eabi-gcc): builds the exip libraries
# only (no OS: tools, examples and tests are off by default).
#
#   cmake -S . -B build-arm -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/arm-none-eabi.cmake \
#         -DEXIP_CFG_PRESET=small -DCMAKE_BUILD_TYPE=MinSizeRel
#   cmake --build build-arm --target size_report
#
# EXIP_ARM_CPU_FLAGS selects the core (default Cortex-M4, Thumb, soft float ABI); the
# libraries are compiled with one section per function and data item, so a firmware linked
# with --gc-sections keeps only what it uses.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX arm-none-eabi-)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(EXIP_SIZE_TOOL ${TOOLCHAIN_PREFIX}size)

# No OS to link a test program against during compiler checks
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(EXIP_ARM_CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=soft" CACHE STRING
    "arm-none-eabi CPU flags (e.g. -mcpu=cortex-m0plus -mthumb, -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard)")
set(CMAKE_C_FLAGS_INIT "${EXIP_ARM_CPU_FLAGS} -ffunction-sections -fdata-sections")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,--gc-sections --specs=nano.specs --specs=nosys.specs")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
