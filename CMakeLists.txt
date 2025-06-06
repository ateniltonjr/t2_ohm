
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(t2_ohm C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(t2_ohm 
                t2_ohm.c # Principal
                # Pasta lib
                lib/ssd1306.c
                lib/matrixws.c)

pico_set_program_name(t2_ohm "t2_ohm")
pico_set_program_version(t2_ohm "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(t2_ohm 1)
pico_enable_stdio_usb(t2_ohm 1)

# Add the standard library to the build
target_link_libraries(t2_ohm
        pico_stdlib
        hardware_adc
        hardware_i2c
        hardware_pio)

# Add the standard include files to the build
target_include_directories(t2_ohm PRIVATE
        ${CMAKE_CURRENT_LIST_DIR})
        
# Add any user requested libraries
target_link_libraries(t2_ohm)
pico_add_extra_outputs(t2_ohm)