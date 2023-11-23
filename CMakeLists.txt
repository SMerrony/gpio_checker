cmake_minimum_required(VERSION 3.22)

# Pull in Raspberry Pi Pico SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set (PROJECT gpio_checker)

add_executable(${PROJECT} 
  src/${PROJECT}.c
)

set(PICO_BOARD pico CACHE STRING "Board type")

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.5.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.5.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(${PROJECT} C CXX ASM)

pico_sdk_init()

pico_set_program_name(${PROJECT} "${PROJECT}")
pico_set_program_version(${PROJECT} "0.0.1")

# pull in common dependencies
target_link_libraries(${PROJECT} 
  pico_stdlib
)

target_compile_options(${PROJECT} PRIVATE -Werror -Wall -Wextra)

pico_enable_stdio_usb(${PROJECT} 1) # STDIO to USB

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT})
