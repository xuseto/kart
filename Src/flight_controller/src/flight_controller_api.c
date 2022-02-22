/***************************************************************************************************
 * @file flight_controller_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 14/02/2022 by jnieto
 * @brief FLIGHT_CONTROLLER
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup FLIGHT_CONTROLLER_API
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "cmsis_os2.h"
#include <stdlib.h>
#include <def_common.h>
#include <flight_controller/src/flight_controller_conductor.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t flight_controller_init(flight_controller_cfg_t *cfg)
{
    if (!cfg)
    {
        return RET_PARAM_ERROR;
    }

    return flight_controller_conductor_init(cfg);
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
