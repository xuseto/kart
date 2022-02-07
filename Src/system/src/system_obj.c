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
#include <dac/dac_api.h>
#include <periodic/periodic_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
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
                .spi = SPI_B,
                .spi_fifo =
                    {
                        .name = "SPI_B",
                        .num_msg = 20,
                        .size_msg = 10,
                    },
            },
};

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
