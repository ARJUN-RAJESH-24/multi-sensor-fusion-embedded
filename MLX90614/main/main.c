#include "driver/i2c.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define I2C_MASTER_NUM        I2C_NUM_0
#define I2C_MASTER_SDA_IO     21
#define I2C_MASTER_SCL_IO     22
#define I2C_MASTER_FREQ       100000

#define MLX90614_ADDR         0x5A
#define MLX90614_TA_REG       0x06
#define MLX90614_TOBJ1_REG    0x07

static const char *TAG = "MLX90614";

static void i2c_master_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ,
    };

    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

static esp_err_t mlx90614_read_reg(uint8_t reg, uint16_t *data)
{
    uint8_t rx_buf[3];
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MLX90614_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg, true);

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MLX90614_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, rx_buf, 3, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(
        I2C_MASTER_NUM,
        cmd,
        pdMS_TO_TICKS(100)
    );

    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK)
        return ret;

    *data = ((uint16_t)rx_buf[1] << 8) | rx_buf[0];
    return ESP_OK;
}

static float mlx90614_raw_to_celsius(uint16_t raw)
{
    return (raw * 0.02f) - 273.15f;
}

static float mlx90614_get_ambient(void)
{
    uint16_t raw;
    if (mlx90614_read_reg(MLX90614_TA_REG, &raw) != ESP_OK)
        return -1000.0f;
    return mlx90614_raw_to_celsius(raw);
}

static float mlx90614_get_object(void)
{
    uint16_t raw;
    if (mlx90614_read_reg(MLX90614_TOBJ1_REG, &raw) != ESP_OK)
        return -1000.0f;
    return mlx90614_raw_to_celsius(raw);
}

void app_main(void)
{
    i2c_master_init();
    ESP_LOGI(TAG, "MLX90614 initialized");

    while (1) {
        float ambient = mlx90614_get_ambient();
        float object  = mlx90614_get_object();

        ESP_LOGI(
            TAG,
            "Ambient: %.2f °C | Object: %.2f °C",
            ambient,
            object
        );

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
