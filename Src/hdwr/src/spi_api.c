
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

#include <hdwr/fifo_api.h>
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

/** define all falgs */
#define SPI_TX (0x01U << 0)
#define SPI_RX (0x01U << 1)
#define SPI_ALL_FLAG (SPI_RX | SPI_TX)

/** Redefine structures of HAL by STM32 */
typedef struct spi_obj_hal_s
{
    SPI_HandleTypeDef *spi_hal; /**< Struct HAL Drivers */
} spi_obj_hal_t;

spi_obj_hal_t spi_obj_hal[] =
    {
        [SPI_A] =
            {
                .spi_hal = &hspi1,
            },
        [SPI_B] =
            {
                .spi_hal = &hspi2,
            },
        [SPI_C] =
            {
                .spi_hal = &hspi3,
            },
};

/** Structure internal of SPI */
typedef struct spi_s
{
    uint16_t size_data;            /**< Sizeof data send o recived data from SPI */
    SPI_HandleTypeDef *driver_hal; /**< Pointer of object of driver HAL */
    void *id_fifo_tx;              /**< ID by FIFOs */
    void *id_fifo_rx;              /**< ID by FIFOs */
    void *msg;                     /**< Where save the value of the Message TX and RX */
    osThreadId_t id_thread;        /**< ID of thread */
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

    if (arguments)
    {
        spi_t *spi = (spi_t *)arguments;
        uint32_t flag_thread = 0x00;
        ret_code_t ret;


 /*       gpio_on(CS_SPI3);
        HAL_SPI_Transmit(&hspi3, (uint8_t *)&tx_buf, sizeof(data), 1000);
        gpio_off(CS_SPI3);*/

        while (1)
        {
            flag_thread = osThreadFlagsWait(SPI_ALL_FLAG, osFlagsWaitAny, osWaitForever);

            if (1) // flag_thread == SPI_TX)
            {
                // ret = fifo_dequeue_msg(spi->id_fifo_tx, spi->msg);

                if (1) // spi->msg && RET_SUCCESS == ret)
                {
                    /*                  uint16_t error = 0;
                                      printf ("SPI : 0x%x ; HAL : 0x%x. \n",spi,spi->driver_hal);
                                      error = (&HAL_SPI_Transmithspi3, spi->msg, spi->size_data, 300);
                                      //error = HAL_SPI_Transmit(&hspi3,  (uint8_t *)&EEPROM_WREN, , 100);
                                      while(HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY);
                    */
                }
            }
        }
    }
}
/* Public functions ------------------------------------------------------------------------------*/
void *spi_init(spi_cfg_t *cfg)
{
    char name[5]; /**< Name of thread */

    if (SPI_MAX < cfg->spi)
    {
        return NULL;
    }

    spi_t *spi = (spi_t *)calloc(1, sizeof(spi_t));

    if (spi)
    {
        char id_sci[] = "0";
        spi->driver_hal = spi_obj_hal[cfg->spi].spi_hal;

        strncat(name, NAME_SPI, sizeof(name) - 1);
        id_sci[0] += cfg->spi;
        strncat(name, id_sci, 1);

        spi->size_data = cfg->spi_fifo_tx.size_msg;

        spi->msg = (uint16_t *)calloc(spi->size_data, sizeof(uint16_t));
        if (!spi->msg)
            return NULL;

        spi->id_fifo_tx = fifo_create_queue(&cfg->spi_fifo_tx);
        if (!spi->id_fifo_tx)
            return NULL;

        spi->id_fifo_rx = fifo_create_queue(&cfg->spi_fifo_rx);
        if (!spi->id_fifo_rx)
            return NULL;

        spi_task_attributes.name = (name) ? name : "unknown";
        spi->id_thread = osThreadNew(spi_task, spi, &spi_task_attributes);
        if (!spi->id_thread)
            return NULL;

        printf("Created SPI : %s (0x%x)\n", name, spi);
    }

    return spi;
}

//--------------------------------------------------------------------------------------------------
ret_code_t spi_enqueue(void *arg, void *msg)
{
    ret_code_t ret = RET_PARAM_ERROR;
    spi_t *spi = (spi_t *)arg;

    if (!spi || NULL == spi->id_thread || !msg)
    {
        return ret;
    }

    ret = fifo_enqueue_msg(spi->id_fifo_tx, msg);

    if (RET_SUCCESS == ret)
    {
        ret = !(osThreadFlagsSet(spi->id_thread, SPI_TX))
                  ? RET_SUCCESS
                  : RET_INT_ERROR;
    }

    return ret;
}
/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/