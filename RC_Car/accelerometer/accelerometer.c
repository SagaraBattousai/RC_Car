
#include <accelerometer/accelerometer.h>

#include <hardware/i2c.h>
#include <pico/time.h>

static const int ACCELEROMETER_ADDR = 0x68;





typedef struct accelerometer {
    i2c_inst_t *i2c;
    uint8_t address;
} accelerometer_t;



void reset_accelerometer(i2c_inst_t *i2c) {
    uint8_t buf[] = {0x6B, 0x80};

    i2c_write_blocking(i2c, ACCELEROMETER_ADDR, buf, 2, false);
    sleep_ms(100);

    buf[1] = 0x00;

    i2c_write_blocking(i2c, ACCELEROMETER_ADDR, buf, 2, false);
    sleep_ms(10);

}

void read_raw(i2c_inst_t *i2c, int16_t acceleration_data[3]) {

    uint8_t buf[6];

    uint8_t acc_reg_addr = 0x3B;
    i2c_write_blocking(i2c, ACCELEROMETER_ADDR, &acc_reg_addr, 1, true);

    i2c_read_blocking(i2c, ACCELEROMETER_ADDR, buf, 6, false);

    for (int i = 0; i < 3; ++i) {
        acceleration_data[i] = (buf[i * 2] << 8 | buf[(i * 2) + 1]);
    }

}



