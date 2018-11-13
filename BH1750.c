#include <stdio.h>
#include <stdlib.h>
#include <pigpiod_if2.h>
#include "BH1750.h"

static uint16_t BH1750_lux(int pi, int bh1750_handle)
{
    char buf[2];
    uint16_t raw_lux=0;

    i2c_write_byte(pi, bh1750_handle, ONE_TIME_HIGH_RES_1);
    time_sleep(ONE_TIME_HIGH_RES_1_DELAY_S);
    i2c_read_device(pi, bh1750_handle, buf, 2);

    raw_lux |= buf[0];
    raw_lux <<= 8;
    raw_lux |= buf[1];

    return (uint16_t) (raw_lux/1.2);
}

static uint16_t BH1750_lux_fast(int pi, int bh1750_handle)
{
    char buf[2];
    uint16_t raw_lux = 0;

    i2c_write_byte(pi, bh1750_handle, ONE_TIME_LOW_RES);
    time_sleep(ONE_TIME_LOW_RES_DELAY_S);
    i2c_read_device(pi, bh1750_handle, buf, 2);

    raw_lux |= buf[0];
    raw_lux <<= 8;
    raw_lux |= buf[1];

    return (uint16_t) (raw_lux/1.2);
}

static void release(int pi, int bh1750_handle)
{
    if (bh1750_handle>=0)
    {
        i2c_close(pi, bh1750_handle);
    }

    if (pi>=0)
    {
        pigpio_stop(pi);
    }
}

int main(int argc, char **argv)
{
    int bh1750_handle;
    int pi;
    uint16_t lux;

    pi = pigpio_start(NULL, NULL);
    if (pi<0)
    {
        return EXIT_FAILURE_GPIOD_INIT;
    }

    bh1750_handle = i2c_open(pi, RPI_I2C_BUS, BH1750_ADDR, 0);
    if (bh1750_handle<0)
    {
        release(pi, bh1750_handle);
        return EXIT_FAILURE_RPI_I2C;
    }

    if (i2c_write_byte(pi, bh1750_handle, POWER_UP))
    {
        release(pi, bh1750_handle);
        return EXIT_FAILURE_I2C_RW;
    }
    time_sleep(0.02);

    if (argc==2)
    {
        if ((argv[1][0]=='-') && (argv[1][1]=='f'))
        {
            lux = BH1750_lux_fast(pi, bh1750_handle);
        }
        else
        {
            lux = BH1750_lux(pi, bh1750_handle);
        }
    }
    else
    {
        lux = BH1750_lux(pi, bh1750_handle);
    }

    printf("Luminosity: %d lux\n", lux);

    release(pi, bh1750_handle);
    return EXIT_SUCCESS;
}
