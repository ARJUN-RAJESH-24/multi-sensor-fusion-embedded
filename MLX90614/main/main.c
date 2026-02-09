#include "driver/i2c.h"
#include "esp_log.h"
#include "freertos.h/FreeRTOS.h"
#include "freertos/task.h"

#define I2C_MASTER_NUM  I2C_NUM_0
#define I2C_MASTER_SDA_IO 21
#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_FREQ 100000

#define MLX90614_ADDR 0x5A
#define MLX90614_TA_REG 0x06 //ambient temp
#define MLX90614_TOBJ1_REG 0x07// obj temp

static void i2c_master_init(void){
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,// date
        .scl_io_num = I2C_MASTER_SCL_IO,//clock
        .sda_pullup_en = GPIO_PULLUP_ENABLE, //enabled
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ,
    };
    i2c_param_config(I2C_MASTER_NUM,&conf);
    i2c_driver_install(I2C_MASTER_NUM,conf.mode,0,0,0);
}