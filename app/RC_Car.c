#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include <hardware/i2c.h>
#include <hardware/gpio.h>
//#include "hardware/spi.h"

#include <accelerometer/accelerometer.h>

extern char __heap_start;
//char* __heap_start = (char*)0x20000000;

extern char _end;
extern char __end__;

int main()
{
    stdio_init_all();

    char* heap_end_ptr = &_end;

    char* dummy = (char*) malloc(0x8);

    if (dummy == NULL)
    {
        panic("UMMMM\n");
    }


    i2c_init(i2c_default, 400 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    reset_accelerometer(i2c_default);

    uint16_t acc_data[3];

    while (true) {
        read_raw(i2c_default, acc_data);
        printf("Raw Acceleration: X = %d, Y = %d, Z = %d\n", acc_data[0], acc_data[1], acc_data[2]);
        printf("Acceleration: X = %f, Y = %f, Z = %f\n", ((float)(acc_data[0]))/16384, ((float)(acc_data[1]))/16384, ((float)(acc_data[2]))/16384);
        sleep_ms(100);

        printf("__heap_start = %x\n", __heap_start);
        printf("ADDR(__heap_start) = %x\n", &__heap_start);

        printf("_end = %x\n", _end);
        printf("deref of heap_end_ptr = %x\n", *heap_end_ptr);
        printf("ADDR(_end) = %x\n", &_end);

        printf("__end__ = %x\n", __end__);
        printf("ADDR(__end__) = %x\n", &__end__);
    }
}
