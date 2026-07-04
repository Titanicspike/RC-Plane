

# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.3.0)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(RC-Plane C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Transmitter Transmitter.cpp)

pico_set_program_name(Transmitter "Transmitter")
pico_set_program_version(Transmitter "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Transmitter 0)
pico_enable_stdio_usb(Transmitter 1)

include(lib/RF24/CMakeLists.txt)

# Add the standard library to the build
target_link_libraries(Transmitter
        pico_stdlib
        hardware_spi
        )

# Add the standard include files to the build
target_include_directories(Transmitter PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(Transmitter 
        RF24
        )

pico_add_extra_outputs(Transmitter)

# Add another executable
# ===========================
add_executable(Receiver Receiver.cpp)

pico_set_program_name(Receiver "Receiver")
pico_set_program_version(Receiver "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Receiver 1)
pico_enable_stdio_usb(Receiver 0)

# Add the standard library to the build
target_link_libraries(Receiver
        pico_stdlib
        hardware_spi
        )

# Add the standard include files to the build
target_include_directories(Receiver PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(Receiver 
        RF24
        )

pico_add_extra_outputs(Receiver)