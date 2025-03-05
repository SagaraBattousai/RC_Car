set(ACCELEROMETER_MODULE_ROOT "${MODULE_ROOT}/accelerometer")

set(c_sources "accelerometer.c")
set(accelerometer_module
  "${ACCELEROMETER_MODULE_ROOT}/accelerometer.h"
  )

#add_library(accelerometer OBJECT ${c_sources})
add_library(accelerometer STATIC ${c_sources})

target_sources(accelerometer PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${accelerometer_module}
  )

# Private for now, depends on header
target_link_libraries(accelerometer PRIVATE hardware_i2c pico_time)#raspiccolo::i2c)
#target_link_libraries(accelerometer PUBLIC hardware_i2c pico_time)#raspiccolo::i2c)
