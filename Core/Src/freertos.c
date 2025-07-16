/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "stdio.h"
#include "ili9341.h"
#include "lcd_conf.h"
#include "tsc2046.h"
#include "../lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_timer.h"
#include "lv_demo_stress.h"
#include "display_app.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for mainTask */
osThreadId_t mainTaskHandle;
const osThreadAttr_t mainTask_attributes = {
    .name = "mainTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};
/* Definitions for touchScreenTask */
osThreadId_t touchScreenTaskHandle;
const osThreadAttr_t touchScreenTask_attributes = {
    .name = "touchScreenTask",
    .stack_size = 1024 * 4,
    .priority = (osPriority_t)osPriorityLow1,
};
/* Definitions for Mutex_SPI1 */
osMutexId_t Mutex_SPI1Handle;
const osMutexAttr_t Mutex_SPI1_attributes = {
    .name = "Mutex_SPI1"};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void mainTaskfun(void *argument);
void TsTaskfun(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
  /* Run time stack overflow checking is performed if
  configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
  called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
void vApplicationMallocFailedHook(void)
{
  /* vApplicationMallocFailedHook() will only be called if
  configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
  function that will get called if a call to pvPortMalloc() fails.
  pvPortMalloc() is called internally by the kernel whenever a task, queue,
  timer or semaphore is created. It is also called by various parts of the
  demo application. If heap_1.c or heap_2.c are used, then the size of the
  heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
  FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
  to query the size of free heap space that remains (although it does not
  provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of Mutex_SPI1 */
  Mutex_SPI1Handle = osMutexNew(&Mutex_SPI1_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of mainTask */
  mainTaskHandle = osThreadNew(mainTaskfun, NULL, &mainTask_attributes);

  /* creation of touchScreenTask */
  touchScreenTaskHandle = osThreadNew(TsTaskfun, NULL, &touchScreenTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_mainTaskfun */
/**
 * @brief  Function implementing the mainTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_mainTaskfun */
void mainTaskfun(void *argument)
{
  /* USER CODE BEGIN mainTaskfun */

  /* Infinite loop */
  for (;;)
  {
    HAL_GPIO_TogglePin(SYSLED_GPIO_Port, SYSLED_Pin);
    osDelay(1000);
  }
  /* USER CODE END mainTaskfun */
}

/* USER CODE BEGIN Header_TsTaskfun */
/**
 * @brief Function implementing the touchScreenTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_TsTaskfun */
void TsTaskfun(void *argument)
{
  /* USER CODE BEGIN TsTaskfun */

  /*lvgl config*/
  lv_init();
  lv_port_disp_init();
  lv_port_indev_init();

  // lv_demo_widgets();
  // lv_demo_benchmark();
  // lv_demo_music();
  lv_demo_keypad_encoder();

  // Display_Gui_init();
  /* Infinite loop */
  for (;;)
  {
    lv_timer_handler();
    osDelay(10);
  }
  /* USER CODE END TsTaskfun */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
