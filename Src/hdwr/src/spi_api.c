
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
/** Redefine structures of HAL by STM32 */
typedef struct spi_obj_hal_s
{
    SPI_HandleTypeDef *spi_hal[SPI_MAX];
}spi_obj_hal_t;

spi_obj_hal_t spi_obj_hal[] = 
{
    [SPI_A] = &hspi1,
    [SPI_B] = &hspi2,
    [SPI_C] = &hspi3,
};

/** Structure internal of SPI */
typedef struct spi_s
{
    char name[5];       /**< Name of thread */
    void *driver_hal; /**< Pointer of object of driver HAL */
}spi_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
void *spi_init (num_spi_t cfg)
{

    spi_t *spi = (spi_t *)calloc (1, sizeof(spi_t));

    if (spi)
    {
        char id_sci[] = "1";
        spi->driver_hal = &spi_obj_hal[cfg];
        
        strncat (spi->name, NAME_SPI, sizeof(spi->name)-1);
        id_sci[0] += cfg; 
        strncat (spi->name, id_sci, 1);

        printf ("Created comunication : %s (0x%x)\n", spi->name, spi);
        
    }

    return spi;
}

/**
  * @}
  */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/