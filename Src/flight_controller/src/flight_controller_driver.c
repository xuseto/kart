/***************************************************************************************************
 * @file flight_controller_driver.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 14/02/2022 by jnieto
 * @brief FLIGHT_CONTROLLER functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup FLIGHT_CONTROLLER_DRIVER
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "flight_controller/flight_controller_api.h"
#include <def_common.h>
#include "flight_controller_conductor.h"
#include "flight_controller_driver.h"
#include "flight_controller_hdwr.h"

#include "log/log_api.h"
#include <stdio.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Funtion for periodic
 *
 * @param arg \ref flight_controller_t
 */
static void flight_controller_driver_periodic(void *arg);

/* Private functions -----------------------------------------------------------------------------*/
static void flight_controller_driver_periodic(void *arg)
{
    if (arg)
    {
        flight_controller_conductor_resume_thread(arg);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t flight_controller_driver_init(flight_controller_t *arg)
{
    arg->periodic_id = periodic_register((periodic_timers_t)arg->cfg->periodic_timer,
                                         flight_controller_driver_periodic,
                                         arg);

    return (arg->periodic_id ? RET_SUCCESS : RET_INT_ERROR);
}

//--------------------------------------------------------------------------------------------------
ret_code_t flight_controller_driver_start_periodic(flight_controller_t *arg)
{
    if (arg->periodic_id)
    {
        return periodic_start(arg->periodic_id);
    }

    return RET_INT_ERROR;
}

//--------------------------------------------------------------------------------------------------
ret_code_t flight_controller_driver_stop_periodic(flight_controller_t *arg)
{
    if (arg->periodic_id)
    {
        return periodic_stop(arg->periodic_id);
    }

    return RET_INT_ERROR;
}

//--------------------------------------------------------------------------------------------------
void flight_controller_driver_update_dac(flight_controller_t *arg)
{
    for (uint8_t i = 0x00; i < MAX_NUM_CONTROLLER; i++)
    {
        arg->dac_values[i] = (uint16_t)(arg->adc_values[i] * 3.3) / 100;
        flight_controller_hdwr_set_dac(arg, arg->dac_values[i]);
    }
}

//--------------------------------------------------------------------------------------------------
ret_code_t flight_controller_driver_log_init(flight_controller_t *arg)
{
    char msg[20];

    sprintf(msg, "CREATED 0x%x", arg);

    return (log_new_msg(arg->cfg->name, LOG_DEBUG, msg));
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
