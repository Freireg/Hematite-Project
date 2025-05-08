/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
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
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "st7789.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DISPLAY_THREAD_STACK_SIZE 1024
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t display_thread_stack[DISPLAY_THREAD_STACK_SIZE];
TX_THREAD display_thread_ptr;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
VOID displayThreadEntry(ULONG *initial_input);
/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  /* USER CODE BEGIN App_ThreadX_MEM_POOL */

  /* USER CODE END App_ThreadX_MEM_POOL */
  /* USER CODE BEGIN App_ThreadX_Init */
  tx_thread_create(&display_thread_ptr,
		  	  	  "Display_Thread",
				  displayThreadEntry,
				  0x1234,
				  display_thread_stack,
				  DISPLAY_THREAD_STACK_SIZE,
				  15,
				  15,
				  1,
				  TX_AUTO_START
		  );
  /* USER CODE END App_ThreadX_Init */

  return ret;
}

  /**
  * @brief  Function that implements the kernel's initialization.
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN Before_Kernel_Start */

  /* USER CODE END Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN Kernel_Start_Error */

  /* USER CODE END Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */
VOID displayThreadEntry(ULONG *initial_input) {
//	char text1[] = "Default Text 1";
//	char text2[] = "Default Text 2";
	char tempBuff[5] = {0};
	uint8_t i = 1;

	ST7789_Init();
	while(1) {
//		ST7789_Fill_Color(DARKBLUE);
		ST7789_DrawFilledRectangle(0, 0, 155, 115, GRAYBLUE);
		ST7789_WriteString(10, 10, "Thread 1 Monitor", Font_7x10, WHITE, GRAYBLUE);
		ST7789_WriteString(10, 25, "ID: ", Font_7x10, WHITE, GRAYBLUE);
		ST7789_WriteString(30, 25, "DisplayManager", Font_7x10, WHITE, GRAYBLUE);
		ST7789_WriteString(10, 50, "Status: ", Font_7x10, WHITE, GRAYBLUE);


		ST7789_DrawFilledRectangle(0, 120, 155, 120, LIGHTBLUE);
		ST7789_WriteString(10, 130, "Thread 2 Monitor", Font_7x10, WHITE, LIGHTBLUE);
		ST7789_WriteString(10, 145, "ID: ", Font_7x10, WHITE, LIGHTBLUE);
		ST7789_WriteString(30, 145, "Blinky", Font_7x10, WHITE, LIGHTBLUE);
		ST7789_WriteString(10, 170, "Information...", Font_7x10, WHITE, LIGHTBLUE);


		ST7789_DrawFilledRectangle(160, 0, 160, 115, LGRAY);
		ST7789_WriteString(170, 10, "Thread 3 Monitor", Font_7x10, WHITE, LGRAY);
		ST7789_WriteString(170, 25, "ID: ", Font_7x10, WHITE, LGRAY);
		ST7789_WriteString(200, 25, "USBX", Font_7x10, WHITE, LGRAY);
		ST7789_WriteString(170, 50, "Information...", Font_7x10, WHITE, LGRAY);

		ST7789_DrawFilledRectangle(160, 120, 160, 120, LBBLUE);
		ST7789_WriteString(170, 130, "Thread 4 Monitor", Font_7x10, WHITE, LBBLUE);
		ST7789_WriteString(170, 145, "ID: ", Font_7x10, WHITE, LBBLUE);
		ST7789_WriteString(200, 145, "FileX", Font_7x10, WHITE, LBBLUE);
		ST7789_WriteString(170, 170, "Information...", Font_7x10, WHITE, LBBLUE);

		while(1) {
			sprintf(tempBuff, "%d", i);
			ST7789_WriteString(60, 50, tempBuff, Font_7x10, WHITE, GRAYBLUE);
			tx_thread_sleep(300);
			i++;
		}
		i = 1;
		ST7789_Fill_Color(BLACK);
		tx_thread_sleep(200);
	}
}
/* USER CODE END 1 */
