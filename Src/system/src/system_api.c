/***************************************************************************************************
 * @file system_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 24/11/2021
 * @date Last modification 05/03/2021 by jnieto
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

#include "heartbeat/heartbeat_api.h"
#include "hdwr/gpio_api.h"
#include "periodic/periodic_api.h"
#include "log/log_api.h"
#include "hdwr/uart_api.h"
#include "sevcon/sevcon_api.h"
#include "gps/gps_api.h"

#include "cmsis_os2.h"
#include "def_common.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
gpio_out_t gpio = LED_BLUE; /**< Fixed the GPIO of LED */

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
void system_init(void)
{

    gpio_on(gpio);

    /* init LOGs */
    ret_code_t ret = log_init();

    /* Init periodic module */
    ret = (RET_SUCCESS == ret) ? periodic_init() : ret;
    /* Init heartbeat module */
    ret = (RET_SUCCESS == ret) ? heartbeat_init(&heartbeat) : ret;
    /* Init Sevcon */
    ret = (RET_SUCCESS == ret) ? sevcon_init(&sevcon_cfg) : ret;

    /* INIT COMMS */
    /* Init CAN module */
    ret = (RET_SUCCESS == ret) ? can_create(&can_cfg) : ret;
    /* Init USART */
    ret = (RET_SUCCESS == ret) ? uart_create(&uart_cfg) : ret;

    /* INIT PERIPHERALS */
    /* Init GPS */
    gps_cfg.output_fields.ins.all = 0x00;
    gps_cfg.output_fields.ins.bit.vel_ned = 1;
    ret = (RET_SUCCESS == ret) ? gps_init(&gps_cfg) : ret;
    /* Init flight controller module */
    // ret = (RET_SUCCESS == ret) ? flight_controller_init(&flight_controller_cfg) : ret;

    osDelay(300);

    if (RET_SUCCESS == ret)
    {
        gpio_off(gpio);
    }
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
