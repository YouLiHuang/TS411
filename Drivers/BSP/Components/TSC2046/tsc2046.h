/*
 * @Author: YouLiHuang huangyouli.scut@gmail.com
 * @Date: 2025-07-15 20:34:57
 * @LastEditors: YouLiHuang huangyouli.scut@gmail.com
 * @LastEditTime: 2025-07-16 15:25:32
 * @FilePath: \MDK-ARMi:\learning\LVGL\TS411\Drivers\BSP\Components\TSC2046\tsc2046.h
 */
#ifndef TSC2046_H
#define TSC2046_H

#include "main.h"
#include "stdbool.h"
#include "spi.h"

#define SCAN_TIME 5
#define SCREEN_WIDTH 320
#define SCREEN_HEIGH 240
#define CMD_READX 0xD0
#define CMD_READY 0x90

typedef struct coordinate
{
    uint16_t xpos;
    uint16_t ypos;
} coordinate;

typedef enum Press_state
{
    PRESS = 0,
    NO_PRESS

} Press_state;

typedef enum CS_LEVEL
{
    CS_LOW = 0,
    CS_HIGH = 1

} CS_LEVEL;

typedef void (*TSC2046_CS_Fun)(CS_LEVEL cs_level);
typedef bool (*TSC2046_Scan_Fun)(void);
typedef void (*TSC2046_Send_Fun)(uint8_t *data, uint16_t len);
typedef void (*TSC2046_Recv_Fun)(uint8_t *data, uint16_t len);
typedef void (*TSC2046_Send_Rev_Fun)(uint8_t *data_Send, uint8_t *data_Recv, uint16_t len);

typedef struct TSC2046_Serial_Port
{
    TSC2046_Scan_Fun Press_scan;
    TSC2046_CS_Fun CS_output;
    TSC2046_Send_Fun send_bytes;
    TSC2046_Recv_Fun read_bytes;
    TSC2046_Send_Rev_Fun send_read_bytes;

} TSC2046_Serial_Port;

typedef struct TSC2046_Device_info
{
    bool init_flag;
    uint16_t screen_width;
    uint16_t screen_height;
} TSC2046_Device_info;

typedef struct TSC2046_Drv
{
    TSC2046_Device_info *info;
    TSC2046_Serial_Port *Port;
} TSC2046_Drv;

bool BSP_TSC2046_init(void);
bool BSP_TSC2046_read(coordinate *pos);
bool BSP_TSC2046_scan(coordinate *pos);
bool BSP_TSC2046_press(void);

#endif
