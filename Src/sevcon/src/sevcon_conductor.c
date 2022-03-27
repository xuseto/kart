/***************************************************************************************************
 * @file sevcon_conductor.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief SEVCON functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SEVCON_CONDUCTOR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <stdlib.h>
#include <string.h>

#include "sevcon_conductor.h"
#include "sevcon_driver.h"
#include "sevcon_hdwr.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t sevcon_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .name = "SEVCON",
        .stack_size = 1024,
};

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run thread
 *
 * @param argument \ref NULL
 */
void sevcon_task(void *argument);

/* Private functions -----------------------------------------------------------------------------*/
void sevcon_task(void *argument)
{
    if (argument)
    {
        sevcon_driver_get_msg(argument);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t sevcon_conductor_init(sevcon_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    sevcon_t *sevcon = calloc(1, sizeof(sevcon_t));
    if (sevcon)
    {
        sevcon->name = sevcon_task_attributes.name;
        osThreadId_t id = osThreadNew(sevcon_task, sevcon, &sevcon_task_attributes);
        ret = (id) ? RET_SUCCESS : RET_INT_ERROR;
    }

    ret = (RET_SUCCESS == ret) ? sevcon_hdwr_init(cfg, sevcon) : ret;

    ret = (RET_SUCCESS == ret) ? sevcon_driver_log_init(sevcon) : ret;

    /* Init GPS */
    if (RET_SUCCESS == ret)
    {
        sevcon->gps = gps_init(&cfg->gps_cfg);
        ret = (sevcon->gps) ? RET_SUCCESS : RET_INT_ERROR;
    }

    return ret;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
