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
#include "hdwr/ieee754.h"
#include <stdio.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
uint16_t decrease_max_percent_working[MAX_NUM_CONTROLLER];
uint16_t delay_tx_msg, tx_front_rear = 0;

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Funtion for periodic
 *
 * @param arg \ref flight_controller_t
 */
static void
flight_controller_driver_periodic(void *arg);

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
        arg->dac_values[i] = (uint16_t)((arg->adc_values[i] * 100.0) / 3.0);
        // Add max percent working
        arg->dac_values[i] -= decrease_max_percent_working[i];
        // Inverter PWM
        arg->dac_values[i] = 100 - arg->dac_values[i];
        flight_controller_hdwr_set_dac(arg->dac_id[i], arg->dac_values[i]);
    }
}

//--------------------------------------------------------------------------------------------------
ret_code_t flight_controller_driver_log_init(flight_controller_t *arg)
{
    char msg[20];

    sprintf(msg, "CREATED 0x%x", arg);

    return (log_new_msg(arg->cfg->name, LOG_DEBUG, msg));
}

//--------------------------------------------------------------------------------------------------
void flight_controller_driver_decrease(uint16_t id, uint16_t value)
{
    decrease_max_percent_working[id] += value;
    if (decrease_max_percent_working[id] > 100)
    {
        decrease_max_percent_working[id] = 100;
    }
}

//--------------------------------------------------------------------------------------------------
void flight_controller_driver_increase(uint16_t id, uint16_t value)
{
    decrease_max_percent_working[id] = (decrease_max_percent_working[id] > value) ? decrease_max_percent_working[id] - value : 0;
}

//--------------------------------------------------------------------------------------------------
void flight_controller_driver_loop_send_values(flight_controller_t *arg)
{
    if (delay_tx_msg % 2 == 0)
    {
        uint32_t value_send[4] = {0};
        uint8_t frame_tx[MAX_SIZEOF_TX_VALUES], j = 2;
        frame_tx[0] = FLIGTH_CONTROLLER_HEAD;
        // Send fast values
        if (delay_tx_msg < 8)
        {
            frame_tx[1] = FLIGTH_CONTROLLER_ID_DATA_SLIPT;
            for (uint8_t i = 0; i < MAX_NUM_CONTROLLER; i++)
            {
                value_send[i] = pack754_32(&arg->slip[i]);
            }
        }
        // Send slow values
        else
        {
            delay_tx_msg = 1;
            frame_tx[1] = (tx_front_rear == POS_FRONT) ? FLIGTH_CONTROLLER_ID_DATA_FRONT : FLIGTH_CONTROLLER_ID_DATA_REAR;
            value_send[0] = pack754_32(&arg->id_p[tx_front_rear]);
            value_send[1] = pack754_32(&arg->id_i[tx_front_rear]);
            value_send[2] = pack754_32(&arg->id_d[tx_front_rear]);
            value_send[3] = pack754_32(&arg->max_slip[tx_front_rear]);
            tx_front_rear = (tx_front_rear == POS_FRONT) ? POS_REAR : POS_FRONT;
        }
        // convert uint32 to char
        for (uint8_t i = 0; i < MAX_NUM_CONTROLLER; i++)
        {
            for (uint8_t z = 0; z < 4; z++)
            {
                frame_tx[j + z] = value_send[i] & 0x000000FF;
                value_send[i] = value_send[i] >> 8;
            }
            j += 4;
        }

        uart_tx(arg->cfg->com, frame_tx, MAX_SIZEOF_TX_VALUES);
    }
    delay_tx_msg++;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
