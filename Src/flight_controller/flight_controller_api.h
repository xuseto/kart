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

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "flight_controller_config.h"

#include <cmsis_os2.h>
#include <hdwr/adc_api.h>
#include <periodic/periodic_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Struct configurated this module */
typedef struct flight_controller_cfg_s
{
    adc_stm32_t adc_channel[MAX_NUM_CONTROLLER]; /** Cfg numer of channel ADC input */
    periodic_timers_t periodic_timer;            /** Cfg timeout for periodic module */
} flight_controller_cfg_t;

/** Struct object data this module */
typedef struct flight_controller_s
{
    flight_controller_cfg_t *cfg; /** Ptr of cfg structure */
    osThreadId_t thread_id;       /** ID for thread */
} flight_controller_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
