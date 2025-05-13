/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_filex.c
  * @author  MCD Application Team
  * @brief   FileX applicative file
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
#include "app_filex.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_threadx.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* Main thread stack size */
#define FX_APP_THREAD_STACK_SIZE         5*1024
/* Main thread priority */
#define FX_APP_THREAD_PRIO               10
/* USER CODE BEGIN PD */
#define BYTE_POOL_SIZE 9120
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* Main thread global data structures.  */
TX_THREAD       fx_app_thread;

/* Buffer for FileX FX_MEDIA sector cache. */
ALIGN_32BYTES (uint32_t fx_sd_media_memory[FX_STM32_SD_DEFAULT_SECTOR_SIZE / sizeof(uint32_t)]);
/* Define FileX global data structures.  */
FX_MEDIA        sdio_disk;
HAL_SD_CardInfoTypeDef *pCardInfoSD;

/* USER CODE BEGIN PV */
uint8_t fx_thread_stack[FX_APP_THREAD_STACK_SIZE];
TX_BYTE_POOL FX_bytePool;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* Main thread entry function.  */
void fx_app_thread_entry(ULONG thread_input);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
  * @brief  Application FileX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
*/
UINT MX_FileX_Init(VOID *memory_ptr)
{
  UINT ret = FX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;
  VOID *pointer;

/* USER CODE BEGIN MX_FileX_MEM_POOL */
  UNUSED(byte_pool);
  UNUSED(pointer);
  tx_byte_pool_create(&FX_bytePool, "FX_Byte_Pool", memory_ptr, BYTE_POOL_SIZE);
/* USER CODE END MX_FileX_MEM_POOL */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*Allocate memory for the main thread's stack*/
  ret = tx_byte_allocate(&FX_bytePool, (VOID**)&fx_thread_stack, FX_APP_THREAD_STACK_SIZE, TX_NO_WAIT);
  ret = FX_SUCCESS;
/* Check FX_APP_THREAD_STACK_SIZE allocation*/
  if (ret != FX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

/* Create the main thread.  */
  ret = tx_thread_create(&fx_app_thread, "FX_Thread", fx_app_thread_entry, 0x1234, fx_thread_stack, FX_APP_THREAD_STACK_SIZE,
                         15, 15, 1, TX_AUTO_START);
  ret = FX_SUCCESS;
/* Check main thread creation */
  if (ret != FX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

/* USER CODE BEGIN MX_FileX_Init */

/* USER CODE END MX_FileX_Init */

/* Initialize FileX.  */
  fx_system_initialize();

/* USER CODE BEGIN MX_FileX_Init 1*/

/* USER CODE END MX_FileX_Init 1*/

  return ret;
}

/**
 * @brief  Main thread entry.
 * @param thread_input: ULONG user argument used by the thread entry
 * @retval none
*/
 void fx_app_thread_entry(ULONG thread_input)
 {

  UINT sd_status = FX_SUCCESS;

/* USER CODE BEGIN fx_app_thread_entry 0*/

/* USER CODE END fx_app_thread_entry 0*/

/* Format the SD memory as FAT */
//  sd_status =  fx_media_format(&sdio_disk,                          // SD_Disk pointer
//                               fx_stm32_sd_driver,                  // Driver entry
//                               (VOID *)FX_NULL,                     // Device info pointer
//                               (UCHAR *) fx_sd_media_memory,        // Media buffer pointer
//                               sizeof(fx_sd_media_memory),          // Media buffer size
//                               FX_SD_VOLUME_NAME,                   // Volume Name
//                               FX_SD_NUMBER_OF_FATS,                // Number of FATs
//                               32,                                  // Directory Entries
//                               FX_SD_HIDDEN_SECTORS,                // Hidden sectors
//                               pCardInfoSD->BlockNbr,                 // Total sectors
//                               FX_STM32_SD_DEFAULT_SECTOR_SIZE,     // Sector size
//                               8,                                   // Sectors per cluster
//                               1,                                   // Heads
//                               1);                                  // Sectors per track

/* Check the format sd_status */
  if (sd_status != FX_SUCCESS)
  {
     /* USER CODE BEGIN SD MEDIA get info error */
//    while(1);
    /* USER CODE END SD MEDIA get info error */
  }

/* Open the SD disk driver */
//  sd_status =  fx_media_open(&sdio_disk, FX_SD_VOLUME_NAME, fx_stm32_sd_driver, (VOID *)FX_NULL, (VOID *) fx_sd_media_memory, sizeof(fx_sd_media_memory));

/* Check the media open sd_status */
  if (sd_status != FX_SUCCESS)
  {
     /* USER CODE BEGIN SD DRIVER get info error */
//    while(1);
    /* USER CODE END SD DRIVER get info error */
  }

/* USER CODE BEGIN fx_app_thread_entry 1*/

/* USER CODE END fx_app_thread_entry 1*/
  }

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
