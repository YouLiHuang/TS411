/*
 * @Author: YouLiHuang huangyouli.scut@gmail.com
 * @Date: 2025-07-14 21:10:43
 * @LastEditors: YouLiHuang huangyouli.scut@gmail.com
 * @LastEditTime: 2025-07-16 12:52:23
 * @FilePath: \MDK-ARMi:\CUBEMX\prj\Tsf411\Core\Src\display_app.c
 */
/* Includes ------------------------------------------------------------------*/
#include "stdlib.h"
#include "stdio.h"
#include "ili9341.h"
#include "lcd_conf.h"
#include "../lvgl.h"
#include "lv_port_disp.h"
#include "lv_timer.h"
#include "lv_demo_stress.h"
#include "tim.h"
#include "display_app.h"
#include "tsc2046.h"

#define CACHE_SIZE (ILI9341_WIDTH * BUFFER_CACHE_LINES)

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
static void show_touch_coords(lv_timer_t *timer);
lv_obj_t *label;
/* USER CODE END Variables */

volatile static uint16_t CacheBuffer[CACHE_SIZE];

uint32_t BSP_LCD_FillRect(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height, uint16_t Color)
{

  uint32_t pointCnt = 0;
  uint32_t Residue = 0;
  uint32_t yoffset = Ypos;
  uint32_t new_size = 0;

  pointCnt = Width * Height;
  Residue = pointCnt;

  if (pointCnt < CACHE_SIZE)
  {
    for (uint16_t i = 0; i < pointCnt; i++)
      CacheBuffer[i] = Color;

    BSP_LCD_FillRGBRect(Instance, USE_LCD_DMA, (uint8_t *)CacheBuffer, Xpos, Ypos, Width, Height);
  }
  /*lager than buffer*/
  else
  {

    uint16_t line = CACHE_SIZE / Width;
    new_size = Width * line;

    while (1)
    {

      if (Residue >= CACHE_SIZE)
      {
        for (uint16_t i = 0; i < new_size; i++)
          CacheBuffer[i] = Color;

        // BSP_LCD_WaitForTransferToBeDone(0);
        BSP_LCD_FillRGBRect(Instance, USE_LCD_DMA, (uint8_t *)CacheBuffer, Xpos, yoffset, Width, line);
      }
      else
      {
        for (uint16_t i = 0; i < Residue; i++)
          CacheBuffer[i] = Color;

        // BSP_LCD_WaitForTransferToBeDone(0);
        BSP_LCD_FillRGBRect(Instance, USE_LCD_DMA, (uint8_t *)CacheBuffer, Xpos, yoffset, Width, Residue / Width);
        break;
      }

      Residue -= CACHE_SIZE;
      yoffset += line;
    }
    // BSP_LCD_WaitForTransferToBeDone(0);
  }

  return BSP_ERROR_NONE;
}

void BSP_LCD_Clear(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height)
{
  BSP_LCD_FillRect(Instance, Xpos, Ypos, Width, Height, 0);
}

static void show_touch_coords(lv_timer_t *timer)
{
  lv_point_t point;
  lv_indev_t *indev = lv_indev_get_next(NULL);
  while (indev)
  {
    if (indev->driver->type == LV_INDEV_TYPE_POINTER)
    {
      lv_indev_get_point(indev, &point);
      lv_label_set_text_fmt(label, "XPOS:%d,YPOS:%d", point.x, point.y);
      break;
    }
    indev = lv_indev_get_next(indev);
  }
}

void Display_Gui_init(void)
{
  label = lv_label_create(lv_scr_act());
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 100);
  lv_timer_create(show_touch_coords, 10, NULL);
}