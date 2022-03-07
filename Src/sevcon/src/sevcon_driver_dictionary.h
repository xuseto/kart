/***************************************************************************************************
 * @file sevcon_driver_dictionary.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief SEVCON dictionary CANOpen
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup SEVCON_DRIVER_DICTIONARY  SEVCON object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __SEVCON_DRIVER_DICTIONARY_H
#define __SEVCON_DRIVER_DICTIONARY_H

/* Includes --------------------------------------------------------------------------------------*/
#include <sevcon/sevcon_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Enum of index of dicctionary */
typedef enum idx_dictionary_canopen_s
{
    // 0x606C
    VELOCITY,
    // 0x4600
    MOTOR_TEMPERATURE_1,
    // 0x320
    ERROR_SEVCON,
    // 0xFFFF
    MAX_DICTIONARY,
} idx_dictionary_canopen_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/

#endif /* __SEVCON_DRIVER_DICTIONARY_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
