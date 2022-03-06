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
 ****************************************************************************************************

    @addtogroup SYSTEM_OBJ
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "system_obj.h"
#include <heartbeat/heartbeat_api.h>
//#include "flight_controller/flight_controller_api.h"
#include <hdwr/adc_api.h>
#include <hdwr/can_api.h>
#include <periodic/periodic_api.h>
#include <sevcon/sevcon_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
/** Struct of the HeartBeat */
heartbeat_cfg_t heartbeat =
    {
        .delay_ms = PERIODIC_EVERY_1_SG, // 1 sg
        .gpio = LED_GREEN,
        .name = "HEARTBEAT",
};

/** Struct of the flight controller */
flight_controller_cfg_t flight_controller_cfg =
    {
        .name = "FLIGHT_CONTROLLER",
        .adc_channel =
            {
                [0] = ADC_IN1,
                [1] = ADC_IN2,
                [2] = ADC_IN4,
                [3] = ADC_IN5,
            },
        .periodic_timer = PERIODIC_EVERY_100_MS,
        .dac_cfg =
            {
                [0] = {
                    .frequency = 10000, // 10KHz
                    .duty = 0,          // 0%
                    .pwm = PWM_3,
                    .channel = PWM_CHANNEL_1,

                },
                [1] = {
                    .frequency = 10000, // 10KHz
                    .duty = 0,          // 0%
                    .pwm = PWM_3,
                    .channel = PWM_CHANNEL_2,

                },
                [2] = {
                    .frequency = 10000, // 10KHz
                    .duty = 0,          // 0%
                    .pwm = PWM_3,
                    .channel = PWM_CHANNEL_3,

                },
                [3] = {
                    .frequency = 10000, // 10KHz
                    .duty = 0,          // 0%
                    .pwm = PWM_3,
                    .channel = PWM_CHANNEL_4,

                },

            },
};

/** Struct of the CAN BUS */
can_cfg_t can_cfg =
    {
        .num_msg = 16,
        .assignament_can = CAN_1,
        .type = CAN_TYPE_STD,
        .filter = NULL,
};

/** Struct of SEVCON */
sevcon_cfg_t sevcon_cfg =
    {
        .fifo_cfg = {
            .num_msg = 20,
        },
};

/** Struct of the DAC */

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
