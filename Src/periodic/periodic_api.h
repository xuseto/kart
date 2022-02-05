/***************************************************************************************************
 * @file periodic_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 05/02/2022
 * @date Last modification 05/02/2022 by jnieto
 * @brief periodic
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @addtogroup PERIODIC
    @{
    @defgroup PERIODIC_API  PERIODIC object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __PERIODIC_API_H
#define __PERIODIC_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*/
typedef enum periodic_timers_s
{
    PERIODIC_EVERY_100_MS,
    PERIODIC_EVERY_200_MS,
    PERIODIC_EVERY_500_MS,
    PERIODIC_EVERY_1_SG,
} periodic_timers_t;

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init periodic module
 *
 */
ret_code_t periodic_init(void);

#endif /* __PERIODIC_API_H */

/**
 * @}
 */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
