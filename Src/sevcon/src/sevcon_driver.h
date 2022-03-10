/***************************************************************************************************
 * @file sevcon_driver.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief SEVCON
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup SEVCON_DRIVER  SEVCON object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __SEVCON_DRIVER_H
#define __SEVCON_DRIVER_H

/* Includes --------------------------------------------------------------------------------------*/
#include <sevcon/sevcon_api.h>
#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Log init sevcon
 *
 * @param sevcon \ref sevcon_t
 * @return \ref ret_code_t
 */
ret_code_t sevcon_driver_log_init(sevcon_t *sevcon);

/**
 * @brief while 1
 *
 * @param arg \ref sevcon_t
 */
void sevcon_driver_get_msg(void *arg);

#endif /* __SEVCON_DRIVER_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
