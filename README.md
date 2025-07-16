# TS411
lvgl8.3在stm32f411平台下的验证
## 硬件平台

接线方式如下：
| PIN | Function        |
| --- | --------------- |
| PA5 | SPI1_SCK        |
| PA7 | SPI1_MOSI       |
| PB0 | RESET           |
| PB1 | DC              |
| PB3 | TCLK(SPI3_CLK)  |
| PB4 | TDIN(SPI3_MISO) |
| PB5 | TDO(SPI_MOSI)   |
| PB6 | TCS             |
| PB7 | TIRQ            |


## 软件架构
- STM32 HAL库
- STM32 X-Cube-Display 屏幕驱动（ili9341）
- 操作系统 FreeRtos
