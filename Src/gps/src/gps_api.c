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
#include "gps_driver.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
gps_id_t gps_init(gps_cfg_t *cfg)
{

    if (!cfg)
    {
        return NULL;
    }

    return gps_conductor_init(cfg);
}

//--------------------------------------------------------------------------------------------------
float gps_get_velocity_north_axis(gps_id_t id)
{
    gps_t *obj = (gps_t *)id;

    return gps_driver_get_velocity_north_axis(obj);
}

//--------------------------------------------------------------------------------------------------
float gps_get_velocity_east_axis(gps_id_t id)
{
    gps_t *obj = (gps_t *)id;

    return gps_driver_get_velocity_east_axis(obj);
}

//--------------------------------------------------------------------------------------------------
float gps_get_velocity_down_axis(gps_id_t id)
{
    gps_t *obj = (gps_t *)id;

    return gps_driver_get_velocity_down_axis(obj);
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
