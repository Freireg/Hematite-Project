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
	char text1[] = "Default Text 1";
	char text2[] = "Default Text 2";
	uint8_t i = 1;

	ST7789_Init();
	while(1) {
		ST7789_Fill_Color(DARKBLUE);
		ST7789_WriteString(10, 16, "ThreadX Example", Font_16x26, WHITE, DARKBLUE);
		tx_thread_sleep(200);

		while(i < 6) {
			ST7789_WriteString(10, (16 + (i*30)), text1, Font_16x26, WHITE, DARKBLUE);
			tx_thread_sleep(300);
			ST7789_WriteString(10, (16 + (i*30)), text2, Font_16x26, WHITE, DARKBLUE);
			tx_thread_sleep(300);

			i++;
		}
		i = 1;
		ST7789_WriteString(10, 196, "End of Example", Font_16x26, WHITE, DARKBLUE);
		tx_thread_sleep(200);
	}
}
/* USER CODE END 1 */
