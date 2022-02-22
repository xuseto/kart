/***************************************************************************************************
 * @file system_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 24/11/2021
 * @date Last modification 28/11/2021 by jnieto
 * @brief All System of the Kart
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SYSTEM_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "system/system_api.h"
#include "system/src/system_obj.h"

#include <heartbeat/heartbeat_api.h>
#include "hdwr/gpio_api.h"
#include "periodic/periodic_api.h"

#include "cmsis_os2.h"
#include "def_common.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
gpio_out_t gpio = LED_RED; /**< Fixed the GPIO of LED */

/** Import Objs Cfg of Syste */
// extern heartbeat_cfg_t heartbeat;

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
void system_init(void)
{

    gpio_on(gpio);

    /* Init periodic module */
    ret_code_t ret = periodic_init();

    /* Init heartbeat module */
    if (RET_SUCCESS == ret)
    {
        ret = heartbeat_init(&heartbeat);
    }

    /* Init flight controller module */
    if (RET_SUCCESS == ret)
    {
        ret = flight_controller_init(&flight_controller_cfg);
    }

    if (RET_SUCCESS == ret)
    {
        gpio_off(gpio);
    }
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
