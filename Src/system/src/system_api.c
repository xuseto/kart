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

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
gpio_out_t gpio = LED_RED; /**< Fixed the GPIO of LED */

/** Struct of the HeartBeat */
heartbeat_cfg_t heartbeat =
    {
        .delay_ms = 1000, // 1 sg
        .gpio = LED_GREEN,
        .name = "HeartBeat"};

/** Struct of the DAC */
dac_cfg_t dac =
    {
        .name = "DAC",
        .id_spi =
            {
                .spi = SPI_C,
                .cs = CS_SPI3,
                .spi_fifo_tx =
                    {
                        .name = "SPI_TX",
                        .num_msg = 20,
                        .size_msg = 3,
                    },
                .spi_fifo_rx =
                    {
                        .name = "SPI_RX",
                        .num_msg = 20,
                        .size_msg = 3,
                    },
            },
};

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
void system_init(void)
{
    ret_code_t ret;

    gpio_on(gpio);

    /* Init herat Beat */
    ret = heartbeat_init(&heartbeat);

    /* Init DAC */
    if (RET_SUCCESS == ret)
    {
        ret = dac_init(&dac);
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
