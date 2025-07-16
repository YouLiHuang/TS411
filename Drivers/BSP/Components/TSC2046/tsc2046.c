#include "tsc2046.h"
#include "main.h"

static TSC2046_Serial_Port TSC2046_Port;
static TSC2046_Device_info TSC2046_info = {
    .init_flag = false,
    .screen_height = SCREEN_HEIGH,
    .screen_width = SCREEN_WIDTH};
static TSC2046_Drv TSC2046_driver;

static bool TSC2046_Port_Press_scan(void);
static void TSC2046_Port_CS_output(CS_LEVEL cs_level);
static void TSC2046_Port_Send_bytes(uint8_t *data, uint16_t len);
static void TSC2046_Port_Recv_bytes(uint8_t *data, uint16_t len);
static void TSC2046_Port_Send_Recv_bytes(uint8_t *data_Send, uint8_t *data_Recv, uint16_t len);

static bool TSC2046_Port_Press_scan(void)
{
    if (HAL_GPIO_ReadPin(TSIRQ_GPIO_Port, TSIRQ_Pin) == GPIO_PIN_RESET)
        return true;
    else
        return false;
}
static void TSC2046_Port_CS_output(CS_LEVEL cs_level)
{
    if (cs_level == CS_HIGH)
        HAL_GPIO_WritePin(TCS_GPIO_Port, TCS_Pin, GPIO_PIN_SET);
    else if (cs_level == CS_LOW)
        HAL_GPIO_WritePin(TCS_GPIO_Port, TCS_Pin, GPIO_PIN_RESET);
}
static void TSC2046_Port_Send_bytes(uint8_t *data, uint16_t len)
{
    /*your code here*/
    if (data != NULL && len != 0)
        HAL_SPI_Transmit(&hspi3, data, len, 100);
}

static void TSC2046_Port_Recv_bytes(uint8_t *data, uint16_t len)
{
    /*your code here*/
    if (data != NULL && len != 0)
        HAL_SPI_Receive(&hspi3, data, len, 100);
}

static void TSC2046_Port_Send_Recv_bytes(uint8_t *data_Send, uint8_t *data_Recv, uint16_t len)
{
    /*your code here*/
    if (data_Send != NULL && data_Recv != NULL && len != 0)
        HAL_SPI_TransmitReceive(&hspi3, data_Send, data_Recv, len, 100);
}

TSC2046_Drv *BSP_TSC2046Drv_request(void)
{
    return &TSC2046_driver;
}

TSC2046_Device_info *BSP_TSC2046_info_get(void)
{
    TSC2046_Drv *Drv = BSP_TSC2046Drv_request();
    return Drv->info;
}

bool BSP_TSC2046_init(void)
{
    TSC2046_Drv *Drv = BSP_TSC2046Drv_request();
    /*Port init*/
    TSC2046_Port.Press_scan = TSC2046_Port_Press_scan;
    TSC2046_Port.CS_output = TSC2046_Port_CS_output;
    TSC2046_Port.read_bytes = TSC2046_Port_Recv_bytes;
    TSC2046_Port.send_bytes = TSC2046_Port_Send_bytes;
    TSC2046_Port.send_read_bytes = TSC2046_Port_Send_Recv_bytes;
    Drv->Port = &TSC2046_Port;

    /*device info init*/
    TSC2046_info.init_flag = true;
    Drv->info = &TSC2046_info;

    return true;
}

bool BSP_TSC2046_read(coordinate *pos)
{
    TSC2046_Drv *Drv = BSP_TSC2046Drv_request();

    uint8_t CMD[] = {CMD_READX, CMD_READY};
    uint8_t buf_Recv[2];
    pos->xpos = 0;
    pos->ypos = 0;
    if (Drv != NULL)
    {

        /*Read xPos*/
        Drv->Port->CS_output(CS_LOW);
        Drv->Port->send_bytes(&CMD[0], 1);
        Drv->Port->read_bytes(buf_Recv, 2);
        Drv->Port->CS_output(CS_HIGH);
        pos->xpos = ((uint16_t)buf_Recv[0] << 8 | buf_Recv[1]) >> 4;

        buf_Recv[0] = 0;
        buf_Recv[1] = 0;
        /*Read yPos*/
        Drv->Port->CS_output(CS_LOW);
        Drv->Port->send_bytes(&CMD[1], 1);
        Drv->Port->read_bytes(buf_Recv, 2);
        Drv->Port->CS_output(CS_HIGH);
        pos->ypos = ((uint16_t)buf_Recv[0] << 8 | buf_Recv[1]) >> 4;

        /*convert to xy*/
        pos->xpos = SCREEN_WIDTH - pos->xpos * SCREEN_WIDTH / 2048;
        pos->ypos = pos->ypos * SCREEN_HEIGH / 2048;
    }
    else
    {
        return false;
    }

    return true;
}

bool BSP_TSC2046_scan(coordinate *pos)
{

    TSC2046_Drv *Drv = BSP_TSC2046Drv_request();

    uint32_t xpos_sum = 0;
    uint32_t ypos_sum = 0;
    coordinate array[SCAN_TIME];
    pos->xpos = 0;
    pos->ypos = 0;

    bool ret = false;

    for (uint8_t i = 0; i < SCAN_TIME; i++)
    {

        ret = BSP_TSC2046_read(&array[i]);
        if (ret != true)
            break;
    }

    for (uint8_t i = 0; i < SCAN_TIME; i++)
    {
        xpos_sum += array[i].xpos;
        ypos_sum += array[i].ypos;
    }
    pos->xpos = xpos_sum / SCAN_TIME;
    pos->ypos = ypos_sum / SCAN_TIME;

    return ret;
}

bool BSP_TSC2046_press(void)
{
    if (HAL_GPIO_ReadPin(TSIRQ_GPIO_Port, TSIRQ_Pin) == GPIO_PIN_RESET)
        return true;
    else
        return false;
}
