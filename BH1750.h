#ifndef BH1750_H
#define BH1750_H


/* This address can be changed to the 0x5C, if that necessary */
#define BH1750_ADDR                    0x23

#define RPI_I2C_BUS                    1

#define POWER_DOWN                     0x00
#define POWER_UP                       0x01
#define RESET                          0x07

#define CONTINUOUS_LOW_RES             0x13
#define CONTINUOUS_HIGH_RES_1          0x10
#define CONTINUOUS_HIGH_RES_2          0x11

#define ONE_TIME_LOW_RES               0x23
#define ONE_TIME_HIGH_RES_1            0x20
#define ONE_TIME_HIGH_RES_2            0x21

#define ONE_TIME_LOW_RES_DELAY_S       0.018
#define ONE_TIME_HIGH_RES_1_DELAY_S    0.14
#define ONE_TIME_HIGH_RES_2_DELAY_S    0.14

#define EXIT_FAILURE_GPIOD_INIT        2
#define EXIT_FAILURE_RPI_I2C           3
#define EXIT_FAILURE_I2C_RW            4


static uint16_t BH1750_lux(int pi, int bh1750_handle);
static uint16_t BH1750_lux_fast(int pi, int bh1750_handle);
static void release(int pi, int bh1750_handle);


#endif
