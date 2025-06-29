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
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BYTE_POOL_SIZE 9120

#define DISPLAY_THREAD_STACK_SIZE 1024
#define BLINKY_THREAD_STACK_SIZE 512

#define MESSAGE_SIZE	sizeof(hematiteQueueData_t)
#define NUMBER_OF_MESSAGES	5
#define QUEUE_SIZE MESSAGE_SIZE * NUMBER_OF_MESSAGES
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
TX_BYTE_POOL bytePool;

uint8_t display_thread_stack[DISPLAY_THREAD_STACK_SIZE];
TX_THREAD display_thread_ptr;

uint8_t blinky_thread_stack[BLINKY_THREAD_STACK_SIZE];
TX_THREAD blinky_thread_ptr;

TX_QUEUE system_queue;
CHAR* system_queue_ptr;

extern TX_SEMAPHORE semaphore;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
VOID displayThreadEntry(ULONG *initial_input);
VOID blinkyThreadEntry(ULONG *param);
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
  tx_byte_pool_create(&bytePool, "System_Byte_Pool", memory_ptr, BYTE_POOL_SIZE);
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

  tx_thread_create(&blinky_thread_ptr,
		  	  	  "Blinky_Thread",
				  blinkyThreadEntry,
				  0x1234,
				  blinky_thread_stack,
				  BLINKY_THREAD_STACK_SIZE,
				  15,
				  15,
				  1,
				  TX_AUTO_START
		  );

  tx_byte_allocate(&bytePool, (VOID**)&system_queue_ptr, QUEUE_SIZE, TX_NO_WAIT);

  tx_queue_create(&system_queue,
		  	  	  "System_Queue",
				  MESSAGE_SIZE,
				  system_queue_ptr,
				  QUEUE_SIZE
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
	char tempBuff[10] = {0};
	char blinkyBuff[10] = {0};
	char usbxBuff[10] = {0};
	uint8_t i = 1;
	ULONG currentTime = 0;
	ULONG elapsedTime = 0;
	float secondsTime = 0.0, uptimeBlinky = 0.0, uptimeUSBX = 0.0;
	hematiteQueueData_t qData;


	currentTime = tx_time_get();

	ST7789_Init();

	/* Draw the first quadrant background */
	ST7789_DrawFilledRectangle(0, 0, 155, 115, GRAYBLUE);
	ST7789_WriteString(10, 10, "Thread 1 Monitor", Font_7x10, WHITE, GRAYBLUE);
	ST7789_WriteString(10, 25, "ID: ", Font_7x10, WHITE, GRAYBLUE);
	ST7789_WriteString(30, 25, "DisplayManager", Font_7x10, WHITE, GRAYBLUE);
	ST7789_WriteString(10, 40, "Init Time: ", Font_7x10, WHITE, GRAYBLUE);
	ST7789_WriteString(10, 65, "Status: ", Font_7x10, WHITE, GRAYBLUE);
	ST7789_WriteString(10, 80, "Uptime: ", Font_7x10, WHITE, GRAYBLUE);

	/* Draw the second quadrant background */
	ST7789_DrawFilledRectangle(0, 120, 155, 120, LIGHTBLUE);
	ST7789_WriteString(10, 130, "Thread 2 Monitor", Font_7x10, WHITE, LIGHTBLUE);
	ST7789_WriteString(10, 145, "ID: ", Font_7x10, WHITE, LIGHTBLUE);
	ST7789_WriteString(30, 145, "Blinky", Font_7x10, WHITE, LIGHTBLUE);
	ST7789_WriteString(10, 160, "Init Time: ", Font_7x10, WHITE, LIGHTBLUE);
	ST7789_WriteString(10, 185, "Status: ", Font_7x10, WHITE, LIGHTBLUE);
	ST7789_WriteString(10, 200, "Uptime: ", Font_7x10, WHITE, LIGHTBLUE);
	ST7789_WriteString(10, 215, "Data: ", Font_7x10, WHITE, LIGHTBLUE);

	/* Draw the third quadrant background */
	ST7789_DrawFilledRectangle(160, 0, 160, 115, LGRAY);
	ST7789_WriteString(170, 10, "Thread 3 Monitor", Font_7x10, WHITE, LGRAY);
	ST7789_WriteString(170, 25, "ID: ", Font_7x10, WHITE, LGRAY);
	ST7789_WriteString(200, 25, "USBX", Font_7x10, WHITE, LGRAY);
	ST7789_WriteString(170, 40, "Init Time: ", Font_7x10, WHITE, LGRAY);
	ST7789_WriteString(170, 65, "Status: ", Font_7x10, WHITE, LGRAY);
	ST7789_WriteString(170, 80, "Uptime: ", Font_7x10, WHITE, LGRAY);
	ST7789_WriteString(170, 95, "Data: ", Font_7x10, WHITE, LGRAY);

	/* Draw the forth quadrant background */
	ST7789_DrawFilledRectangle(160, 120, 160, 120, LBBLUE);
	ST7789_WriteString(170, 130, "Thread 4 Monitor", Font_7x10, WHITE, LBBLUE);
	ST7789_WriteString(170, 145, "ID: ", Font_7x10, WHITE, LBBLUE);
	ST7789_WriteString(200, 145, "FileX", Font_7x10, WHITE, LBBLUE);
	ST7789_WriteString(170, 160, "Init Time: ", Font_7x10, WHITE, LBBLUE);
	ST7789_WriteString(170, 185, "Status: ", Font_7x10, WHITE, LBBLUE);
	ST7789_WriteString(220, 185, "Halted", Font_7x10, WHITE, LBBLUE);
	ST7789_WriteString(170, 200, "Uptime: ", Font_7x10, WHITE, LBBLUE);
	ST7789_WriteString(170, 215, "Data: ", Font_7x10, WHITE, LBBLUE);

	elapsedTime = tx_time_get() - currentTime;
	secondsTime = elapsedTime / 100.0;

	sprintf(tempBuff, "%.2f s", secondsTime);
	ST7789_WriteString(80, 40, tempBuff, Font_7x10, WHITE, GRAYBLUE);

	while(1) {
		ST7789_WriteString(60, 65, "Running", Font_7x10, WHITE, GRAYBLUE);
		currentTime = tx_time_get();
		secondsTime = currentTime / 100.0;

		sprintf(tempBuff, "%.2f", secondsTime);
		ST7789_WriteString(75, 80, tempBuff, Font_7x10, WHITE, GRAYBLUE);

		/* Check for new queue messages */
		if(tx_queue_receive(&system_queue,&qData, 10) == TX_SUCCESS) {
			switch (qData.thread_id) {
				case BLINKY_THREAD_ID:
					/* Update Blinky thread status */
					if(qData.thread_status != RUNNING) {
						ST7789_WriteString(60, 185, "Halted", Font_7x10, WHITE, LIGHTBLUE);
					} else {
						ST7789_WriteString(60, 185, "Running", Font_7x10, WHITE, LIGHTBLUE);
						/* Display thread uptime */
						uptimeBlinky = qData.time / 100.0;
						sprintf(blinkyBuff, "%.2f", uptimeBlinky);
						ST7789_WriteString(75, 200, blinkyBuff, Font_7x10, WHITE, LIGHTBLUE);
					}
					/* Display the data sent from the blinky thread */
					sprintf(blinkyBuff, "%03d", qData.data);
					ST7789_WriteString(60, 215, blinkyBuff, Font_7x10, WHITE, LIGHTBLUE);

					break;
				case USB_THREAD_ID:
					/* Update USB thread status*/
					if(qData.thread_status != RUNNING) {
						ST7789_WriteString(220, 65, "Halted", Font_7x10, WHITE, LGRAY);
					} else {
						ST7789_WriteString(220, 65, "Running", Font_7x10, WHITE, LGRAY);
						/* Display thread uptime */
						uptimeUSBX = qData.time / 100.0;
						sprintf(usbxBuff, "%.2f", uptimeUSBX);
						ST7789_WriteString(235, 80, usbxBuff, Font_7x10, WHITE, LGRAY);
					}
					/* Display the data sent from the usbx thread */
					sprintf(usbxBuff, "%05d", qData.data);
					ST7789_WriteString(235, 95, usbxBuff, Font_7x10, WHITE, LGRAY);
					break;
				default:
					break;
			}
		}
	}

}

VOID blinkyThreadEntry(ULONG *param) {
	uint8_t counter = 0;
	ULONG elapsedTime = 0, currentTime = 0;
	hematiteQueueData_t qData = {0};

	currentTime = tx_time_get();

	/* Set the message ID */
	qData.thread_id = BLINKY_THREAD_ID;
	qData.thread_status = RUNNING;

	while(1) {
		/* Toggle IO */
		HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);

		elapsedTime = tx_time_get() - currentTime;

		qData.time = elapsedTime;
		qData.data = counter;
		/* Send the queue data to the system queue */
		tx_queue_send(&system_queue, &qData, TX_WAIT_FOREVER);

		tx_semaphore_put(&semaphore);

		counter++;
		/* Increasing sleep time for the fun of it */
		tx_thread_sleep(counter * 2);

	}
}
/* USER CODE END 1 */
