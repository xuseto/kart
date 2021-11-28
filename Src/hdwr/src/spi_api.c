
/***************************************************************************************************
 * @file spi_api.h 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 11/11/2021
 * @date Last modification 11/11/2021 by jnieto
 * @brief SPI
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SPI_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hdwr/spi_api.h"

#include <cmsis_os2.h>
#include <stm32l5xx_hal.h>
#include <def_common.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Defines ---------------------------------------------------------------------------------------*/
/** Inital name of SPIs */
#define NAME_SPI "SPI_"

__attribute__((weak)) extern SPI_HandleTypeDef hspi1;
__attribute__((weak)) extern SPI_HandleTypeDef hspi2;
__attribute__((weak)) extern SPI_HandleTypeDef hspi3;

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t spi_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 1024};

/** Redefine structures of HAL by STM32 */
typedef struct spi_obj_hal_s
{
    SPI_HandleTypeDef *spi_hal[SPI_MAX];
} spi_obj_hal_t;

spi_obj_hal_t spi_obj_hal[] =
    {
        [SPI_A] = &hspi1,
        [SPI_B] = &hspi2,
        [SPI_C] = &hspi3,
};

/** Structure internal of SPI */
typedef struct spi_s
{
    char name[5];           /**< Name of thread */
    void *driver_hal;       /**< Pointer of object of driver HAL */
    osThreadId_t id_thread; /**< ID of thread */
} spi_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run Thread
 * 
 * @param aguments \ref spi_t
 */
void spi_task(void *aguments);

/* Private functions -----------------------------------------------------------------------------*/
void spi_task(void *arguments)
{
    if (!arguments)
    {
        return;
    }

    uint32_t flag_thread;

    while (1)
    {
        flag_thread = osThreadFlagsWait(0x00, osFlagsWaitAny, osWaitForever);
    }
}
/* Public functions ------------------------------------------------------------------------------*/
void *spi_init(num_spi_t cfg)
{

    if (SPI_MAX < cfg)
    {
        return NULL;
    }

    spi_t *spi = (spi_t *)calloc(1, sizeof(spi_t));

    if (spi)
    {
        char id_sci[] = "1";
        spi->driver_hal = &spi_obj_hal[cfg];

        strncat(spi->name, NAME_SPI, sizeof(spi->name) - 1);
        id_sci[0] += cfg;
        strncat(spi->name, id_sci, 1);

        spi_task_attributes.name = (spi->name) ? spi->name ? "unknown";
        spi->id_thread = osThreadNew(spi_task, spi, &spi_task_attributes);

        printf("Created comunication : %s (0x%x)\n", spi->name, spi);
    }

    return spi;
}

/**
  * @}
  */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/