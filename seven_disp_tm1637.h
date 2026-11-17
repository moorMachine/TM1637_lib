#include <stdint.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_rom_gpio.h"

#ifndef _SEVEN_DISP_TM1636_H_
#define _SEVEN_DISP_TM1636_H_

#define DISP_MAX_DATA_LENGTH 4 //16

#define AUTO_INC_MODE 0x40
#define START_POSITON 0xC0

struct seven_disp_tm1636 
{
    uint8_t clk_pin;
    uint8_t dio_pin;
    uint8_t data[DISP_MAX_DATA_LENGTH];
    uint8_t data_len;
};

enum disp_numb {
    DISP_0 = 0x3F,
    DISP_1 = 0x06,
    DISP_2 = 0x5B,
    DISP_3 = 0x4F,
    DISP_4 = 0x66,
    DISP_5 = 0x6D,
    DISP_6 = 0x7D,
    DISP_7 = 0x07,
    DISP_8 = 0x7F,
    DISP_9 = 0x6F,
};
int num_to_disp(uint8_t num);

int seven_disp_init(struct seven_disp_tm1636* disp, uint8_t dio_pin, uint8_t clk_pin);
// int seven_disp_send_data(struct seven_disp_tm1636* disp, uint8_t position);
int seven_disp_send_data_auto_inc(struct seven_disp_tm1636* disp, uint8_t position);
int seven_disp_send_cmd(struct seven_disp_tm1636* disp, uint8_t cmd);
int seven_disp_set_data(struct seven_disp_tm1636* disp, uint8_t* data, uint8_t len);



int seven_disp_send_update(struct seven_disp_tm1636* disp);
// int sdtm_set_data(struct seven_disp_tm1636* disp, char* data);

// int seven_disp_init(struct seven_disp_tm1636* disp, uint8_t dio_pin, uint8_t clk_pin);

// void seven_disp_write_byte(uint8_t dio_pin, uint8_t clk_pin, uint8_t byte);

// void seven_disp_start(struct seven_disp_tm1636* disp);
// void seven_disp_stop(struct seven_disp_tm1636* disp);

// void seven_disp_delay(void);

// void seven_disp_start(uint8_t dio_pin, uint8_t clk_pin);

// void seven_disp_stop(uint8_t dio_pin, uint8_t clk_pin);


// // 1 START 
// // 2  CMD 0x40 auto increment
// // 3 stop
// // 4 start
// // 5 CMD C0 <- pozycja 0 w wysweitlaczu
// // 6 znak 1
// // 7 znak 2
// //8 znak 3
// // 9 znak 4
// // 10 stop

// // 11start
// // 12 ON oraz jasnosc 0x88
// // 13 stop

// // koleje literki :
// // 1 START 
// // 2  CMD 0x40 auto increment
// // 3 stop
// // 4 start
// // 5 CMD C0 <- pozycja 0 w wysweitlaczu
// // 6 znak 1
// // 7 znak 2
// //8 znak 3
// // 9 znak 4
// // 10 stop



#endif /*_SEVEN_DISP_TM1636_H_*/