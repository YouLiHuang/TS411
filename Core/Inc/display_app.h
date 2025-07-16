/*
 * @Author: YouLiHuang huangyouli.scut@gmail.com
 * @Date: 2025-07-14 21:11:07
 * @LastEditors: YouLiHuang huangyouli.scut@gmail.com
 * @LastEditTime: 2025-07-15 11:58:49
 * @FilePath: \MDK-ARMi:\CUBEMX\prj\Tsf411\Core\Inc\display_app.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef DISPLAY_APP_H
#define DISPLAY_APP_H

#include "stdint.h"

#define SCREEN_TEST                 0
#define USE_LCD_DMA                 0

uint32_t BSP_LCD_FillRect(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height, uint16_t Color);
void BSP_LCD_Clear(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height);
void Display_Gui_init(void);

#endif

