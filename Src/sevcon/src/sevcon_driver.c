/***************************************************************************************************
 * @file sevcon_driver.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief SEVCON functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SEVCON_DRIVER
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "sevcon_driver.h"
#include "sevcon_hdwr.h"

#include <def_common.h>
#include <log/log_api.h>
#include <stdio.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t sevcon_driver_log_init(sevcon_t *sevcon)
{
    char msg[20];

    sprintf(msg, "CREATED 0x%x", sevcon);

    return (log_new_msg(sevcon->name, LOG_DEBUG, msg));
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
