/***************************************************************************************************
 * @file sevcon_driver.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief SEVCON functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SEVCON_DRIVER
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "sevcon_driver.h"
#include "sevcon_hdwr.h"
#include "sevcon_driver_dictionary.h"

#include <def_common.h>
#include <log/log_api.h>
#include <stdio.h>
#include <stdint.h>

#include <hdwr/can_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Process new message
 *
 * @param sevcon \ref sevcon_t
 * @param msg ptr to void
 */
void sevcon_proccess_message(sevcon_t *sevcon, void *msg);

/**
 * @brief Proccess message of velocity
 *
 * @param sevcon \ref sevcon_t
 */
static void sevcon_proccess_velocity(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data);

/**
 * @brief Proccess message of temperature
 *
 * @param sevcon \ref sevcon_t
 */
static void sevcon_proccess_temperature(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data);

/**
 * @brief Proccess message of error
 *
 * @param sevcon \ref sevcon_t
 */
static void sevcon_proccess_error(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data);

/* Private functions -----------------------------------------------------------------------------*/
void sevcon_proccess_message(sevcon_t *sevcon, void *msg)
{

    uint16_t id_sevcon = sevcon_hdwr_get_num_sevcon(msg);
    if (id_sevcon >= SEVCON_MAX_DRIVERS)
    {
        // Force exit because id does not exists
        return;
    }

    uint16_t idx = sevcon_hdwr_get_index(msg);
    uint16_t subidx = sevcon_hdwr_get_subindex(msg);
    uint32_t data = sevcon_hdwr_get_data(msg);

    switch (sevcon_dictionary_found_id(idx, subidx))
    {
    case VELOCITY:
        sevcon_proccess_velocity(sevcon, id_sevcon, data);
        break;
    case MOTOR_TEMPERATURE_1:
        sevcon_proccess_temperature(sevcon, id_sevcon, data);
        break;
    case ERROR_SEVCON:
        sevcon_proccess_error(sevcon, id_sevcon, data);
        break;
    case MAX_DICTIONARY:
    default:
        printf("MAX_DICTIONARY\n");
        break;
    }
}

//--------------------------------------------------------------------------------------------------
static void sevcon_proccess_velocity(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data)
{
    if (data != sevcon->driver[id_sevcon].vel_rpm)
    {
        uint16_t opposite_motor = sevcon_hdwr_get_opposite_motor(id_sevcon);

        sevcon->driver[id_sevcon].vel_rpm = data;
    }
}

//--------------------------------------------------------------------------------------------------
static void sevcon_proccess_temperature(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data)
{
    if (data != sevcon->driver[id_sevcon].temperature)
    {
        uint16_t opposite_motor = sevcon_hdwr_get_opposite_motor(id_sevcon);

        sevcon->driver[id_sevcon].temperature = data;
    }
}

//--------------------------------------------------------------------------------------------------
static void sevcon_proccess_error(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data)
{
    if (data != sevcon->driver[id_sevcon].error)
    {
        uint16_t opposite_motor = sevcon_hdwr_get_opposite_motor(id_sevcon);

        sevcon->driver[id_sevcon].error = data;
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t sevcon_driver_log_init(sevcon_t *sevcon)
{
    char msg[20];

    sprintf(msg, "CREATED 0x%x", sevcon);

    return (log_new_msg(sevcon->name, LOG_DEBUG, msg));
}

//--------------------------------------------------------------------------------------------------
void sevcon_driver_get_msg(void *arg)
{
    sevcon_t *sevcon = (sevcon_t *)arg;
    void *msg;

    while (1)
    {
        msg = sevcon_hdwr_get_msg(sevcon);
        if (msg)
        {
            sevcon_proccess_message(sevcon, msg);
        }
    }
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
