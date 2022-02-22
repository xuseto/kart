/***************************************************************************************************
 * @file flight_controller_conductor.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 17/02/2022 by jnieto
 * @brief FLIGHT_CONTROLLER functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup FLIGHT_CONTROLLER_CONDUCTOR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "flight_controller_conductor.h"
#include "cmsis_os2.h"
#include <stdlib.h>
#include <def_common.h>
#include <stdio.h>
#include "flight_controller_hdwr.h"
#include "flight_controller_driver.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t flight_controller_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 2048,
};

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run thread
 *
 * @param arg \ref flight_controller_cfg_t
 */
static void fligth_controller_thread(void *arg);

/* Private functions -----------------------------------------------------------------------------*/
static void fligth_controller_thread(void *arg)
{
    if (!arg)
    {
        return;
    }

    flight_controller_t *fligth_ctrl_thread = (flight_controller_t *)arg;

    flight_controller_driver_start_periodic(fligth_ctrl_thread);

    while (1)
    {
        osThreadFlagsWait(0x00, osFlagsWaitAny, osWaitForever);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t flight_controller_conductor_init(flight_controller_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    flight_controller_t *flight_controller = (flight_controller_t *)calloc(1, sizeof(flight_controller_t));
    ret = (flight_controller) ? RET_SUCCESS : RET_INT_ERROR;

    if (RET_SUCCESS == ret)
    {
        flight_controller->cfg = cfg;

        ret = flight_controller_driver_init(flight_controller);

        ret = (RET_SUCCESS == ret) ? flight_controller_hdwr_init(flight_controller) : ret;

        flight_controller_task_attributes.name = cfg->name ? cfg->name : "unknown";

        flight_controller->thread_id =
            (RET_SUCCESS == ret) ? osThreadNew(fligth_controller_thread, flight_controller,
                                               &flight_controller_task_attributes)
                                 : NULL;

        ret = (flight_controller->thread_id != NULL) ? RET_SUCCESS : RET_INT_ERROR;
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------
void flight_controller_conductor_resume_thread(flight_controller_t *arg)
{
    if (arg->thread_id)
    {
        osThreadResume(arg->thread_id);
    }
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
