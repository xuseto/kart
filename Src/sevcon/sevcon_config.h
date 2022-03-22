/***************************************************************************************************
 * @file sevcon_config.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief SEVCON
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup SEVCON_CONFIG  SEVCON object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __SEVCON_CONFIG_H
#define __SEVCON_CONFIG_H

/* Includes --------------------------------------------------------------------------------------*/
#include <hdwr/can_api.h>

/* Defines ---------------------------------------------------------------------------------------*/
/** MAX of functions callback regsiter every SEVCON */
#define SEVCON_MAX_DRIVERS 4

/** Define type message RX of the CANOpen */
#define OD_TYPE_MSG_CAN TPDO4

/** define ID of every motor */
#define MOTOR_UP_LEFT 0
#define MOTOR_UP_RIGHT 1
#define MOTOR_DOWN_LEFT 2
#define MOTOR_DOWN_RIGHT 3

/** Define opposite motor */
#define MOTOR_OPPOSITE_UP_LEFT 1
#define MOTOR_OPPOSITE_UP_RIGHT 0
#define MOTOR_OPPOSITE_DOWN_LEFT 3
#define MOTOR_OPPOSITE_DOWN_RIGHT 2

#endif /* __SEVCON_CONFIG_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
