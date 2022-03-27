/***************************************************************************************************
 * @file flight_controller_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 14/02/2022 by jnieto
 * @brief flight controller
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup FLIGHT_CONTROLLER_API
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __FLIGHT_CONTROLLER_API_H
#define __FLIGHT_CONTROLLER_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include "flight_controller/flight_controller_config.h"

#include <cmsis_os2.h>
#include <hdwr/adc_api.h>
#include <periodic/periodic_api.h>
#include <hdwr/pwm_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Struct configurated this module */
typedef struct
{
    const char *name;                            /**< name of thread */
    adc_stm32_t adc_channel[MAX_NUM_CONTROLLER]; /** Cfg numer of channel ADC input */
    periodic_timers_t periodic_timer;            /** Cfg timeout for periodic module */
    pwm_cfg_t dac_cfg[MAX_NUM_CONTROLLER];
} flight_controller_cfg_t;

/** Struct object data this module */
typedef struct
{
    flight_controller_cfg_t *cfg;            /** Ptr of cfg structure */
    osThreadId_t thread_id;                  /** ID for thread */
    periodic_id_t periodic_id;               /** ID for periodic */
    float adc_values[MAX_NUM_CONTROLLER];    /** Values of de ADCs 0 - 3.3V */
    float adc_offset[MAX_NUM_CONTROLLER];    /** Values initial of de ADCs 0 - 3.3V */
    uint16_t dac_values[MAX_NUM_CONTROLLER]; /** Values of de DACs */
    pwm_id_t dac_id[MAX_NUM_CONTROLLER];     /** ID form PWM for DACs */
} flight_controller_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief init flight controller module
 *
 * @param cfg \ref flight_controller_cfg_t
 * @return ret_code_t \ref ret_code_t
 */
ret_code_t flight_controller_init(flight_controller_cfg_t *cfg);

void flight_controller_decrease(uint16_t idx_flight_controller, uint16_t value);
void flight_controller_increase(uint16_t idx_flight_controller, uint16_t value);

#endif /* __FLIGHT_CONTROLLER_API_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
