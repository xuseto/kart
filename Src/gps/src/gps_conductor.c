/***************************************************************************************************
 * @file GPS_conductor.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 15/03/2022
 * @date Last modification 15/03/2022 by jnieto
 * @brief gps functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup GPS_CONDUCTOR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <stdlib.h>
#include <string.h>
#include <cmsis_os2.h>

#include "gps_conductor.h"
#include "gps_driver.h"
#include "gps_hdwr.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t gps_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .name = "GPS",
        .stack_size = 512,
};

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run thread
 *
 * @param argument \ref NULL
 */
void gps_task(void *argument);

/* Private functions -----------------------------------------------------------------------------*/
void gps_task(void *argument)
{
    if (argument)
    {
        gps_driver_get_msg(argument);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t gps_conductor_init(gps_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    gps_t *gps = calloc(1, sizeof(gps_t));
    if (gps)
    {
        gps->name = gps_task_attributes.name;
        gps->id_thread = osThreadNew(gps_task, gps, &gps_task_attributes);
        ret = (gps->id_thread) ? RET_SUCCESS : RET_INT_ERROR;
    }

    ret = (RET_SUCCESS == ret) ? gps_hdwr_init(cfg, gps) : ret;

    ret = (RET_SUCCESS == ret) ? gps_driver_log_init(gps) : ret;

    return ret;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
