
/***************************************************************************************************
 * @file can_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 05/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief CAN
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup CAN_API
    @{

       * Clock's CAN is 110 MHz
       * source: https://phryniszak.github.io/stm32g-fdcan/
*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hdwr/can_api.h"
#include <stm32l5xx_hal_fdcan.h>

#include <def_common.h>
#include <stdio.h>
#include <string.h>
#include <def_common.h>
#include <log/log_api.h>

/* Defines ---------------------------------------------------------------------------------------*/
/** Offset to indicate data length \ref FDCAN_data_length_code */
#define OFFSET_BITS_DLC 16

/* Private values --------------------------------------------------------------------------------*/
/** struct external of HAL libarires */
extern FDCAN_HandleTypeDef hfdcan1;

/** Name for fifo queue */
char name_fifo_can[10] = "CAN_FIFO_";

/** Name for thread */
char name_thread_can[5] = "CAN_";

/** ID of thread */
osThreadId_t id_thread;

/** Definitions for defaultTask */
osThreadAttr_t can_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 1024,
};

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run Thread
 *
 * @param aguments \ref spi_t
 */
void can_task(void *aguments);

can_msg_t msg;
/* Private functions -----------------------------------------------------------------------------*/
void can_task(void *aguments)
{
    can_cfg_t *can = (can_cfg_t *)aguments;

    can_msg_t msg;

    for (uint8_t I = 0; I < MAX_CAN_MSG_LENGTH; I++)
    {
        msg.data[I] = I + 10;
    }
    msg.id_frame = 0x200;
    msg.length = MAX_CAN_MSG_LENGTH;

    can_tx(CAN_1, &msg);

    osThreadFlagsWait(NULL, osFlagsWaitAny, osWaitForever);
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t can_create(can_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    if (!cfg || cfg->assignament_can >= CAN_MAX || cfg->num_msg == NULL)
    {
        return ret;
    }

    if (cfg->assignament_can == CAN_1)
    {
        cfg->handle = &hfdcan1;
    }
    else
    {
        return ret;
    }

    name_thread_can[4] = '0' + cfg->assignament_can;
    can_task_attributes.name = name_thread_can;
    id_thread = osThreadNew(can_task, cfg, &can_task_attributes);

    /* Start the FDCAN module */
    HAL_StatusTypeDef ret_hal = HAL_FDCAN_Start(cfg->handle);
    ret = (HAL_OK == ret_hal) ? RET_SUCCESS : RET_INT_ERROR;

    char msg[20];
    if (HAL_OK == ret_hal)
    {
        /** Activate ISR FIFO 0 and FIFO 1 */
        HAL_FDCAN_ActivateNotification(cfg->handle, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
        HAL_FDCAN_ActivateNotification(cfg->handle, FDCAN_IT_RX_FIFO0_MESSAGE_LOST, 0);
        HAL_FDCAN_ActivateNotification(cfg->handle, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0);
        HAL_FDCAN_ActivateNotification(cfg->handle, FDCAN_IT_RX_FIFO1_MESSAGE_LOST, 0);

        sprintf(msg, "CREATED CAN %d", cfg->assignament_can);

        return (log_new_msg(can_task_attributes.name, LOG_DEBUG, msg));
    }

    sprintf(msg, "FAIL CREATED CAN %d", cfg->assignament_can);
    log_new_msg(can_task_attributes.name, LOG_DEBUG, msg);

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t can_tx(can_number_t can_id, can_msg_t *msg)
{
    ret_code_t ret = RET_INT_ERROR;

    if (can_id >= CAN_MAX)
    {
        return ret;
    }

    uint32_t mailbox; // required by the current HAL
    FDCAN_TxHeaderTypeDef tx_msg;
    FDCAN_HandleTypeDef *handle;

    if (can_id == CAN_1)
    {
        handle = &hfdcan1;
        // tx_msg.Identifier = hfdca
    }
    tx_msg.Identifier = msg->id_frame;
    tx_msg.IdType = CAN_TYPE_STD;
    tx_msg.TxFrameType = FDCAN_DATA_FRAME;
    tx_msg.DataLength = msg->length << OFFSET_BITS_DLC;
    tx_msg.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    tx_msg.BitRateSwitch = FDCAN_BRS_OFF;
    tx_msg.BitRateSwitch = FDCAN_BRS_OFF;
    tx_msg.FDFormat = FDCAN_CLASSIC_CAN;
    tx_msg.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    tx_msg.MessageMarker = 0;

    ret = (HAL_OK == HAL_FDCAN_AddMessageToTxFifoQ(handle, &tx_msg, msg->data)) ? RET_SUCCESS : RET_INT_ERROR;

    while (HAL_FDCAN_IsTxBufferMessagePending(handle, mailbox))
        ;
    
    return ret;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/