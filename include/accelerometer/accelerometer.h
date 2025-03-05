#ifndef __RC_CAR_ACCELERATION_H__
#define __RC_CAR_ACCELERATION_H__

// As done in something like pico/binary_info/structure ....
#ifndef __packed
#define __packed __attribute__((packed))
#endif

#include <stdint.h>

//forward declare i2c_inst_t so we dont have to include 
// hardware/i2c.h in this header
typedef struct i2c_inst i2c_inst_t;

typedef struct accelerometer {
    i2c_inst_t *i2c;
    uint8_t address;
} accelerometer_t;

// Shouldn't need __attribute__((packed))!? but ... better to be safe for making equivilent to uint16_t[3]
// and pico sdk does it for us with __packed :D so ... 
typedef struct __packed acceleration_raw {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} acceleration_raw_t;

void reset_accelerometer(i2c_inst_t *i2c);

void read_raw(i2c_inst_t *i2c, int16_t acceleration_data[3]);

//void write_

#endif