/***************************************************************************************************
 * @file gps_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief gps functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup GPS_API
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include <gps/gps_api.h>
#include <def_common.h>

#include "gps_conductor.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t gps_init(gps_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    if (!cfg)
    {
        return ret;
    }

    return gps_conductor_init(cfg);
}
/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
