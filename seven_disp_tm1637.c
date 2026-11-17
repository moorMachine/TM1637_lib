#include "seven_disp_tm1637.h"
#include "esp_log.h"
#include "string.h"



int num_to_disp(uint8_t num)
{
    if (num == 0) return DISP_0;
    if (num == 1) return DISP_1;
    if (num == 2) return DISP_2;
    if (num == 3) return DISP_3;
    if (num == 4) return DISP_4;
    if (num == 5) return DISP_5;
    if (num == 6) return DISP_6;
    if (num == 7) return DISP_7;
    if (num == 8) return DISP_8;
    if (num == 9) return DISP_9;

    return -1;
}


static void seven_disp_delay(void)
{
    esp_rom_delay_us(5);
}

void seven_disp_start(struct seven_disp_tm1636* disp)
{
    gpio_set_level(disp->dio_pin, 1);
    gpio_set_level(disp->clk_pin, 1);

    seven_disp_delay();

    gpio_set_level(disp->dio_pin, 0);

    seven_disp_delay();

}

void seven_disp_stop(struct seven_disp_tm1636* disp)
{
    gpio_set_level(disp->clk_pin, 0);
    seven_disp_delay();

    gpio_set_level(disp->dio_pin, 0);
    seven_disp_delay();

    gpio_set_level(disp->clk_pin, 1);
    seven_disp_delay();

    gpio_set_level(disp->dio_pin, 1);
}

/**
 * send one byte to display
 */
void seven_disp_write_byte(struct seven_disp_tm1636* disp, uint8_t byte)
{
    for (int i = 0; i < 8; i ++)
    {
        gpio_set_level(disp->clk_pin, 0);
        gpio_set_level(disp->dio_pin, (byte >> i) & 1);
        seven_disp_delay();
        gpio_set_level(disp->clk_pin, 1);
        seven_disp_delay();

    }

    // Handle ack
    gpio_set_level(disp->clk_pin, 0);
    gpio_set_direction(disp->dio_pin, GPIO_MODE_INPUT);
    seven_disp_delay();
    gpio_set_level(disp->clk_pin, 1);
    seven_disp_delay();
    gpio_set_direction(disp->dio_pin, GPIO_MODE_OUTPUT);

}

// int seven_disp_update(struct seven_disp_tm1636* disp)
// {
//       if (disp == NULL)
//       {
//         ESP_LOGI("TEST", "Display Update invalid argument");
//         return -1;
//       }

//     static char data

// }
// int seven_disp_update(struct seven_disp_tm1636* disp)
// {
//     if (disp == NULL)
//     {
//         ESP_LOGI("TEST", "Display Update invalid argument");
//         return -1;
//     }

//     for (int i = 0; i < disp->data_len; i++)
//     {
//         seven_disp_set_data();
//     }
    

// }
int seven_disp_send_cmd(struct seven_disp_tm1636* disp, uint8_t cmd)
{
    if (disp == NULL)
    {
        ESP_LOGI("TEST", "Display send start invalid argument");
        return -1;
    }

    seven_disp_start(disp);
    seven_disp_write_byte(disp, cmd);
    seven_disp_stop(disp);

    return 1;
}

/** position -> 0xC0*/
int seven_disp_send_data(struct seven_disp_tm1636* disp, uint8_t position)
{
    if (disp == NULL)
    {
        ESP_LOGI("TEST", "Display Update invalid argument");
        return -1;
    }

    seven_disp_start(disp);
    seven_disp_write_byte(disp, position);
    seven_disp_stop(disp);


    for (int i = 0; i < disp->data_len; i++)
    {
        seven_disp_write_byte(disp, disp->data[i]);
        printf(" %d \r\n", i);
    }

    seven_disp_stop(disp);

    return 1;
}
int seven_disp_send_update(struct seven_disp_tm1636* disp)
{
     seven_disp_send_cmd(disp, 0x40);

    seven_disp_send_data_auto_inc(disp, 0xC0);

    seven_disp_send_cmd(disp, 0x88); 
    
    return 1;
}


int seven_disp_send_data_auto_inc(struct seven_disp_tm1636* disp, uint8_t position)
{
    if (disp == NULL)
    {
        ESP_LOGI("TEST", "Display Update invalid argument");
        return -1;
    }

    seven_disp_start(disp);
    seven_disp_write_byte(disp, position);

    for (int i = 0; i < disp->data_len; i++)
    {
        seven_disp_write_byte(disp, disp->data[i]);
    }

    seven_disp_stop(disp);

    return 1;
}


int seven_disp_set_data(struct seven_disp_tm1636* disp, uint8_t* data, uint8_t len)
{
    if (disp == NULL || data == NULL ||
        len == 0 || len > DISP_MAX_DATA_LENGTH)
    {
        //ESP_LOGI("TEST", "Display set data invalid argument");
        return -1;
    }
    
    memcpy(disp->data, data, len);
    disp->data_len = len;

    return 1;
}

int seven_disp_init(struct seven_disp_tm1636* disp, uint8_t dio_pin, uint8_t clk_pin)
{
    if (disp == NULL)
    {
        ESP_LOGI("TEST", "Display init invalid argument");
    }

    disp->dio_pin = dio_pin;
    disp->clk_pin = clk_pin;

    return 1;
}