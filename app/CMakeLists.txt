

add_executable(RC_Car RC_Car.c )

pico_set_program_name(RC_Car "RC_Car")
pico_set_program_version(RC_Car "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(RC_Car 1)
pico_enable_stdio_usb(RC_Car 1)


FetchContent_MakeAvailable(raspiccolo)


# Add the standard library to the build
target_link_libraries(RC_Car
        pico_stdlib raspiccolo::pwm accelerometer hardware_i2c hardware_gpio)

# Add the standard include files to the build
target_include_directories(RC_Car PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
#target_link_libraries(RC_Car 
        #hardware_spi
        #hardware_i2c
        #)

pico_add_extra_outputs(RC_Car)

# Can't work out how to tell vs code to look in subdir for 
# elf and cannot waste any more time!!

set_target_properties(RC_Car PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

###############################################################################
###### CUSTOM LINKER SCRIPT IS IGNORED FOR NOW! 
## A) Don't really want to rewrite the whole thing 
##### (wouldn't be so bad if we could just add stuff in a second script.)
#
## B) I guess I don't fully understand .Heap as it has no "size" and grows
##### dynamically.
#
## C) The Heap can overtake the stack anyway so lets just stick our custom 
##### part at the end of the Heap
###############################################################################

# set(LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/custom_malloc.ld")
# set(LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/memmap_custom_malloc.ld")
# set_target_properties(RC_Car PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
# target_link_options(RC_Car PUBLIC "LINKER:-T,${LINKER_SCRIPT}")
# target_link_options(RC_Car PUBLIC "LINKER:SHELL:-T ${LINKER_SCRIPT}")
# pico_add_link_depend(RC_Car ${LINKER_SCRIPT})
# pico_set_linker_script(RC_Car ${LINKER_SCRIPT})
