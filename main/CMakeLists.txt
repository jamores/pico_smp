cmake_minimum_required(VERSION 3.13)

#set(ENV{PICO_SDK_PATH} "/home/jamor3s/work/10_home/05_pico/pico_sdk")
set(ENV{PICO_SDK_PATH} "../../pico-sdk")
set(ENV{FREERTOS_KERNEL_PATH} "../../FreeRTOS-Kernel")

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico_sdk_import.cmake)
include(FreeRTOS_Kernel_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(main
    main.c
    FreeRTOSConfig.h
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main pico_stdlib pico_multicore FreeRTOS-Kernel FreeRTOS-Kernel-Heap4)

# serial to USB
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)

# TODO (refactor properly) : add current directory to include paths so FreeRTOSConfig.h can be found
target_include_directories(main PRIVATE .)

