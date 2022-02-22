/***************************************************************************************************
 * @file system_obj.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 24/11/2021
 * @date Last modification 24/11/2021 by jnieto
 * @brief Define all objets of the system Kart
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @addtogroup SYSTEM_OBJ
    @{
    @defgroup SYSTEM_OBJ  SYSTEM object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __SYSTEM_OBJ_H
#define __SYSTEM_OBJ_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <heartbeat/heartbeat_api.h>
#include "flight_controller/flight_controller_api.h"

/* Typedefs --------------------------------------------------------------------------------------*/
extern heartbeat_cfg_t heartbeat;
extern flight_controller_cfg_t flight_controller_cfg;

/* Public Function -------------------------------------------------------------------------------*/

#endif /* __SYSTEM_OBJ_H */

/**
 * @}
 */
/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
