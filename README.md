<!--
 * @Author: YouLiHuang huangyouli.scut@gmail.com
 * @Date: 2025-07-16 16:15:20
 * @LastEditors: YouLiHuang huangyouli.scut@gmail.com
 * @LastEditTime: 2025-07-16 16:31:08
 * @FilePath: \TS411\README.md
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
-->
# TS411

lvgl8.3在stm32f411平台下的验证

## 硬件平台

### IC以及接口
| IC               | 接口 |
| ---------------- | ---- |
| ili9341(LCD驱动) | SPI1 |
| TSC2046(触摸IC)  | SPI3 |


### 接线方式
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
- STM32 X-Cube-Display LCD驱动
- 操作系统 FreeRtos CMSIS 2.0

## 尚未解决的软件问题
- TSC2046驱动接收16bits(2个byte)转12bits时数据"截断"，最大ADC值为2048？(理论值应为4096)
  


## 开发过程心得
- TSC2046时钟最大速度有限制(开发时忽略了导致读数失败)
- LVGL的flush接口参数"色块"为一个缓冲区，可以直接使用(与LCD接口适配)
  

