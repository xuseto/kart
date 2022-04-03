/***************************************************************************************************
 * @file user_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 31/03/2022
 * @date Last modification 31/03/2022 by jnieto
 * @brief USER
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @addtogroup USER
    @{
    @defgroup USER_API  USER object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __USER_API_H
#define __USER_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <stdint.h>
#include "cmsis_os2.h"
#include "hdwr/fifo_api.h"
#include "hdwr/uart_api.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Struct cfg by user module */
typedef struct
{
    fifo_cfg_t fifo_cfg;       /** FIFO CFG */
    uart_number_t uart_number; /** Number uart */
} user_cfg_t;

/** Struct data by user module */
typedef struct
{
    osThreadId_t id_thread; /** ID for thread */
    fifo_t id_fifo;
    uint16_t length_msg_tx;
    uint16_t length_msg_rx;
} user_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init user module
 *
 * @param cfg \ref user_cfg_t
 * @return \ref ret_code_t
 */
ret_code_t user_init(user_cfg_t *cfg);

#endif /* __USER_API_H */

/**
 * @}
 */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
