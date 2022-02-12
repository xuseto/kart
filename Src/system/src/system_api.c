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
#include <system/system_api.h>
#include <heartbeat/heartbeat_api.h>
#include <dac/dac_api.h>
#include "cmsis_os2.h"
#include "def_common.h"
#include "hdwr/gpio_api.h"
#include "periodic/periodic_api.h"
#include "hdwr/adc_api.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
gpio_out_t gpio = LED_RED; /**< Fixed the GPIO of LED */

/** Struct of the HeartBeat */
heartbeat_cfg_t heartbeat =
    {
        .delay_ms = PERIODIC_EVERY_1_SG, // 1 sg
        .gpio = LED_GREEN,
        .name = "HeartBeat"};

/** Struct of the DAC */
dac_cfg_t dac =
    {
        .name = "DAC",
        .id_spi =
            {
                .spi = SPI_C,
                .spi_fifo =
                    {
                        .name = "SPIC",
                        .num_msg = 20,
                        .size_msg = 10,
                    },
            },
};

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

    //   /* Init DAC */
    //   if (RET_SUCCESS == ret)
    //   {
    //       ret = dac_init(&dac);
    //   }

    /* Init ADCs module */
    if (RET_SUCCESS == ret)
    {
        ret = adc_init();
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
