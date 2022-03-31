
/***************************************************************************************************
 * @file uart_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 10/03/2022
 * @date Last modification 10/03/2022 by jnieto
 * @brief UART
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup UART_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hdwr\uart_api.h"

#include <log\log_api.h>
#include <def_common.h>
#include <stm32l5xx_hal_uart.h>
#include <stdio.h>
#include <cmsis_os2.h>
#include <stdbool.h>

/* Defines ---------------------------------------------------------------------------------------*/
extern UART_HandleTypeDef huart3;

/** Size FIFO RX */
#define SIZEOF_UART_RX 20

/* Private values --------------------------------------------------------------------------------*/

/** Name for fifo queue */
char name_fifo_uart[10] = "UART_FIFO_";

/** Name for thread */
char name_thread_uart[6] = "UART_";

/** ID of thread */
static osThreadId_t id_thread;

/** Definitions for defaultTask */
osThreadAttr_t uart_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 512,
};

/** FIFO RX subscribe to UART */
fifo_t uart_fifo_subscribe[UART_MAX_MODULES_SUBSCRIBE];
/** FIFO RX size to UART */
uint16_t uart_fifo_size[UART_MAX_MODULES_SUBSCRIBE];

/** FIFO RX */
uint8_t uart_rx[SIZEOF_UART_RX] = {0};

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run Thread
 *
 * @param aguments \ref spi_t
 */
void uart_task(void *aguments);

/**
 * @brief Enqueue new message UART recived by UART
 *
 */
void UART_enqueue_new_message(void *handle, uint32_t fifo_UART);

UART_HandleTypeDef *get_handle(uart_number_t uart);

/* Private functions -----------------------------------------------------------------------------*/
void uart_task(void *aguments)
{
    uart_cfg_t *uart = (uart_cfg_t *)aguments;

    osThreadFlagsWait(NULL, osFlagsWaitAny, osWaitForever);
}

//--------------------------------------------------------------------------------------------------
void UART_enqueue_new_message(void *handle, uint32_t fifo_UART)
{
}

//--------------------------------------------------------------------------------------------------
UART_HandleTypeDef *get_handle(uart_number_t uart)
{
    if (uart == UART_3)
    {
        return &huart3;
    }
    else
    {
        return NULL;
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t uart_create(uart_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    if (!cfg || cfg->assignament_uart >= UART_MAX || cfg->num_msg == NULL)
    {
        return ret;
    }

    cfg->handle = get_handle(cfg->assignament_uart);
    if (!cfg->handle)
    {
        return ret;
    }

    name_thread_uart[5] = '0' + cfg->assignament_uart;
    uart_task_attributes.name = name_thread_uart;
    id_thread = osThreadNew(uart_task, cfg, &uart_task_attributes);

    char msg[20];
    if (id_thread) // HAL_OK == ret_hal)
    {
        sprintf(msg, "CREATED UART %d", cfg->assignament_uart);

        return (log_new_msg(uart_task_attributes.name, LOG_DEBUG, msg));
    }

    sprintf(msg, "FAIL CREATED UART %d", cfg->assignament_uart);
    log_new_msg(uart_task_attributes.name, LOG_DEBUG, msg);

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t uart_suscribe_rx_fifo(fifo_t *fifo_rx, uint16_t size, uart_number_t uart)
{
    ret_code_t ret = RET_PARAM_ERROR;

    for (uint8_t i = 0x00; i < UART_MAX_MODULES_SUBSCRIBE; i++)
    {
        if (!uart_fifo_subscribe[i])
        {
            uart_fifo_subscribe[i] = fifo_rx;
            uart_fifo_size[i] = size;
            ret = RET_SUCCESS;
            i = UART_MAX_MODULES_SUBSCRIBE + 1;

            HAL_UART_Receive_IT(&huart3, uart_rx, size);
        }
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t uart_unsuscribe_rx_fifo(fifo_t *fifo_rx)
{
    ret_code_t ret = RET_PARAM_ERROR;

    for (uint8_t i = 0x00; i < UART_MAX_MODULES_SUBSCRIBE; i++)
    {
        if (uart_fifo_subscribe[i] == fifo_rx)
        {
            uart_fifo_subscribe[i] = NULL;
            uart_fifo_size[i] = NULL;
            ret = RET_SUCCESS;
            i = UART_MAX_MODULES_SUBSCRIBE + 1;
        }
    }

    return ret;
}

//* ISR --------------------------------------------------------------------------------------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    for (uint8_t i = 0x00; i < UART_MAX_MODULES_SUBSCRIBE; i++)
    {
        if (uart_fifo_subscribe[i])
        {
            fifo_enqueue_msg(uart_fifo_subscribe[i], &uart_rx);
            HAL_UART_Receive_IT(&huart3, uart_rx, uart_fifo_size[i]);
        }
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    /* Set transmission flag: transfer complete */
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/